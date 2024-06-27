set(IpxCameraSDK_VERSION 1.5.0.63)

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was _PackageConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set_and_check(IpxCameraSDK_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/inc")
set_and_check(IpxCameraSDK_LIBRARY_DIR "${PACKAGE_PREFIX_DIR}/lib/Linux64_ARM")
set_and_check(IpxCameraSDK_OUTPUT_DIR "${PACKAGE_PREFIX_DIR}/bin/Linux64_ARM")
set_and_check(IpxCameraSDK_SAMPLES_DIR "${PACKAGE_PREFIX_DIR}/samples")
set_and_check(IpxCameraSDK_DOC_DIR "${PACKAGE_PREFIX_DIR}/doc")
set_and_check(IpxCameraSDK_GenLIB_DIR "${PACKAGE_PREFIX_DIR}/lib/Linux64_ARM/genicam/bin/Linux64_ARM")

get_filename_component(_CURRENT_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)

# load target file
set(IpxCameraSDK_EXPORT_TARGETS_FILE "${_CURRENT_DIR}/IpxCameraSDK-targets.cmake")
if (EXISTS ${IpxCameraSDK_EXPORT_TARGETS_FILE})
    include(${IpxCameraSDK_EXPORT_TARGETS_FILE})
else()
    message(WARNING "Cannot find ${IpxCameraSDK_EXPORT_TARGETS_FILE} with IMPORTED targets")
endif()

# load additional config file
set(IpxCameraSDK_ADDITIONAL_TARGETS_FILE "${_CURRENT_DIR}/IpxTools-targets_Export.cmake")
if (EXISTS ${IpxCameraSDK_ADDITIONAL_TARGETS_FILE})
    include(${IpxCameraSDK_ADDITIONAL_TARGETS_FILE})
else()
    message(WARNING "Cannot find additional file ${IpxCameraSDK_ADDITIONAL_TARGETS_FILE}")
endif()
