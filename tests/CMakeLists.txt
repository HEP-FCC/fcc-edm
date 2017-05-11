include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/datamodel
)

add_executable(fccedm-graph-write graph_write_test.cc)
add_executable(fccedm-graph-read graph_read_test.cc)

target_link_libraries(fccedm-graph-read utilities datamodel podio ${ROOT_LIBRARIES})
target_link_libraries(fccedm-graph-write utilities datamodel podio  ${ROOT_LIBRARIES})


# --- adding tests for examples ------------------------------
add_test(NAME fccedm-graph-write COMMAND fccedm-graph-write)
set_property(TEST fccedm-graph-write PROPERTY ENVIRONMENT LD_LIBRARY_PATH=$ENV{PODIO}/lib:${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/examples:$ENV{LD_LIBRARY_PATH})

add_test(NAME fccedm-graph-read COMMAND fccedm-graph-read  DEPENDS fccedm-graph-write)
set_property(TEST fccedm-graph-read PROPERTY ENVIRONMENT LD_LIBRARY_PATH=$ENV{PODIO}/lib:${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/examples:$ENV{LD_LIBRARY_PATH})
