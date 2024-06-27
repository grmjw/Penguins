/**************************************************************************
Copyright (c) 2021, s.m.s, smart microwave sensors GmbH, Brunswick, Germany

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**************************************************************************/

#ifndef EXTERNAL__VERSIONEDIFACE_H_
#define EXTERNAL__VERSIONEDIFACE_H_

#include <ExternalTypes.h>

namespace com {
class EXPORT_COM_LIB VersionedIface {
 public:
  VersionedIface() {}
  virtual ~VersionedIface() {}

  virtual uint16_t GetMajorVer() const = 0;
  virtual uint16_t GetMinorVer() const = 0;
  virtual uint16_t GetPatchVer() const = 0;
};

}  // namespace com

#endif  // EXTERNAL__VERSIONEDIFACE_H_
