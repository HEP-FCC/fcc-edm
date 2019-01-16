include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/datamodel
)

file(GLOB sources src/*.cc)
file(GLOB headers datamodel/*.h podio/PythonEventStore.h)

add_library(datamodel SHARED ${sources} ${headers})
target_link_libraries(datamodel podio)

REFLEX_GENERATE_DICTIONARY(datamodel ${headers} SELECTION src/selection.xml )
add_library(datamodelDict SHARED datamodel.cxx)
add_dependencies(datamodelDict datamodel-dictgen)
target_link_libraries(datamodelDict datamodel podio ROOT::RIO ROOT::Tree ROOT::Physics)

set_target_properties(datamodel PROPERTIES
  PUBLIC_HEADER "${headers}")

install(TARGETS datamodel datamodelDict
  # IMPORTANT: Add the datamodel library to the "export-set"
  EXPORT fccedmTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/datamodel"
  COMPONENT dev)

install(FILES
  "${PROJECT_BINARY_DIR}/datamodel/datamodelDict.rootmap"
  DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)

if (${ROOT_VERSION} GREATER 6)
  install(FILES
      "${PROJECT_BINARY_DIR}/datamodel/datamodel_rdict.pcm"
      DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)
endif()
