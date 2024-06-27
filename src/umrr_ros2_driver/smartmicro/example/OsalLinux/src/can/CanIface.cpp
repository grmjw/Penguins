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
#include <CanIface.h>
#include <unistd.h>

#include <set>
#include <string>
#include <utility>

const uint32_t TERMINATION_CAN_RECEIVER_CNT = 100U;

osal::CanIface::CanIface(osal::types::CanDevId canDeviceId,
                         const std::string &canIfaceName, uint32_t baudrate)
    : _canDeviceId(canDeviceId),
      _canIfaceName(canIfaceName),
      _canBaudrate(0),
      _isRun(false) {}

osal::CanIface::~CanIface() {
  Stop();
  close(_canFd);
}

bool osal::CanIface::Init() {
  // creating CAN socket
  _canFd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (0 > _canFd) {
    printf("Error: Failed to open CAN socket \n");
    return false;
  }

  struct ifreq ifRequest;
  sprintf(ifRequest.ifr_name, "%s", _canIfaceName.c_str());

  if (0 != ioctl(_canFd, SIOCGIFINDEX, &ifRequest)) {
    printf("Error: Failed to get iterface request \n");
    close(_canFd);
    return false;
  }
  struct sockaddr_can sockAddr;
  sockAddr.can_family = AF_CAN;
  sockAddr.can_ifindex = ifRequest.ifr_ifindex;

  if (0 != bind(_canFd, (struct sockaddr *)&sockAddr, sizeof(sockAddr))) {
    printf("Error: Failed to bind CAN socket \n");
    close(_canFd);
    return false;
  }
  return true;
}

bool osal::CanIface::Start() {
  _isRun.store(true);
  _isStopped.store(false);
  _receiverThread = std::thread(&CanIface::canReceiver, this);
  _receiverThread.detach();
  return true;
}

void osal::CanIface::Stop() {
  _isRun.store(false);
  // Wait for termination of receiver()-Thread
  uint32_t timeCnt = 0;
  while (!_isStopped.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    timeCnt++;
    if (timeCnt > TERMINATION_CAN_RECEIVER_CNT) {
      printf(
          "CanIface::Stop(): No termination response from "
          "canReceive()-Thread\n");
      break;
    }
  }
}

bool osal::CanIface::SendCanMsg(
    IN const osal::types::BufferDescriptor &bufferDesc) {
  osal::types::CanFormat *canMsg =
      (osal::types::CanFormat *)bufferDesc.GetBufferPtr();

  struct can_frame frame;
  frame.can_id = canMsg->u16_identifier;
  frame.can_dlc = canMsg->u8_dlc;
  memcpy(&frame.data, (const void *)&canMsg->au8_data[0], frame.can_dlc);

  auto sent = write(_canFd, &frame, sizeof(frame));
  if (sent != sizeof(frame)) {
    printf("Error: SendCanMsg Wrong amount of byte sent[%zd] \n", sent);
    return false;
  }
  return true;
}

bool osal::CanIface::RegisterCanReceiver(
    IN const std::set<osal::types::CanId> &canIdSet,
    IN ReceiverCallback callback) {
  std::lock_guard<std::mutex> lock(_mutex);
  for (auto it : canIdSet) {
    auto pos = _canIdReceiverCallbackMap.begin();
    auto pair = std::make_pair(it, callback);
    _canIdReceiverCallbackMap.insert(pos, pair);
  }
  return true;
}

bool osal::CanIface::UnRegisterCanReceiver(
    IN const std::set<osal::types::CanId> &canIdSet) {
  std::lock_guard<std::mutex> lock(_mutex);
  // validate canId set
  for (auto it : canIdSet) {
    auto pos = _canIdReceiverCallbackMap.find(it);

    // one of the CanId provided in the canIdset is not registered (unlikely)
    if (pos == _canIdReceiverCallbackMap.end()) {
      printf("Error: Invalid canId provided in un-register request \n");
      return false;
    }
  }

  // un-register the canIdSet
  for (auto it : canIdSet) {
    _canIdReceiverCallbackMap.erase(it);
  }
  return true;
}

void osal::CanIface::canReceiver() {
  osal::types::CanFormat canMsg;
  osal::types::CanId canId;
  while (_isRun.load()) {
    if (receiveCanMsg(canId, canMsg)) {
      _mutex.lock();
      auto pos = _canIdReceiverCallbackMap.find(canId);
      osal::types::BufferDescriptor buffDesc(
          reinterpret_cast<uint8_t *>(&canMsg), sizeof(canMsg));
      pos->second(buffDesc);
      _mutex.unlock();
    }
  }
  _isStopped.store(true);
}

bool osal::CanIface::receiveCanMsg(OUT osal::types::CanId &canId,
                                   OUT osal::types::CanFormat &canMsg) {
  struct can_frame canFrame;

  memset(&canFrame, 0, sizeof(canFrame));
  auto size = read(_canFd, &canFrame, sizeof(canFrame));

  if (size < 0) {
    return false;
  }

  canId = canFrame.can_id;

  _mutex.lock();
  auto pos = _canIdReceiverCallbackMap.find(canId);
  if (pos == _canIdReceiverCallbackMap.end()) {
    _mutex.unlock();
    // can id not registered, drop packet
    return false;
  }
  _mutex.unlock();

  if (0 > size || size != sizeof(canFrame)) {
    printf("Error: Failed to read from socket \n ");
    return false;
  }

  if (canFrame.can_id & CAN_EFF_FLAG) {
    printf("Error: Error set EFF Flag \n");
    return false;
  }

  if (canFrame.can_id & CAN_ERR_FLAG) {
    printf("Error: Error set ERR Flag \n");
    return false;
  }

  if (canFrame.can_id & CAN_RTR_FLAG) {
    printf("Error: Error set RTR Flag \n");
    return false;
  }

  if (canFrame.can_dlc > CAN_DATA_LEN_MAX || canFrame.can_dlc > CAN_MAX_DLEN) {
    printf("Error: The frame size is too high \n");
    return false;
  }
  canMsg.u16_identifier = canId;
  canMsg.u8_dlc = canFrame.can_dlc;
  memcpy(&canMsg.au8_data[0], &canFrame.data[0], canMsg.u8_dlc);

  return true;
}
