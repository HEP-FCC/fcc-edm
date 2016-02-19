include(CMakePackageConfigHelpers)
configure_file(cmake/fccedmConfig.cmake.in "${PROJECT_BINARY_DIR}/fccedmConfig.cmake" @ONLY)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/fccedmConfigVersion.cmake
                                 VERSION ${fccedm_VERSION}
                                 COMPATIBILITY SameMajorVersion )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/fccedmConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/fccedmConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake )
