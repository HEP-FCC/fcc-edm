include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/datamodel
)

file(GLOB sources *.cc)
file(GLOB headers *.h)

add_library(utilities SHARED ${sources})
target_link_libraries(utilities datamodel podio ${ROOT_LIBRARIES})
target_include_directories(utilities PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS utilities
  # IMPORTANT: Add the podio library to the "export-set"
  EXPORT fccedmTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/utilities)
