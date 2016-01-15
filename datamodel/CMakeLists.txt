include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/datamodel
)

file(GLOB sources src/*.cc datamodel/*.h)
file(GLOB headers datamodel/*.h podio/PythonEventStore.h)

REFLEX_GENERATE_DICTIONARY(ExampleDict ${headers} SELECTION src/selection.xml )

add_library(datamodel SHARED ${sources} ExampleDict.cxx)
target_link_libraries(datamodel podio ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES})

set_target_properties(datamodel PROPERTIES
  PUBLIC_HEADER "${headers}")

install(TARGETS datamodel
  # IMPORTANT: Add the datamodel library to the "export-set"
  EXPORT fccedmTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/datamodel"
    COMPONENT dev)

if (${ROOT_VERSION} GREATER 6)
  install(FILES
      "${PROJECT_BINARY_DIR}/datamodel/ExampleDict_rdict.pcm"
      DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)
endif()
