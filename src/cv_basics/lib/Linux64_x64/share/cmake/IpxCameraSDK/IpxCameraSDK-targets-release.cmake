#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "IpxCTI" for configuration "Release"
set_property(TARGET IpxCTI APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxCTI PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCTI.cti.1.5.0.83"
  IMPORTED_SONAME_RELEASE "libIpxCTI.cti.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxCTI )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxCTI "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCTI.cti.1.5.0.83" )

# Import target "IpxCameraApi" for configuration "Release"
set_property(TARGET IpxCameraApi APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxCameraApi PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "GenICam_GCBase;GenICam_GenApi"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraApi.so.1.5.0.83"
  IMPORTED_SONAME_RELEASE "libIpxCameraApi.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxCameraApi )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxCameraApi "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraApi.so.1.5.0.83" )

# Import target "IpxCameraApiPy" for configuration "Release"
set_property(TARGET IpxCameraApiPy APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxCameraApiPy PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "IpxCameraApi;IpxImageApi;IpxDemosaicing;IpxImageSerializer;IpxImageUnpacker;IpxImageConverter"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraApiPy.so.1.5.0.83"
  IMPORTED_SONAME_RELEASE "libIpxCameraApiPy.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxCameraApiPy )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxCameraApiPy "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraApiPy.so.1.5.0.83" )

# Import target "IpxCameraGuiApiPy" for configuration "Release"
set_property(TARGET IpxCameraGuiApiPy APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxCameraGuiApiPy PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "IpxCameraApi;IpxCameraGuiApi;IpxDisplayQt;IpxImageApi;IpxDemosaicing;IpxImageSerializer;IpxImageUnpacker;IpxImageConverter"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraGuiApiPy.so.1.5.0.83"
  IMPORTED_SONAME_RELEASE "libIpxCameraGuiApiPy.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxCameraGuiApiPy )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxCameraGuiApiPy "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraGuiApiPy.so.1.5.0.83" )

# Import target "IpxCameraGuiApi" for configuration "Release"
set_property(TARGET IpxCameraGuiApi APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxCameraGuiApi PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "IpxCameraApi;GenICam_GCBase;GenICam_GenApi;Qt5::Core;Qt5::Gui;Qt5::Widgets"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraGuiApi.so.1.5.0.83"
  IMPORTED_SONAME_RELEASE "libIpxCameraGuiApi.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxCameraGuiApi )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxCameraGuiApi "${_IMPORT_PREFIX}/lib/Linux64_x64/libIpxCameraGuiApi.so.1.5.0.83" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
