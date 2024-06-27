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
 * @brief Declaration of the hardware inventory
 *
 */
#ifndef COM_COMMON_OSAL_WINDOWS_UTIL_H
#define COM_COMMON_OSAL_WINDOWS_UTIL_H

#include <HwProperty.h>
#include <OSALIface.h>
#include <cjson/cJSON.h>
#include <iterator>
#include <list>
#include <map>
#include <sys/stat.h>

namespace osal {

class HwInventory {
public:
  /* destructor */
  virtual ~HwInventory();

  /**
   * @brief Returns hardware inventory instanz.
   *
   * @returns returns instanz of hardware inventory.
   */
  static std::shared_ptr<HwInventory> GetInstance();

  /**
   * @brief Sets hardware inventory file path.
   *
   * @param  [in] fileName     path to the hardware inventory file.
   */
  void SetHwInventory(IN const std::string &fileName);

  /**
   * @brief Parses hardware inventory file.
   *
   * Parses the hardware inventory file and creates hardware instanz list.
   *
   * @returns True if successful, false if failed.
   */
  bool ParseHwInventory();

  /**
   * @brief Returns hardware interfaces and those configuration.
   *
   * @param  [out] hwIfList     list with hardware interfaces for the com lib.
   *
   * @returns True if successful, false if failed.
   */
  bool GetHwIfList(
      OUT std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>> &hwIfList);

  /**
   * @brief Returns hardware interfaces and those configuration.
   *
   * @param  [out] hwIfList     list with hardware interfaces for the internal
   * handling.
   *
   * @returns True if successful, false if failed.
   */
  bool GetHwIfInternList(OUT std::list<std::shared_ptr<HwProperty>> &hwIfList);

private:
  HwInventory();

  /**
   * @brief Read the json file.
   *
   * @param  [IN] hwItem   hardware item from the json file.
   *
   * @returns The parsed json file .
   */
  cJSON *parseJsonFile();

  /**
   * @brief Parse the can configuration from the hardware json file.
   *
   * @param  [IN] hwItem   hardware item from the json file.
   *
   * @returns True if successful, false if failed.
   */
  bool parseCanDev(IN cJSON *hwItem);

  /**
   * @brief Parse the eth configuration from the hardware json file.
   *
   * @param  [IN] hwItem   hardware item from the json file.
   *
   * @returns True if successful, false if failed.
   */
  bool parseEthDev(IN cJSON *hwItem);

  /**
   * @brief Parse the rs485 configuration from the hardware json file.
   *
   * @param  [IN] hwItem   hardware item from the json file.
   *
   * @returns True if successful, false if failed.
   */
  bool parseRs485Dev(IN cJSON *hwItem);

  /**
   * @brief Read a item from the parsed json file.
   *
   * @param  [IN] item  parsed json section.
   *
   * @param  [IN] searchItem  searched key.
   *
   * @returns
   */
  std::string getItem(IN cJSON *item, IN const char *searchItem);

  std::list<std::shared_ptr<HwProperty>> _hwInstList;
  std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>> _hwIfOsalList;
  std::string _hwInventory;
  static std::shared_ptr<HwInventory> _instance;
};

} // namespace osal

#endif
