/************************************************************************
 * Copyright
 *
 * s.m.s. smart microwave sensors GmbH
 * In den Waashainen 1
 * 38108 Braunschweig - Germany
 *
 * Register Court: Amtsgericht Braunschweig / Register Number: HRB 4525
 * VAT ID: DE 193324798 / Tax Number: 13/207/02357
 ************************************************************************/
#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <rs485/Rs485Iface.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <string>

const size_t RS485_MSG_MAX_SIZE = 4096U;
const uint32_t TERMINATION_RS485_RECEIVER_CNT = 100U;

osal::Rs485Iface::Rs485Iface(const std::string &ifaceName, uint32_t baudrate)
    : _ifaceName(ifaceName),
      _isRun(false),
      _callback(nullptr),
      _baudrate(baudrate) {}

osal::Rs485Iface::~Rs485Iface() {
  Stop();
  if (0 > close(_fd)) {
    printf(
        "Rs485Iface::UnRegisterReceiver(): Error - Couldn't close serial port, "
        "_fd = %d\n",
        _fd);
  }
}

bool osal::Rs485Iface::Init() {
  _fd = open(_ifaceName.c_str(), O_RDWR | O_NOCTTY);
  if (0 > _fd) {
    printf("Error: Failed to open serial port = %s\n", _ifaceName.c_str());
    printf("open-Call returned with errno = %d\n", errno);
    return false;
  }
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  cfmakeraw(&tty);

  // Configure tty-Attributes -----------------
  tty.c_cc[VMIN] = 1;  // minimum of reading bytes
  tty.c_cflag = (tty.c_cflag & ~CSIZE) |
                CS8;  // was STD_FLG; 8N1, read, no modem status,.
  tty.c_iflag &= ~IGNBRK;
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  tty.c_cflag |= (CLOCAL | CREAD);  // ignore modem controls,
  tty.c_lflag = 0;                  // disable canonical mode
  tty.c_oflag = 0;
  tty.c_cflag &= ~(PARENB | PARODD);  // shut off parity
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  // Configre and set the baudrate ---------------
  speed_t bdflag;
  if (!getBaudrateFlag(bdflag)) {
    return false;
  }
  /* input speed */
  cfsetispeed(&tty, bdflag);
  /* output speed */
  cfsetospeed(&tty, bdflag);

  // Set the tty-Attributes -------------------------
  if (tcsetattr(_fd, TCSANOW, &tty) != 0) {
    printf("Error: Setting the terminal parameter failed");
    return false;
  }

  // Put the terminal into exclusive mode ------------
  // No further open-operations on the terminal are permitted.
  int32_t modelines = 0;
  ioctl(_fd, TIOCEXCL, &modelines);

  // Flash the old received data from serial port
  tcflush(_fd, TCIFLUSH);

  return true;
}

void osal::Rs485Iface::RegisterReceiver(IN ReceiverCallback callback) {
  _callback = callback;
}

void osal::Rs485Iface::UnRegisterReceiver() {
  _callback = nullptr;
  _isRun.store(false);
}

bool osal::Rs485Iface::Start() {
  _isRun.store(true);
  _isStopped.store(false);
  _thread = std::thread(&Rs485Iface::receiver, this);
  _thread.detach();
  return true;
}

void osal::Rs485Iface::Stop() {
  _isRun.store(false);
  // Wait for termination of receiver()-Thread
  uint32_t timeCnt = 0;
  while (!_isStopped.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    timeCnt++;
    if (timeCnt > TERMINATION_RS485_RECEIVER_CNT) {
      printf(
          "Rs485Iface::Stop(): No termination response from "
          "receiver()-Thread\n");
      break;
    }
  }
}

void osal::Rs485Iface::receiver() {
  //--- Serial port receive-Loop -----------------------------------------------
  uint8_t buffer[RS485_MSG_MAX_SIZE];
  size_t size = sizeof(buffer);
  while (_isRun.load()) {
    if (rcvMsg(buffer, size) != true) {
      printf(
          "Rs485Iface::receiver(): rcvMsg() returned without reading data\n");
    }
  }
  tcflush(_fd, TCIFLUSH);
  _isStopped.store(true);
}

