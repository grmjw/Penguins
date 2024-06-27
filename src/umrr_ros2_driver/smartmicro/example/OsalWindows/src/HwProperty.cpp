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
#include <HwProperty.h>

using namespace osal::types;
using namespace osal;

HwProperty::HwProperty(HwIfaceType hwType) : _hwType(hwType) {}

HwProperty::~HwProperty() {}

HwIfaceType HwProperty::GetHwIfaceType() const { return _hwType; }

std::string HwProperty::GetIfaceName() const { return _ifcName; }

std::string HwProperty::GetDevSupplier() const { return _hwDevSupplier; }

std::string HwProperty::GetDevType() const { return _hwDevType; }

std::string HwProperty::GetLinkSpeed() const { return _linkSpeed; }

std::string HwProperty::GetIpAddress() const { return _ipAddress; }

std::string HwProperty::GetUsedPort() const { return _usedPort; }

std::string HwProperty::GetDeviceId() const { return _deviceId; }

void HwProperty::SetIfaceName(IN std::string ifcName) { _ifcName = ifcName; }

void HwProperty::SetDevSupplier(IN std::string hwDevSupplier) {
  _hwDevSupplier = hwDevSupplier;
}

void HwProperty::SetDevType(IN std::string hwDevType) {
  _hwDevType = hwDevType;
}

void HwProperty::SetLinkSpeed(IN std::string linkSpeed) {
  _linkSpeed = linkSpeed;
}

void HwProperty::SetIpAddress(IN std::string ipAddress) {
  _ipAddress = ipAddress;
}

void HwProperty::SetUsedPort(IN std::string usedPort) { _usedPort = usedPort; }

void HwProperty::SetDeviceId(IN std::string deviceId) { _deviceId = deviceId; }