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
#include <iostream>

using namespace osal::types;
using namespace osal;

const std::string HW_INVENTORY_FILE = "hw_inventory.json";

static std::shared_ptr<OSALImpl> instance;

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
  _hwPropList.clear();
}

bool OSALImpl::Init(const std::string &configPath) {
  // create hw inventory instance
  _hwInventory = HwInventory::GetInstance();
  if (!_hwInventory) {
    printf("_hwInventory is null \n");
    return false;
  }
  // parse the hardware inventory file
  std::string hwInventPath(configPath + "\\" + HW_INVENTORY_FILE);
  _hwInventory->SetHwInventory(hwInventPath);
  if (!_hwInventory->ParseHwInventory()) {
    printf("Failed to init hw inventory \n");
    return false;
  }
  // Init each device in the hardware list
  _hwInventory->GetHwIfInternList(_hwPropList);
  for (auto it : _hwPropList) {
    switch (it->GetHwIfaceType()) {
    // init rs485 devcie
    case HW_IFACE_RS485: {
      if (!createRs485Device(it)) {
        printf("Failed to create and init rs485 device \n");
        return false;
      }
    } break;
    // init ethernet device
    case HW_IFACE_ETH: {
      if (!createEthDevice(it)) {
        printf("Failed to create and init the ethernet device \n");
        return false;
      }
    } break;
    default:
      printf("hardware interface is not supported \n");
      return false;
      break;
    }
  }
  return true;
}

bool OSALImpl::GetHwIfaces(
    OUT std::list<std::shared_ptr<HwIfaceDescriptor>> &hwIfList) {
  return _hwInventory->GetHwIfList(hwIfList);
}

ErrorCode OSALImpl::RegisterReceiver(IN const HwRegistry &registry,
                                     IN ReceiverCallback callback) {
  ErrorCode returnCode = ERROR_CODE_OK;

  switch (registry.GetHwType()) {
  case HW_IFACE_RS485: {
    // cast rs485 hardware registry
    const Rs485HwRegistry &rs485HwRegistry =
        dynamic_cast<const Rs485HwRegistry &>(registry);
    // finde the device interface
    auto pos = _rs485InstMap.find(rs485HwRegistry.GetDevId());
    if (pos == _rs485InstMap.end()) {
      printf("The rs485 device is not registered \n");
      returnCode = ERROR_CODE_REGISTRATION_ERROR;
    } else {
      // register callback
      bool status = pos->second->RegisterCallback(registry, callback);
      if (!status) {
        returnCode = ERROR_CODE_GENERIC_ERROR;
      }
    }
  } break;
  case HW_IFACE_ETH: {
    // cast ethernet hardware registry
    const EthernetRegistry &ethHwRegistry =
        dynamic_cast<const EthernetRegistry &>(registry);
    EthTransportType protoType = ethHwRegistry.GetTransType();
    switch (protoType) {
    case ETH_TRANSPORT_TYPE_UDP: {
      // register callback
      bool status = _ethInst->RegisterReceiver(ethHwRegistry.GetIp(), callback);
      if (!status) {
        returnCode = ERROR_CODE_GENERIC_ERROR;
      }
    } break;
    case ETH_TRANSPORT_TYPE_MULTICAST: {
      std::shared_ptr<MulticastIface> multiIface(
          new MulticastIface(ethHwRegistry.GetIp(), ethHwRegistry.GetPort(),
                             _ethInst->GetRxIpAddr()));
      if (multiIface->Init()) {
        printf("Multicast init OK \n");
        if (multiIface->Start()) {
          if (_multicastMap.find(ethHwRegistry.GetIp()) !=
              _multicastMap.end()) {
            returnCode = ERROR_CODE_REGISTRATION_ERROR;
            printf("Multicast registration error \n");
          } else {
            _multicastMap.insert(
                std::pair<std::string, std::shared_ptr<MulticastIface>>(
                    ethHwRegistry.GetIp(), multiIface));
            if (!multiIface->RegisterReceiver(ethHwRegistry.GetIp(),
                                              callback)) {
              returnCode = ERROR_CODE_REGISTRATION_ERROR;
              printf("Multicast registration receiver error \n");
            }
          }
        }
      } else {
        printf("Failed to init multicast iface \n");
        returnCode = ERROR_CODE_REGISTRATION_ERROR;
      }
    } break;
    default:
      returnCode = ERROR_CODE_REGISTRATION_ERROR;
      break;
    }
  } break;
  default:
    break;
  }
  return returnCode;
}

