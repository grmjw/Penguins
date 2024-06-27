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
#include <cstring>
#include <rs485/Rs485Inst.h>
#include <sys/stat.h>
#include <sys/types.h>

const size_t RS485_MSG_MAX_SIZE = 4096U;

using namespace osal::types;
using namespace osal;

Rs485Inst::Rs485Inst()
    : _hwProperty(nullptr), _processThread(true),
      _rxBuffer(new uint8_t[RS485_MSG_MAX_SIZE]) {}

Rs485Inst::~Rs485Inst() {
  delete[] _rxBuffer;
  // close thread
  if (_processThread == true) {
    _processThread = false;

    _thread.join();
  }
  // close the com port
  BOOL status = CloseHandle(_uartPortHandle);
  // check the status from close handle
  if (status != 1) {
    // handle the error
    printf("RS485Inst: The serial port can not closed \n");
  }
}

bool Rs485Inst::Init(IN std::shared_ptr<HwProperty> hwProperty) {
  bool retValue = true;

  // store the hw porperty
  _hwProperty = hwProperty;
  // get the com port
  char port_name[16] = "";
  strcpy_s(port_name, _hwProperty->GetUsedPort().c_str());
  // open the serial port
  _uartPortHandle =
      CreateFile(port_name,                    // com port number
                 GENERIC_READ | GENERIC_WRITE, // access (read-write) mode
                 0,                            // share mode
                 NULL,                         // address of security descriptor
                 OPEN_EXISTING,                // how to create
                 0,                            // file attributes
                 NULL // handle of file with attributes to copy
      );
  // check the handle status
  if (INVALID_HANDLE_VALUE == _uartPortHandle) {
    // handle the error
    printf("RS485Inst: The com port can not be open. com port: %s \n",
           port_name);
    retValue = false;
  } else {
    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.WriteTotalTimeoutMultiplier = 50;
    timeouts.WriteTotalTimeoutConstant = 2000;
    retValue = SetCommTimeouts(_uartPortHandle, &timeouts);
    if (retValue) {
      // configure baudrate from serial port
      retValue = configureBaudrate();
      // if status is true, the receive thread will start
      if (retValue) {
        // initialize the thread
        _thread = std::thread(&Rs485Inst::receiver, this);
      }
    } else {
      // setting timeouts failed.
      printf("RS485Inst: Set timeout failed \n");
      retValue = false;
    }
  }
  return retValue;
}

bool Rs485Inst::configureBaudrate() {
  bool retValue = true;
  DCB dcb;

  // initialize the dcb structure
  SecureZeroMemory(&dcb, sizeof(DCB));
  dcb.DCBlength = sizeof(DCB);
  // get the current configuration
  BOOL status = GetCommState(_uartPortHandle, &dcb);
  // check the status
  if (status != 1) {
    // handle the error
    printf("RS485Inst: GetCommState failed with error %d \n", GetLastError());
    retValue = false;
  } else {
    // com port settings
    //  baud rate
    dcb.BaudRate = std::stoi(_hwProperty->GetLinkSpeed());
    //  data size, xmit and rcv
    dcb.ByteSize = 8;
    //  parity bit
    dcb.Parity = NOPARITY;
    //  stop bit
    dcb.StopBits = ONESTOPBIT;
    // set the com port settings
    status = SetCommState(_uartPortHandle, &dcb);
    if (status != 1) {
      // handle the error
      printf("RS485Inst: SetCommState failed with error %d", GetLastError());
      retValue = false;
    }
  }
  return retValue;
}

bool Rs485Inst::RegisterCallback(IN const HwRegistry &registry,
                                 IN ReceiverCallback callback) {
  // registert the callback function
  _callback = callback;
  return true;
}

bool Rs485Inst::UnRegisterReceiver(IN const HwRegistry &registry) {
  // unregister the callback function
  _callback = nullptr;
  return true;
}

void Rs485Inst::receiver() {
  // receive loop
  while (_processThread) {
    // number of bytes read from the port
    DWORD numberOfBytesRead = 0;
    uint8_t buffer[RS485_MSG_MAX_SIZE] = "";
    // read data from port
    ReadFile(_uartPortHandle, &buffer, sizeof(buffer), &numberOfBytesRead,
             NULL);
    if (numberOfBytesRead > 0) {
      if (_callback != nullptr) {
        // create the buffer with received data
        BufferDescriptor desc(buffer, numberOfBytesRead);
        _callback(desc);
      }
    }
  }
}

bool Rs485Inst::SendData(IN const HwRegistry &registry,
                         IN const BufferDescriptor &bufferDesc) {
  bool retValue = true;
  // number of bytes written to the port
  DWORD numOfBytesWritten = 0;
  // write the buffer to the com port
  BOOL status =
      WriteFile(_uartPortHandle, bufferDesc.GetBufferPtr(),
                (DWORD)bufferDesc.GetSize(), &numOfBytesWritten, NULL);
  // check the status from write file
  if (status != 1) {
    // handle the error
    printf("RS485Inst: The serial port can not send the data \n");
    retValue = false;
  }
  return retValue;
}
