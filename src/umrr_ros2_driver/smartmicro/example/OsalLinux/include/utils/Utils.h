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

#ifndef UTILS__UTILS_H_
#define UTILS__UTILS_H_

#include <iostream>
#include <regex>
#include <string>

class OSALUtils {
 public:
  static uint32_t CastExplicitDoubleToInt(double& inVal);
  static bool ExtractVersionInfo(const std::string& SemanticVersion,
                                 uint16_t& majorVer, uint16_t& minorVer,
                                 uint16_t& patchVer);
};

#endif  // UTILS__UTILS_H_
