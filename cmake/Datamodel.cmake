include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/datamodel
)

file(GLOB sources src/*.cc)
file(GLOB headers datamodel/*.h podio/PythonEventStore.h)

add_library(datamodel SHARED ${sources})
target_include_directories(datamodel PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(datamodel podio)

REFLEX_GENERATE_DICTIONARY(datamodel ${headers} SELECTION src/selection.xml)
add_library(datamodelDict SHARED datamodel.cxx)
add_dependencies(datamodelDict datamodel-dictgen)
target_link_libraries(datamodelDict datamodel podio ${ROOT_LIBRARIES})

install(TARGETS datamodel datamodelDict
  # IMPORTANT: Add the datamodel library to the "export-set"
  EXPORT fccedmTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY ${CMAKE_SOURCE_DIR}/datamodel/datamodel DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES
  ${PROJECT_BINARY_DIR}/datamodel/datamodelDict.rootmap
  ${PROJECT_BINARY_DIR}/datamodel/datamodel_rdict.pcm
  DESTINATION ${CMAKE_INSTALL_LIBDIR})
