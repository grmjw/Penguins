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
/**
 * @addtogroup osal
 * @{
 *
 * @file HwInventory.h
 *
 * @brief Parses hardware inventory file to get all hw devices.
 *
 */

#ifndef HWINVENTORY_H_
#define HWINVENTORY_H_

#define _FILE_OFFSET_BITS 64

#include <OSALIface.h>
#include <OSALTypes.h>
#include <cjson/cJSON.h>
#include <sys/stat.h>

#include <list>
#include <map>
#include <memory>
#include <string>

namespace osal {
/*
 * Hardware inventory class
 */
class HwInventory {
 public:
  /**
   * @brief Returns hardware inventory instance.
   *
   * @returns returns instance of hardware inventory.
   */
  static std::shared_ptr<HwInventory> GetInstance() {
    if (!_instance) {
      _instance.reset(new HwInventory);
    }
    return _instance;
  }

  /* destructor */
  virtual ~HwInventory();

  /**
   * @brief Sets hardware inventory file path.
   *
   * @param  [in] fileName     path to the hardware inventory file.
   * @param  [in] fileName     path to the hardware inventory file.
   * @param  [in] fileName     path to the hardware inventory file.
   * @param  [in] fileName     path to the hardware inventory file.
   * @param  [in] fileName     path to the hardware inventory file.
   */
  inline void SetHwInventory(IN const std::string& fileName) {
    _hwInventory.assign(fileName);
  }

  /**
   * @brief Parses hardware inventory file.
   *
   *
   *
   *
   *
   * Parses the hardware inventory file and creates hardware instanz list.
   *
   * @returns True if successful, false if failed.
   */
  bool ParseHwInventory();
  /**
   * @brief Returns hardware interfaces and those configuration.
   *
   *
   *
   *
   *
   * @param  [out] hwIfList     list with hardware interfaces for the com lib.
   *
   * @returns True if successful, false if failed.
   */
  bool GetHwIfList(
      OUT std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>>& hwIfList);

 private:
  HwInventory();

  cJSON* parseJsonFile();
  bool parseCanDev(IN cJSON* hwItem);
  bool parseEthDev(IN cJSON* hwItem);
  bool parseRs485Dev(IN cJSON* hwItem);

  std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>> _hwIfList;
  std::string _hwInventory;
  static std::shared_ptr<HwInventory> _instance;
  uint16_t _hwConfigMajorVersion;
  uint16_t _hwConfigMinorVersion;
  uint16_t _hwConfigPatchVersion;
};

}  // namespace osal

#endif  // HWINVENTORY_H_
