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
#include <HwInventory.h>

using namespace osal::types;
using namespace osal;

std::shared_ptr<HwInventory> HwInventory::_instance;

HwInventory::HwInventory() {}

HwInventory::~HwInventory() {}

void HwInventory::SetHwInventory(IN const std::string &fileName) {
  _hwInventory.assign(fileName);
}

bool HwInventory::ParseHwInventory() {
  // parse the hardware config
  cJSON *json = parseJsonFile();
  if (NULL == json) {
    printf("Failed to parse HW Inventory %s \n", _hwInventory.c_str());
    return false;
  }

  // clear the hardware list and fill the list with new hardware
  // config in the next steps
  _hwInstList.clear();
  // get all hardware items
  cJSON *hwItems = cJSON_GetObjectItem(json, "hwItems");
  if (NULL == hwItems) {
    printf("Failed get hwItems list \n");
    cJSON_Delete(json);
    return false;
  }
  // number of devices
  int8_t size = cJSON_GetArraySize(hwItems);
  // read each device configuration
  for (auto index = 0; index < size; index++) {
    // get the device
    cJSON *hwItem = cJSON_GetArrayItem(hwItems, index);
    if (NULL == hwItem) {
      printf("Failed to get json hwItem \n");
      cJSON_Delete(json);
      return false;
    }
    // read the device type
    std::string hwItemType = getItem(hwItem, "type");
    if ("" == hwItemType) {
      printf("Failed get hwItem type \n");
      cJSON_Delete(json);
      return false;
    }
    // if it is can device, read the can configuration
    if (0 == hwItemType.compare("can")) {
      if (!parseCanDev(hwItem)) {
        printf("Failed get can item \n");
        cJSON_Delete(json);
        return false;
      }
    }
    // if it is ethernet device, read the ethernet configuration
    else if (0 == hwItemType.compare("eth")) {
      if (!parseEthDev(hwItem)) {
        printf("Failed get eth item \n");
        cJSON_Delete(json);
        return false;
      }
    }
    // if it is rs485 device, read the rs485 configuration
    else if (0 == hwItemType.compare("rs485")) {
      if (!parseRs485Dev(hwItem)) {
        printf("Failed get rs485 item \n");
        cJSON_Delete(json);
        return false;
      }
    }
    // the device type is not supported or undefined
    else {
      printf("Obtained Undefined type hwItem \n");
      cJSON_Delete(json);
      return false;
    }
  }
  cJSON_Delete(json);
  return true;
}

cJSON *HwInventory::parseJsonFile() {
  struct stat fileStat;
  /* Check if a file exists */
  if (0 != stat(_hwInventory.c_str(), &fileStat)) {
    printf("File %s not found \n", _hwInventory.c_str());
    return NULL;
  }
  char *buf = new char[fileStat.st_size];
  FILE *file;
  /* open the hardware config file */
  errno_t err = fopen_s(&file, _hwInventory.c_str(), "r+");
  /* evaluate the status from fopen */
  if (err != 0) {
    printf("Failed to open file %s \n", _hwInventory.c_str());
    delete[] buf;
    return NULL;
  }
  /* read the file */
  fread(buf, fileStat.st_size, 1, file);
  // pars the config file
  cJSON *result = cJSON_Parse(buf);
  if (NULL == result) {
    printf("Failed to parse json \n");
  }
  delete[] buf;
  fclose(file);
  // return: parsed file
  return result;
}

bool HwInventory::GetHwIfList(
    std::list<std::shared_ptr<HwIfaceDescriptor>> &hwIfList) {
  // copy the hardware list
  std::copy(_hwIfOsalList.begin(), _hwIfOsalList.end(),
            std::back_inserter(hwIfList));
  return true;
}

bool HwInventory::GetHwIfInternList(
    std::list<std::shared_ptr<HwProperty>> &hwIfList) {
  // copy the hardware list
  std::copy(_hwInstList.begin(), _hwInstList.end(),
            std::back_inserter(hwIfList));
  return true;
}

