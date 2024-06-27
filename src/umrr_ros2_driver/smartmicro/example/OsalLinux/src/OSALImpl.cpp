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
#include <OSALImpl.h>
#include <can/CanIface.h>
#include <ethernet/MulticastIface.h>
#include <ethernet/UdpIface.h>
#include <rs485/Rs485Iface.h>
#include <unistd.h>

#include <iostream>

#define OSAL_CAN_ID_START 0
const std::string HW_INVENTORY_FILE = "hw_inventory.json";

using namespace osal;
using namespace osal::types;

static std::shared_ptr<OSALImpl> instance;
// Singelton function
std::shared_ptr<OSALIface> OSALIface::GetOSAL() {
  if (!instance) {
    instance.reset(new OSALImpl());
  }
  return instance;
}

OSALImpl::OSALImpl() {}

OSALImpl::~OSALImpl() {
  if (instance) {
    instance.reset();
  }
}

bool OSALImpl::Init(const std::string& configPath) {
  _hwInventory = HwInventory::GetInstance();
  if (!_hwInventory) {
    printf("Error: _hwInventory is null \n");
    return false;
  }
  std::string hwInventPath(configPath + "/" + HW_INVENTORY_FILE);
  _hwInventory->SetHwInventory(hwInventPath);
  // Parsing HW inventory
  if (!_hwInventory->ParseHwInventory()) {
    printf("Error: Failed to init hw inventory \n");
    return false;
  }
  // Get all hw devices
  _hwInventory->GetHwIfList(_hwIfList);
  // create hw interfaces
  for (auto it : _hwIfList) {
    switch (it->GetHwIfaceType()) {
      case HW_IFACE_CAN: {
        auto hwCanDesc = std::dynamic_pointer_cast<HwCanDescriptor>(it);
        // create CAN Interface
        if (!createCanIface(hwCanDesc)) {
          printf("Error: Failed to create and init can iface \n");
          return false;
        }
      } break;
      case HW_IFACE_RS485: {
        auto hwRs485Desc = std::dynamic_pointer_cast<HwRS485Descriptor>(it);
        // create RS485 Interface
        if (!createRs485Iface(hwRs485Desc)) {
          printf("Error: Failed to create and init rs485 iface \n");
          return false;
        }
      } break;
      case HW_IFACE_ETH: {
        auto ethDesc = std::dynamic_pointer_cast<HwEthernetDescriptor>(it);
        // create UDP Interface
        if (!createUdpIface(ethDesc)) {
          printf("Error: Failed to create and init ethernet iface \n");
          return false;
        }
      } break;
      default:
        break;
    }
  }
  return true;
}

bool OSALImpl::GetHwIfaces(
    OUT std::list<std::shared_ptr<HwIfaceDescriptor>>& hwIfList) {
  return _hwInventory->GetHwIfList(hwIfList);
}

ErrorCode OSALImpl::RegisterReceiver(IN const HwRegistry& registry,
                                     IN ReceiverCallback callback) {
  ErrorCode retVal = ERROR_CODE_OK;
  switch (registry.GetHwType()) {
    case HW_IFACE_CAN: {
      const CanHwRegistry* canRegistry =
          dynamic_cast<const CanHwRegistry*>(&registry);
      retVal = registerCanReceiver(canRegistry->GetIds(),
                                   canRegistry->GetDevId(), callback);
    } break;
    case HW_IFACE_RS485: {
      const Rs485HwRegistry* rs485Registry =
          dynamic_cast<const Rs485HwRegistry*>(&registry);
      retVal = registerRS485Receiver(rs485Registry->GetDevId(), callback);
    } break;
    case HW_IFACE_ETH: {
      const EthernetRegistry* ethRegistry =
          dynamic_cast<const EthernetRegistry*>(&registry);
      retVal = registerEthernetReceiver(ethRegistry->GetIp(),
                                        ethRegistry->GetTransType(),
                                        ethRegistry->GetPort(), callback);
    } break;
  }
  return retVal;
}
ErrorCode OSALImpl::UnRegisterReceiver(IN const HwRegistry& registry) {
  ErrorCode retVal = ERROR_CODE_OK;
  switch (registry.GetHwType()) {
    case HW_IFACE_CAN: {
      const CanHwRegistry* canRegistry =
          dynamic_cast<const CanHwRegistry*>(&registry);
      retVal =
          unregisterCanReceiver(canRegistry->GetIds(), canRegistry->GetDevId());
    } break;
    case HW_IFACE_RS485: {
      const Rs485HwRegistry* rs485Registry =
          dynamic_cast<const Rs485HwRegistry*>(&registry);
      retVal = unregisterRS485Receiver(rs485Registry->GetDevId());
    } break;
    case HW_IFACE_ETH: {
      const EthernetRegistry* ethRegistry =
          dynamic_cast<const EthernetRegistry*>(&registry);
      retVal = unegisterEthernetReceiver(ethRegistry->GetIp(),
                                         ethRegistry->GetTransType(),
                                         ethRegistry->GetPort());
    } break;
  }
  return retVal;
}

