# TODO: re-enable dataframe test as root 6.16 is available

include_directories(
        ${CMAKE_SOURCE_DIR}/datamodel
)

add_executable(fccedm-write write.cc)
#add_executable(fccedm-dataframe dataframe.cc)
add_executable(fccedm-read read.cc)
add_executable(fccedm-simplewrite simplewrite.cc)
add_executable(fccedm-simpleread simpleread.cc)
add_executable(fccedm-graph graph.cc)

target_link_libraries(fccedm-write utilities datamodel podio::podioRootIO datamodelDict)
#target_link_libraries(fccedm-dataframe utilities datamodel podio::podioRootIO datamodelDict ROOT::ROOTDataFrame)
target_link_libraries(fccedm-read utilities datamodel podio::podioRootIO datamodelDict )
target_link_libraries(fccedm-simplewrite utilities datamodel podio::podioRootIO datamodelDict )
target_link_libraries(fccedm-simpleread utilities datamodel podio::podioRootIO datamodelDict )
target_link_libraries(fccedm-graph utilities)
install(TARGETS fccedm-write fccedm-read fccedm-simplewrite fccedm-simpleread #fccedm-dataframe
  # IMPORTANT: Add the write executable to the "export-set"
  EXPORT fccedmTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)



# --- adding tests for examples ------------------------------
add_test(NAME fccedm-simplewrite COMMAND fccedm-simplewrite)
set_property(TEST fccedm-simplewrite PROPERTY ENVIRONMENT LD_LIBRARY_PATH=$ENV{PODIO}/lib:${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/examples:$ENV{LD_LIBRARY_PATH})

add_test(NAME fccedm-simpleread COMMAND fccedm-simpleread DEPENDS fccedm-simplewrite)
set_property(TEST fccedm-simpleread PROPERTY ENVIRONMENT LD_LIBRARY_PATH=$ENV{PODIO}/lib:${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/examples:$ENV{LD_LIBRARY_PATH})

add_test(NAME fccedm-write COMMAND fccedm-write)
set_property(TEST fccedm-write PROPERTY ENVIRONMENT LD_LIBRARY_PATH=$ENV{PODIO}/lib:${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/examples:$ENV{LD_LIBRARY_PATH})

add_test(NAME fccedm-read COMMAND fccedm-read DEPENDS fccedm-write)
set_property(TEST fccedm-read PROPERTY ENVIRONMENT LD_LIBRARY_PATH=$ENV{PODIO}/lib:${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/examples:$ENV{LD_LIBRARY_PATH})

#add_test(NAME fccedm-dataframe COMMAND fccedm-dataframe DEPENDS fccedm-write)
#set_property(TEST fccedm-dataframe PROPERTY ENVIRONMENT LD_LIBRARY_PATH=$ENV{PODIO}/lib:${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/examples:$ENV{LD_LIBRARY_PATH})

