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

#include <Utils.h>

// Implicit/Explicit Conversion-Proof function due to cJSON/Compilers
// misbehaviour
uint32_t OSALUtils::CastExplicitDoubleToInt(double& inVal) {
  uint32_t outValImpl;
  // If inVal is in right format (non-zero Implicit converstion check)
  if (inVal) {
    // try implicit conversion
    outValImpl = inVal;
    // if implicit converstion succesful
    if (outValImpl) {
      return outValImpl;
    }
    // non-zero Converstion failed
  }

  // if non-zero implicit converstion is not succesful, or zero inVal
  uint32_t* outValExpl;
  outValExpl = reinterpret_cast<uint32_t*>(&inVal);
  if (*outValExpl) {
    // non-zero Explicity Converstion succesfuly
    return *outValExpl;
  }

  // Zero/Non-Zero Implicit Converstion, the normal case
  outValImpl = inVal;
  return outValImpl;
}

bool OSALUtils::ExtractVersionInfo(const std::string& semanticVersion,
                                   uint16_t& majorVer, uint16_t& minorVer,
                                   uint16_t& patchVer) {
  const uint8_t MIN_FIELDS = 3;
  uint16_t VersionInfo[MIN_FIELDS];
  uint8_t versionIndex = 0;
  std::regex regExprVersion(
      "(0|[1-9][0-9]*)\\.(0|[1-9][0-9]*)\\.(0|[1-9][0-9]*)");
  if (!std::regex_match(semanticVersion, regExprVersion)) {
    printf("OsalUtils : Semantic version doesn't match the requirement [%s]\n",
           semanticVersion.c_str());
    return false;
  }
  std::regex regExprNum("(0|[1-9][0-9]*)");
  auto regExBegin = std::sregex_iterator(semanticVersion.begin(),
                                         semanticVersion.end(), regExprNum);
  auto regExEnd = std::sregex_iterator();
  auto dist = std::distance(regExBegin, regExEnd);
  if (std::distance(regExBegin, regExEnd) != MIN_FIELDS) {
    printf(
        "OsalUtils : Semantic version doesn't match have enough fields [%s]\n",
        semanticVersion.c_str());
    return false;
  }
  for (std::sregex_iterator itr = regExBegin; itr != regExEnd; ++itr) {
    std::smatch match = *itr;
    std::string match_str = match.str();
    try {
      VersionInfo[versionIndex] = std::stoi(match_str);
      versionIndex++;
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      break;
    }
  }
  majorVer = VersionInfo[0];
  minorVer = VersionInfo[1];
  patchVer = VersionInfo[2];
  return true;
}
