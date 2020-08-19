include_directories(
        ${CMAKE_SOURCE_DIR}/datamodel
)


### Legacy Issue: FloatData
### Due to a header collision on MacOS ("Float.h")
### the float data type was removed from fcc-edm
### In order to keep backwards compatibility with existing samples
### FloatData.h is added to a dictionary here and 
### copied to the datamodel include directory

file(GLOB sources *.cc)
file(GLOB headers *.h)

include_directories(${CMAKE_SOURCE_DIR}/utilities)
ROOT_GENERATE_DICTIONARY(G__utilities FloatData.h FCCLambdas.h LINKDEF LinkDef.h)

add_library(utilities SHARED ${sources} ${headers} G__utilities.cxx )
target_link_libraries(utilities datamodel podio::podioRootIO ROOT::Physics)

set_target_properties(utilities PROPERTIES
  PUBLIC_HEADER "${headers}")

install(TARGETS utilities
  # IMPORTANT: Add the podio library to the "export-set"
  EXPORT fccedmTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/utilities"
    COMPONENT dev)


# copy FloatData header to datamodel include directory,
# in order not to break #include statements.
install(FILES
  ${CMAKE_SOURCE_DIR}/utilities/FloatData.h
  DESTINATION "${INSTALL_INCLUDE_DIR}/datamodel" COMPONENT dev)

install(FILES
  "${PROJECT_BINARY_DIR}/utilities/libutilities.rootmap"
  DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)

if (${ROOT_VERSION} GREATER 6)
  install(FILES
      "${PROJECT_BINARY_DIR}/utilities/libutilities_rdict.pcm"
      DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)
endif()