ErrorCode OSALImpl::UnRegisterReceiver(IN const HwRegistry &registry) {
  ErrorCode returnCode = ERROR_CODE_OK;

  switch (registry.GetHwType()) {
  case HW_IFACE_RS485: {
    // cast rs485 hardware registry
    const Rs485HwRegistry &rs485HwRegistry =
        dynamic_cast<const Rs485HwRegistry &>(registry);
    // finde the device interface
    auto pos = _rs485InstMap.find(rs485HwRegistry.GetDevId());
    if (pos == _rs485InstMap.end()) {
      returnCode = ERROR_CODE_REGISTRATION_ERROR;
    } else {
      bool status = pos->second->UnRegisterReceiver(registry);
      if (!status) {
        returnCode = ERROR_CODE_GENERIC_ERROR;
      }
    }
  } break;
  case HW_IFACE_ETH: {
    // cast ethernet hardware registry
    const EthernetRegistry &ethHwRegistry =
        dynamic_cast<const EthernetRegistry &>(registry);

    bool status = _ethInst->UnRegisterReceiver(ethHwRegistry.GetIp());
    if (!status) {
      returnCode = ERROR_CODE_GENERIC_ERROR;
    }

  } break;
  default:
    break;
  }
  return returnCode;
}

ErrorCode OSALImpl::SendData(IN const HwRegistry &registry,
                             IN const BufferDescriptor &bufferDesc) {
  ErrorCode returnCode = ERROR_CODE_OK;

  switch (registry.GetHwType()) {
  case HW_IFACE_RS485: {
    // cast rs485 hardware registry
    const Rs485HwRegistry &rs485HwRegistry =
        dynamic_cast<const Rs485HwRegistry &>(registry);
    // finde the device interface
    auto pos = _rs485InstMap.find(rs485HwRegistry.GetDevId());
    if (pos == _rs485InstMap.end()) {
      returnCode = ERROR_CODE_REGISTRATION_ERROR;
    } else {
      bool status = pos->second->SendData(registry, bufferDesc);
      if (!status) {
        returnCode = ERROR_CODE_GENERIC_ERROR;
      }
    }
  } break;
  case HW_IFACE_ETH: {
    // cast ethernet hardware registry
    const EthernetRegistry &ethHwRegistry =
        dynamic_cast<const EthernetRegistry &>(registry);
    ErrorCode retVal = ERROR_CODE_GENERIC_ERROR;
    switch (ethHwRegistry.GetTransType()) {
    case ETH_TRANSPORT_TYPE_UDP: {
      bool status = _ethInst->SendData(ethHwRegistry.GetIp(),
                                       ethHwRegistry.GetPort(), bufferDesc);
      if (!status) {
        returnCode = ERROR_CODE_GENERIC_ERROR;
      }
    } break;
    case ETH_TRANSPORT_TYPE_MULTICAST: {
      auto it = _multicastMap.find(ethHwRegistry.GetIp());
      if (it != _multicastMap.end()) {
        if (it->second->SendData(ethHwRegistry.GetIp(), ethHwRegistry.GetPort(),
                                 bufferDesc)) {
          retVal = ERROR_CODE_OK;
        }
      }
    } break;
    default:
      printf("Unknown iface [%s:%u] \n", ethHwRegistry.GetIp().c_str(),
             ethHwRegistry.GetPort());
      break;
    }
  } break;
  default:
    break;
  }
  return returnCode;
}

bool OSALImpl::createRs485Device(IN std::shared_ptr<HwProperty> desc) {
  bool returnValue = true;
  if (desc) {
    // create rs485 instanz
    std::unique_ptr<Rs485Inst> rs485Inst(new Rs485Inst());
    // ini the device
    if (rs485Inst->Init(desc)) {
      // add the rs485 device with the device id to the map
      SerialDevId devId = std::stoi(desc->GetDeviceId());
      _rs485InstMap.insert(std::make_pair(devId, std::move(rs485Inst)));
    } else {
      printf("Failed to init osal rs485 device \n");
      returnValue = false;
    }
  }
  return returnValue;
}

bool OSALImpl::createEthDevice(IN std::shared_ptr<HwProperty> desc) {
  bool returnValue = true;
  if (desc) {
    // create ethernet instanz
    std::shared_ptr<UdpIface> ethInst(
        new UdpIface(desc->GetIpAddress(), std::stoi(desc->GetUsedPort())));
    // init the ethernet device
    if (ethInst->Init()) {
      _ethInst = ethInst;
    } else {
      printf("Failed to init osal ethernet device \n");
      returnValue = false;
    }
    if (returnValue) {
      ethInst->Start();
    }
  }
  return returnValue;
}