bool osal::Rs485Iface::SendMsg(
    IN const osal::types::BufferDescriptor &bufferDesc) {
  bool retVal = true;
  size_t bufSize = bufferDesc.GetSize();
  if (bufSize > 0) {
    size_t nBytesToWrite = bufSize;
    uint8_t *sendPtr = bufferDesc.GetBufferPtr();
    //--- Serial port send-Loop
    //-------------------------------------------------
    while (nBytesToWrite > 0) {
      // Set timeout-Option for serial port with timeval = 100 msec
      struct timeval timeout;
      timeout.tv_sec = 0;
      timeout.tv_usec = 100000;
      // Initialize the input set
      fd_set output_set;
      FD_ZERO(&output_set);
      FD_SET(_fd, &output_set);
      // select-Call to cover the blocking write():
      int32_t retSel = select((_fd + 1), NULL, &output_set, NULL, &timeout);
      if (retSel == -1) {
        printf("Rs485Iface::SendMsg(): Failed to select serial port\n");
        printf("Rs485Iface::SendMsg(): Call returned with errno = %d\n", errno);
        printf(
            "Rs485Iface::SendMsg(): Error - Could not sent complete buffer\n");
        retVal = false;
        break;
      } else {
        // Check if file descriptor _fd is still set in current output set
        // before calling write()
        if (FD_ISSET(_fd, &output_set)) {
          int32_t nBytesSent = write(_fd, sendPtr, bufferDesc.GetSize());
          if (nBytesSent > 0) {
            nBytesToWrite = nBytesToWrite - nBytesSent;
            sendPtr = sendPtr + nBytesSent;
          }
        }
      }
      FD_CLR(_fd, &output_set);
    }
  } else {
    printf("Rs485Iface::SendMsg(): Error - Invalid bufffer size\n");
    retVal = false;
  }
  return retVal;
}

bool osal::Rs485Iface::getBaudrateFlag(OUT speed_t &flag) {
  bool retVal = true;
  switch (_baudrate) {
    case 9600:
      flag = B9600;
      break;
    case 19200:
      flag = B19200;
      break;
    case 38400:
      flag = B38400;
      break;
    case 57600:
      flag = B57600;
      break;
    case 115200:
      flag = B115200;
      break;
    case 230400:
      flag = B230400;
      break;
    case 460800:
      flag = B460800;
      break;
    case 500000:
      flag = B500000;
      break;
    case 576000:
      flag = B576000;
      break;
    case 921600:
      flag = B921600;
      break;
    case 1000000:
      flag = B1000000;
      break;
    case 1152000:
      flag = B1152000;
      break;
    case 1500000:
      flag = B1500000;
      break;
    case 2000000:
      flag = B2000000;
      break;
    case 2500000:
      flag = B2500000;
      break;
    case 3000000:
      flag = B3000000;
      break;
    case 3500000:
      flag = B3500000;
      break;
    case 4000000:
      flag = B4000000;
      break;
    default:
      printf("Error: Wrong baudrate[%u]", _baudrate);
      retVal = false;
      break;
  }
  return retVal;
}

bool osal::Rs485Iface::rcvMsg(uint8_t *buffer, size_t size) {
  bool retVal = true;

  // Set timeout-Option for serial port with timeval = 100 msec
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 200000;
  // Initialize the input set
  fd_set input_set;
  FD_ZERO(&input_set);
  FD_SET(_fd, &input_set);
  // Use select-Call to cover the blocking read():
  int32_t retSel = select((_fd + 1), &input_set, NULL, NULL, &timeout);
  if (retSel == -1) {
    printf("Rs485Iface::rcvMsg(): Failed to select serial port\n");
    printf("Rs485Iface::rcvMsg(): Call returned with errno = %d\n", errno);
    retVal = false;
  } else {
    // Check if file descriptor _fd is still set in current input set before
    // calling read()
    if (FD_ISSET(_fd, &input_set)) {
      auto received = read(_fd, buffer, size);
      if (0 < received) {
        osal::types::BufferDescriptor desc(buffer, received);
        if (nullptr != _callback) {
          _callback(desc);
        }
      }
    }
  }
  FD_CLR(_fd, &input_set);
  return retVal;
}
