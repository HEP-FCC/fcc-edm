
PODIO_GENERATE_DATAMODEL(datamodel ../edm.yaml headers sources)

add_library(datamodel SHARED ${sources} ${headers})
target_link_libraries(datamodel
  PUBLIC
  podio::podio
  )
target_include_directories(datamodel
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_target_properties(datamodel PROPERTIES PUBLIC_HEADER "${headers}")

add_library(datamodelDict SHARED)
add_library(fcc::datamodelDict ALIAS datamodelDict )
target_link_libraries(datamodelDict
  PUBLIC
  datamodel
  podio::podio
  ROOT::Core
  )
target_include_directories(datamodelDict
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  ${ROOT_INCLUDE_DIRS}
)

PODIO_GENERATE_DICTIONARY(datamodelDict ${headers} SELECTION src/selection.xml
  OPTIONS --library ${CMAKE_SHARED_LIBRARY_PREFIX}datamodelDict${CMAKE_SHARED_LIBRARY_SUFFIX} )
set_target_properties(datamodelDict-dictgen PROPERTIES EXCLUDE_FROM_ALL TRUE)
add_dependencies(datamodelDict datamodel)

install(TARGETS datamodel datamodelDict
  EXPORT fccedmTargets
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/datamodel"
  COMPONENT dev)

install(FILES
  "${PROJECT_BINARY_DIR}/datamodel/datamodelDictDict.rootmap"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev)

if (${ROOT_VERSION} GREATER 6)
  install(FILES
      "${PROJECT_BINARY_DIR}/datamodel/libdatamodelDict_rdict.pcm"
      DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev)
endif()