ErrorCode OSALImpl::SendData(IN const HwRegistry& registry,
                             IN const BufferDescriptor& buffer) {
  ErrorCode retVal = ERROR_CODE_OK;
  switch (registry.GetHwType()) {
    case HW_IFACE_CAN: {
      const CanHwRegistry* canRegistry =
          dynamic_cast<const CanHwRegistry*>(&registry);
      retVal = sendCanMsg(canRegistry->GetDevId(), buffer);
    } break;
    case HW_IFACE_RS485: {
      const Rs485HwRegistry* rs485Registry =
          dynamic_cast<const Rs485HwRegistry*>(&registry);
      retVal = sendRS485Msg(rs485Registry->GetDevId(), buffer);
    } break;
    case HW_IFACE_ETH: {
      const EthernetRegistry* ethRegistry =
          dynamic_cast<const EthernetRegistry*>(&registry);
      retVal = sendEthMsg(ethRegistry->GetIp(), ethRegistry->GetTransType(),
                          ethRegistry->GetPort(), buffer);
    } break;
  }
  return retVal;
}
// CAN-Interface
ErrorCode OSALImpl::registerCanReceiver(IN const std::set<CanId>& canIdset,
                                        IN CanDevId canDeviceId,
                                        IN ReceiverCallback callback) {
  auto pos = _canIfaceMap.find(canDeviceId);
  if (pos == _canIfaceMap.end()) {
    // can device interface doesnt exists
    printf("Error: canDevId does not exist [%u]\n", canDeviceId);
    return ERROR_CODE_REGISTRATION_ERROR;
  } else {
    // Object already exists
    pos->second->RegisterCanReceiver(canIdset, callback);
  }
  return ERROR_CODE_OK;
}

ErrorCode OSALImpl::unregisterCanReceiver(IN const std::set<CanId>& canIdset,
                                          IN CanDevId canDeviceId) {
  auto pos = _canIfaceMap.find(canDeviceId);
  if (pos == _canIfaceMap.end()) {
    // can device id doesnt exist, can't un-register
    printf("Error: canDevId Not registered [%u]\n", canDeviceId);
    return ERROR_CODE_REGISTRATION_ERROR;
  } else {
    // remove canId from registered canDevice
    if (pos->second->UnRegisterCanReceiver(canIdset)) {
      return ERROR_CODE_OK;
    } else {
      return ERROR_CODE_REGISTRATION_ERROR;
    }
  }
}

ErrorCode OSALImpl::sendCanMsg(IN CanDevId canDeviceId,
                               IN const BufferDescriptor& bufferDesc) {
  auto pos = _canIfaceMap.find(canDeviceId);
  if (pos == _canIfaceMap.end()) {
    // CanDevId not registered
    printf("Error: canDevId Not registered [%u]\n", canDeviceId);
    return ERROR_CODE_REGISTRATION_ERROR;
  } else {
    // CanDevId previously registred, Forward msg to CanIf
    pos->second->SendCanMsg(bufferDesc);
  }
  return ERROR_CODE_OK;
}

