#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "IpxDemosaicing" for configuration "Release"
set_property(TARGET IpxDemosaicing APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxDemosaicing PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "IpxMisc;IpxImageApi;opencv_core;opencv_imgproc"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxDemosaicing.so.3.3.0.55"
  IMPORTED_SONAME_RELEASE "libIpxDemosaicing.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxDemosaicing )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxDemosaicing "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxDemosaicing.so.3.3.0.55" )

# Import target "IpxMisc" for configuration "Release"
set_property(TARGET IpxMisc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxMisc PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxMisc.so.3.3.0.55"
  IMPORTED_SONAME_RELEASE "libIpxMisc.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxMisc )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxMisc "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxMisc.so.3.3.0.55" )

# Import target "IpxImageApi" for configuration "Release"
set_property(TARGET IpxImageApi APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxImageApi PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageApi.so.3.3.0.55"
  IMPORTED_SONAME_RELEASE "libIpxImageApi.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxImageApi )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxImageApi "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageApi.so.3.3.0.55" )

# Import target "IpxImageConverter" for configuration "Release"
set_property(TARGET IpxImageConverter APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxImageConverter PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "IpxMisc;IpxImageApi;IpxDemosaicing"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageConverter.so.3.3.0.55"
  IMPORTED_SONAME_RELEASE "libIpxImageConverter.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxImageConverter )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxImageConverter "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageConverter.so.3.3.0.55" )

# Import target "IpxImageUnpacker" for configuration "Release"
set_property(TARGET IpxImageUnpacker APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxImageUnpacker PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "IpxMisc;IpxImageApi"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageUnpacker.so.3.3.0.55"
  IMPORTED_SONAME_RELEASE "libIpxImageUnpacker.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxImageUnpacker )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxImageUnpacker "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageUnpacker.so.3.3.0.55" )

# Import target "IpxImageSerializer" for configuration "Release"
set_property(TARGET IpxImageSerializer APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxImageSerializer PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "ffmpeg_libavutil;ffmpeg_libavcodec;ffmpeg_libavformat;ffmpeg_libswscale;ffmpeg_libswresample;IpxImageApi"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageSerializer.so.3.3.0.55"
  IMPORTED_SONAME_RELEASE "libIpxImageSerializer.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxImageSerializer )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxImageSerializer "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxImageSerializer.so.3.3.0.55" )

# Import target "IpxDisplayQt" for configuration "Release"
set_property(TARGET IpxDisplayQt APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IpxDisplayQt PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "IpxDemosaicing;opencv_core;opencv_imgproc;Qt5::Widgets"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxDisplayQt.so.3.3.0.55"
  IMPORTED_SONAME_RELEASE "libIpxDisplayQt.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS IpxDisplayQt )
list(APPEND _IMPORT_CHECK_FILES_FOR_IpxDisplayQt "${_IMPORT_PREFIX}/lib/Linux64_ARM/libIpxDisplayQt.so.3.3.0.55" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
