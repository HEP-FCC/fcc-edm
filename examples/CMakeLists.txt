include_directories(
        ${CMAKE_SOURCE_DIR}/datamodel
)

add_executable(fccedm-write write.cc)
add_executable(fccedm-read read.cc)
add_executable(fccedm-simplewrite simplewrite.cc)
add_executable(fccedm-simpleread simpleread.cc)

target_link_libraries(fccedm-write utilities datamodel podio ${ROOT_LIBRARIES})
target_link_libraries(fccedm-read utilities datamodel podio ${ROOT_LIBRARIES})
target_link_libraries(fccedm-simplewrite utilities datamodel podio ${ROOT_LIBRARIES})
target_link_libraries(fccedm-simpleread utilities datamodel podio ${ROOT_LIBRARIES})

install(TARGETS fccedm-write fccedm-read fccedm-simplewrite fccedm-simpleread
  # IMPORTANT: Add the write executable to the "export-set"
  EXPORT fccedmTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