// Ethernet-Interface
ErrorCode OSALImpl::registerEthernetReceiver(IN const std::string& ip,
                                             IN EthTransportType protoType,
                                             IN uint32_t port,
                                             IN ReceiverCallback callback) {
  ErrorCode retVal = ERROR_CODE_OK;
  EthIfaceKey key(ip, port);
  std::shared_ptr<EthIface> iface;
  switch (protoType) {
    case ETH_TRANSPORT_TYPE_UDP:
      // Udp ifaces are created dutring init , so it shall already exist
      iface = std::dynamic_pointer_cast<EthIface>(_udpIface);
      break;
    case ETH_TRANSPORT_TYPE_MULTICAST: {
      // if udp is supported
      if (_udpIface) {
        std::shared_ptr<MulticastIface> multiIface(
            new MulticastIface(_udpIface->GetIfaceName(), ip, port));
        if (multiIface->Init()) {
          if (multiIface->Start()) {
            if (_multicastMap.find(key) != _multicastMap.end()) {
              retVal = ERROR_CODE_REGISTRATION_ERROR;
            } else {
              _multicastMap.insert(
                  std::pair<EthIfaceKey, std::shared_ptr<MulticastIface>>(
                      key, multiIface));
              iface = std::dynamic_pointer_cast<EthIface>(multiIface);
            }
          }
        } else {
          printf("Error: Failed to init multicast iface \n");
          retVal = ERROR_CODE_REGISTRATION_ERROR;
        }
      } else {
        printf("Error: Failed to unicast iface is defined \n");
        retVal = ERROR_CODE_REGISTRATION_ERROR;
      }
    } break;
    default:
      retVal = ERROR_CODE_REGISTRATION_ERROR;
      break;
  }

  if (ERROR_CODE_OK == retVal) {
    if (!iface->RegisterReceiver(ip, callback)) {
      retVal = ERROR_CODE_REGISTRATION_ERROR;
    }
  }
  return retVal;
}

ErrorCode OSALImpl::sendEthMsg(IN const std::string& ip,
                               IN EthTransportType type, IN uint32_t port,
                               IN const BufferDescriptor& buffer) {
  ErrorCode retVal = ERROR_CODE_GENERIC_ERROR;
  switch (type) {
    case ETH_TRANSPORT_TYPE_UDP:
      if (_udpIface) {
        if (_udpIface->SendData(ip, port, buffer)) {
          retVal = ERROR_CODE_OK;
        }
      } else {
        printf("Error: udp iface is nullptr \n");
      }
      break;
    case ETH_TRANSPORT_TYPE_MULTICAST: {
      EthIfaceKey key(ip, port);
      auto it = _multicastMap.find(key);
      if (it != _multicastMap.end()) {
        if (it->second->SendData(ip, port, buffer)) {
          retVal = ERROR_CODE_OK;
        }
      } else {
        printf("Error: Unknown multicast iface [%s:%u] \n", ip.c_str(), port);
      }
    } break;
    default:
      printf("Error: Unknown iface [%s:%u] \n", ip.c_str(), port);
      break;
  }
  return retVal;
}

// RS485-Interface
ErrorCode OSALImpl::registerRS485Receiver(IN SerialDevId deviceId,
                                          IN ReceiverCallback callback) {
  auto pos = _rs485IfaceMap.find(deviceId);
  if (pos == _rs485IfaceMap.end()) {
    // rs485 device interface doesnt exists
    printf("Error: no device Id %u \n", deviceId);
    return ERROR_CODE_REGISTRATION_ERROR;
  } else {
    // Object already exists
    pos->second->RegisterReceiver(callback);
  }
  return ERROR_CODE_OK;
}

ErrorCode OSALImpl::unregisterRS485Receiver(IN SerialDevId deviceId) {
  auto pos = _rs485IfaceMap.find(deviceId);
  if (pos == _rs485IfaceMap.end()) {
    // rs485 device interface doesnt exists
    printf("Error: no device Id %u \n", deviceId);
    return ERROR_CODE_REGISTRATION_ERROR;
  } else {
    // Object already exists
    pos->second->UnRegisterReceiver();
  }
  return ERROR_CODE_OK;
}

