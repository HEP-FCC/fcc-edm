#--- CMake Config Files -----------------------------------------------
# - Use CMake's module to help generating relocatable config files
include(CMakePackageConfigHelpers)

# - Versioning
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/fccedmConfigVersion.cmake
  VERSION ${fccedm_VERSION}
  COMPATIBILITY SameMajorVersion)

# - Install time config and target files
configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/fccedmConfig.cmake.in
  "${PROJECT_BINARY_DIR}/fccedmConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/fccedm"
  PATH_VARS
    CMAKE_INSTALL_BINDIR
    CMAKE_INSTALL_INCLUDEDIR
    CMAKE_INSTALL_LIBDIR
  )

# - install and export
install(FILES
  "${PROJECT_BINARY_DIR}/fccedmConfigVersion.cmake"
  "${PROJECT_BINARY_DIR}/fccedmConfig.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/fccedm"
  )
install(EXPORT fccedmTargets
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/fccedm"
  )
