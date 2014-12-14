include_directories(
        ${CMAKE_SOURCE_DIR}/datamodel
)

add_executable(fccedm-write write.cc)
add_executable(fccedm-read read.cc)

target_link_libraries(fccedm-write utilities datamodel albers)
target_link_libraries(fccedm-read utilities datamodel albers)

install(TARGETS fccedm-write fccedm-read
  # IMPORTANT: Add the write executable to the "export-set"
  EXPORT fccedmTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