ErrorCode OSALImpl::sendRS485Msg(IN SerialDevId deviceId,
                                 IN const BufferDescriptor& bufferDesc) {
  auto pos = _rs485IfaceMap.find(deviceId);
  if (pos == _rs485IfaceMap.end()) {
    // DevId not registered
    printf("Error: DevId[%u] is not registered \n", deviceId);
    return ERROR_CODE_REGISTRATION_ERROR;
  } else {
    // DevId previously registered, Forward msg to Rs485 Iface
    pos->second->SendMsg(bufferDesc);
  }
  return ERROR_CODE_OK;
}

bool OSALImpl::createCanIface(IN std::shared_ptr<HwCanDescriptor> desc) {
  if (desc) {
    std::unique_ptr<CanIface> canIf(new CanIface(desc->GetCanDeviceId(),
                                                 desc->GetCanIfaceName(),
                                                 desc->GetCanBaudrate()));
    if (canIf->Init()) {
      // Start thread
      canIf->Start();
      _canIfaceMap.insert(
          std::make_pair(desc->GetCanDeviceId(), std::move(canIf)));
      return true;
    } else {
      printf("Error: Failed to init osal can iface \n");
      return false;
    }
  }
  return false;
}

bool OSALImpl::createRs485Iface(IN std::shared_ptr<HwRS485Descriptor> desc) {
  if (desc) {
    std::unique_ptr<Rs485Iface> rs485If(
        new Rs485Iface(desc->GetIfaceName(), desc->GetBaudrate()));
    if (rs485If->Init()) {
      // Start thread
      rs485If->Start();
      _rs485IfaceMap.insert(
          std::make_pair(desc->GetRs485DeviceId(), std::move(rs485If)));
    } else {
      printf("Error: Failed to init osal rs485 iface\n");
      return false;
    }
  }
  return true;
}

bool OSALImpl::createUdpIface(IN std::shared_ptr<HwEthernetDescriptor> desc) {
  bool retVal = true;
  if (desc) {
    std::shared_ptr<UdpIface> udpIf(
        new UdpIface(desc->GetIfaceName(), desc->GetPort()));
    if (udpIf->Init()) {
      if (_udpIface) {
        printf("Error: Only one ETH iface is allowed \n");
        retVal = false;
      } else {
        // Start thread
        if (udpIf->Start()) {
          _udpIface = udpIf;
          desc->SetIp(_udpIface->GetRxIpAddr());
        } else {
          retVal = false;
        }
      }
    } else {
      printf("Error: Failed to init osal udp receiver \n");
      retVal = false;
    }
  } else {
    printf("Error: Descriptor is null \n");
    retVal = false;
  }
  return retVal;
}

ErrorCode OSALImpl::unegisterEthernetReceiver(IN const std::string& ip,
                                              IN EthTransportType protoType,
                                              IN uint32_t port) {
  ErrorCode retVal = ERROR_CODE_OK;
  switch (protoType) {
    case ETH_TRANSPORT_TYPE_UDP:
      if (!_udpIface->UnRegisterReceiver(ip)) {
        retVal = ERROR_CODE_REGISTRATION_ERROR;
      }
      break;
    case ETH_TRANSPORT_TYPE_MULTICAST: {
      EthIfaceKey key(ip, port);
      auto it = _multicastMap.find(key);
      if (it == _multicastMap.end()) {
        retVal = ERROR_CODE_REGISTRATION_ERROR;
      } else {
        if (it->second->UnRegisterReceiver(ip)) {
          _multicastMap.erase(it);
        } else {
          retVal = ERROR_CODE_REGISTRATION_ERROR;
        }
      }
    } break;
    default:
      retVal = ERROR_CODE_REGISTRATION_ERROR;
      break;
  }
  return retVal;
}
