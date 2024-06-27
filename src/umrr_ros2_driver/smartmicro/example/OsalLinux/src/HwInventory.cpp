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
#include <Utils.h>

using namespace osal;
using namespace types;
const uint16_t REQ_HWINV_CONFIG_MAJORVER = 1;
const uint16_t REQ_HWINV_CONFIG_MINORVER = 0;
const uint16_t REQ_HWINV_CONFIG_PATCHVER = 0;

std::shared_ptr<HwInventory> HwInventory::_instance;

HwInventory::HwInventory()
    : _hwConfigMajorVersion(0),
      _hwConfigMinorVersion(0),
      _hwConfigPatchVersion(0) {}

HwInventory::~HwInventory() {}

bool HwInventory::ParseHwInventory() {
  cJSON* json = parseJsonFile();
  if (NULL == json) {
    printf("Error: Failed to parse HW Inventory \n");
    return false;
  }

  // Check for valid HW Inventory version
  cJSON* versionInfo = cJSON_GetObjectItem(json, "version");
  if (nullptr != versionInfo) {
    std::string libVersionStr = versionInfo->valuestring;
    if (!OSALUtils::ExtractVersionInfo(libVersionStr, _hwConfigMajorVersion,
                                       _hwConfigMinorVersion,
                                       _hwConfigPatchVersion)) {
      printf("Error: HW Inventory version is not in required format\n");
      cJSON_Delete(json);
      return false;
    }
    if ((REQ_HWINV_CONFIG_MAJORVER != _hwConfigMajorVersion) ||
        (REQ_HWINV_CONFIG_MINORVER > _hwConfigMinorVersion)) {
      printf("Error: HW Inventory version mismatch\n");
      cJSON_Delete(json);
      return false;
    }
  } else {
    printf("Error : version info not available in HW inventory\n");
    cJSON_Delete(json);
    return false;
  }

  // Get HW Inventory items
  cJSON* hwItems = cJSON_GetObjectItem(json, "hwItems");
  if (NULL == hwItems) {
    printf("Error: Failed get hwItems list \n ");
    cJSON_Delete(json);
    return false;
  }

  _hwIfList.clear();

  int8_t size = cJSON_GetArraySize(hwItems);

  for (auto index = 0; index < size; index++) {
    cJSON* hwItem = cJSON_GetArrayItem(hwItems, index);
    if (NULL == hwItem) {
      printf("Error: Failed to get json hwItem \n");
      cJSON_Delete(json);
      return false;
    }

    cJSON* tmp = cJSON_GetObjectItem(hwItem, "type");
    if (NULL == tmp) {
      printf("Error: Failed get hwItem type \n");
      cJSON_Delete(json);
      return false;
    }

    std::string hwItemType(cJSON_GetStringValue(tmp));

    if (0 == hwItemType.compare("can")) {
      if (!parseCanDev(hwItem)) {
        printf("Error: Failed get can item \n ");
        cJSON_Delete(json);
        return false;
      }
    } else if (0 == hwItemType.compare("eth")) {
      if (!parseEthDev(hwItem)) {
        printf("Error: Failed get eth item \n");
        cJSON_Delete(json);
        return false;
      }
    } else if (0 == hwItemType.compare("rs485")) {
      if (!parseRs485Dev(hwItem)) {
        printf("Error: Failed get rs485 item \n");
        cJSON_Delete(json);
        return false;
      }
    } else {
      printf("Error: Obtained Undefined type hwItem \n");
      cJSON_Delete(json);
      return false;
    }
  }
  cJSON_Delete(json);
  return true;
}

cJSON* HwInventory::parseJsonFile() {
  // Get size of hwInventory data
  struct stat fileStat;
  if (0 != stat(_hwInventory.c_str(), &fileStat)) {
    printf("Error: File %s not found \n", _hwInventory.c_str());
    return NULL;
  }
  int size = fileStat.st_size;

  // Read hwInventory-Data into buffer
  // Create Buffer for file data + string termination '\0'
  char* buf = new char[size + 1];
  buf[size] = '\0';
  FILE* file = fopen(_hwInventory.c_str(), "rt");
  if (NULL == file) {
    printf("Error: Failed to open file %s \n", _hwInventory.c_str());
    delete[] buf;
    return NULL;
  }
  if (1 != fread(buf, fileStat.st_size, 1, file)) {
    printf("Error: Failed to read file %s \n", _hwInventory.c_str());
    delete[] buf;
    fclose(file);
    return NULL;
  }

  // Parsing cJSON-Data copied into buffer
  cJSON* result = cJSON_Parse(buf);
  if (NULL == result) {
    printf("Error: Failed to parse json file %s\n", _hwInventory.c_str());
  }
  delete[] buf;
  fclose(file);
  return result;
}

bool HwInventory::GetHwIfList(
    std::list<std::shared_ptr<HwIfaceDescriptor>>& hwIfList) {
  std::copy(_hwIfList.begin(), _hwIfList.end(), std::back_inserter(hwIfList));
  return true;
}

bool HwInventory::parseCanDev(IN cJSON* hwItem) {
  auto tmp = cJSON_GetObjectItem(hwItem, "dev_id");
  if (NULL == tmp) {
    printf("Error: Failed get dev Id \n");
    return false;
  }

  auto tmpDeviceId = cJSON_GetNumberValue(tmp);
  CanDevId deviceId(OSALUtils::CastExplicitDoubleToInt(tmpDeviceId));

  tmp = cJSON_GetObjectItem(hwItem, "iface_name");
  if (NULL == tmp) {
    printf("Error: Failed get iface name \n");
    return false;
  }
  std::string ifName(cJSON_GetStringValue(tmp));

  tmp = cJSON_GetObjectItem(hwItem, "baudrate");
  if (NULL == tmp) {
    printf("Error: Failed get Baudrate type \n");
    return false;
  }
  auto tmpBaudRate = cJSON_GetNumberValue(tmp);
  uint32_t baudrate(OSALUtils::CastExplicitDoubleToInt(tmpBaudRate));

  _hwIfList.push_back(std::shared_ptr<HwCanDescriptor>(
      new HwCanDescriptor(deviceId, ifName, baudrate)));

  return true;
}

bool HwInventory::parseRs485Dev(IN cJSON* hwItem) {
  auto tmp = cJSON_GetObjectItem(hwItem, "dev_id");
  if (NULL == tmp) {
    printf("Error: Failed get dev Id \n");
    return false;
  }

  auto tmpDeviceId = cJSON_GetNumberValue(tmp);
  SerialDevId deviceId(OSALUtils::CastExplicitDoubleToInt(tmpDeviceId));

  tmp = cJSON_GetObjectItem(hwItem, "iface_name");
  if (NULL == tmp) {
    printf("Error: Failed get iface name \n");
    return false;
  }
  std::string ifName(cJSON_GetStringValue(tmp));

  tmp = cJSON_GetObjectItem(hwItem, "baudrate");
  if (NULL == tmp) {
    printf("Error: Failed get Baudrate type \n");
    return false;
  }
  auto tmpBaudRate = cJSON_GetNumberValue(tmp);
  uint32_t baudrate(OSALUtils::CastExplicitDoubleToInt(tmpBaudRate));

  _hwIfList.push_back(std::shared_ptr<HwRS485Descriptor>(
      new HwRS485Descriptor(deviceId, ifName, baudrate)));
  return true;
}

bool HwInventory::parseEthDev(IN cJSON* hwItem) {
  auto tmp = cJSON_GetObjectItem(hwItem, "dev_id");
  if (NULL == tmp) {
    printf("Error: Failed get id \n");
    return false;
  }
  auto tmpDeviceId = cJSON_GetNumberValue(tmp);
  uint16_t devId(OSALUtils::CastExplicitDoubleToInt(tmpDeviceId));

  tmp = cJSON_GetObjectItem(hwItem, "iface_name");
  if (NULL == tmp) {
    printf("Error: Failed get iface name\n");
    return false;
  }

  std::string ifaceName(cJSON_GetStringValue(tmp));

  tmp = cJSON_GetObjectItem(hwItem, "port");
  if (NULL == tmp) {
    printf("Error: Failed get port \n");
    return false;
  }
  auto tmpPort = cJSON_GetNumberValue(tmp);
  uint16_t port(OSALUtils::CastExplicitDoubleToInt(tmpPort));
  // the ip address will extracted from the eth interface
  _hwIfList.push_back(std::shared_ptr<HwEthernetDescriptor>(
      new HwEthernetDescriptor(devId, ifaceName, "no_ip", port)));
  return true;
}