bool HwInventory::parseCanDev(IN cJSON *hwItem) {
  bool retValue = true;
  /* read device id */
  std::string deviceId = getItem(hwItem, "deviceId");
  if ("" == deviceId) {
    printf("Failed get can deviceId \n");
    retValue = false;
  } else {
    /* read link speed */
    std::string linkSpeed = getItem(hwItem, "linkSpeed");
    if ("" == linkSpeed) {
      printf("Failed get can linkSpeed \n");
      retValue = false;
    } else {
      /* read device type */
      std::string deviceType = getItem(hwItem, "deviceType");
      if ("" == deviceType) {
        printf("Failed get can deviceType \n");
        retValue = false;
      } else {
        /* read device supplier */
        std::string deviceSup = getItem(hwItem, "deviceSupplier");
        if ("" == deviceSup) {
          printf("Failed get can deviceSupplier \n");
          retValue = false;
        } else {
          /* create can property */
          std::shared_ptr<HwProperty> canProp =
              std::make_shared<HwProperty>(HW_IFACE_CAN);
          canProp->SetDeviceId(deviceId);
          canProp->SetLinkSpeed(linkSpeed);
          canProp->SetDevType(deviceType);
          canProp->SetDevSupplier(deviceSup);
          /* add can property to hardware instruction list */
          _hwInstList.push_back(canProp);
          _hwIfOsalList.push_back(
              std::shared_ptr<HwCanDescriptor>(new HwCanDescriptor(
                  std::stoi(deviceId), deviceType, std::stoi(linkSpeed))));
        }
      }
    }
  }
  return retValue;
}

bool HwInventory::parseRs485Dev(IN cJSON *hwItem) {
  bool retValue = true;
  /* read device id */
  std::string deviceId = getItem(hwItem, "deviceId");
  if ("" == deviceId) {
    printf("Failed get rs485 deviceId \n");
    retValue = false;
  } else {
    /* read link speed */
    std::string linkSpeed = getItem(hwItem, "linkSpeed");
    if ("" == linkSpeed) {
      printf("Failed get rs485 linkSpeed \n");
      retValue = false;
    } else {
      /* read used port */
      std::string usedPort = getItem(hwItem, "usedPort");
      if ("" == usedPort) {
        printf("Failed get ethernet usedPort \n");
        retValue = false;
      } else {
        /* create rs485 property */
        std::shared_ptr<HwProperty> rs485Prop =
            std::make_shared<HwProperty>(HW_IFACE_RS485);
        rs485Prop->SetDeviceId(deviceId);
        rs485Prop->SetLinkSpeed(linkSpeed);
        rs485Prop->SetUsedPort(usedPort);
        /* add rs485 property to hardware instruction list */
        _hwInstList.push_back(rs485Prop);
        _hwIfOsalList.push_back(
            std::shared_ptr<HwRS485Descriptor>(new HwRS485Descriptor(
                std::stoi(deviceId), usedPort, std::stoi(linkSpeed))));
      }
    }
  }
  return retValue;
}

bool HwInventory::parseEthDev(IN cJSON *hwItem) {
  bool retValue = true;
  /* read device id */
  std::string deviceId = getItem(hwItem, "deviceId");
  if ("" == deviceId) {
    printf("Failed get ethernet deviceId \n");
    retValue = false;
  } else {
    /* read link speed */
    std::string ipAddres = getItem(hwItem, "ipAddress");
    if ("" == ipAddres) {
      printf("Failed get ethernet ipAddress \n");
      retValue = false;
    } else {
      /* read used port */
      std::string usedPort = getItem(hwItem, "usedPort");
      if ("" == usedPort) {
        printf("Failed get ethernet usedPort \n");
        retValue = false;
      } else {
        /* create ethernet property */
        std::shared_ptr<HwProperty> ethProp =
            std::make_shared<HwProperty>(HW_IFACE_ETH);
        ethProp->SetDeviceId(deviceId);
        ethProp->SetIpAddress(ipAddres);
        ethProp->SetUsedPort(usedPort);
        /* add ethernet property to hardware instruction list */
        _hwInstList.push_back(ethProp);
        _hwIfOsalList.push_back(
            std::shared_ptr<HwEthernetDescriptor>(new HwEthernetDescriptor(
                std::stoi(deviceId), ipAddres, ipAddres, std::stoi(usedPort))));
      }
    }
  }
  return retValue;
}

std::string HwInventory::getItem(IN cJSON *hwItem, IN const char *searchItem) {
  std::string returnItem = "";
  /* search item in item from json file */
  auto tmp = cJSON_GetObjectItem(hwItem, searchItem);
  /* item exist */
  if (NULL != tmp) {
    /* convert item to string */
    returnItem = cJSON_GetStringValue(tmp);
  }
  return returnItem;
}

std::shared_ptr<HwInventory> HwInventory::GetInstance() {
  if (!_instance) {
    _instance.reset(new HwInventory);
  }
  return _instance;
}
