cmake_minimum_required(VERSION 2.8)

project(fccedm)
set(fccedm_MAJOR_VERSION 0)
set(fccedm_MINOR_VERSION 4)
set(fccedm_PATCH_VERSION 0)
set(fccedm_VERSION
  ${fccedm_MAJOR_VERSION}.${fccedm_MINOR_VERSION}.${fccedm_PATCH_VERSION})

#--- Test if this is actually needed
if(APPLE)
  set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif(APPLE)

#--- Declare options -----------------------------------------------------------
option(fccedm_documentation "Whether or not to create doxygen doc target.")

#--- set up default install dirs -----------------------------------------------
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")

#-- set compiler flags ---------------------------------------------------------
add_definitions(-Wno-unused-variable -Wno-unused-parameter -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DDROP_CGAL -std=c++11 -Wall -Wextra -Wpedantic")

#--- Declare ROOT dependency ---------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(ROOT REQUIRED COMPONENTS RIO Tree)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

#--- enable unit testing capabilities ------------------------------------------
include(CTest)

#--- enable CPack --------------------------------------------------------------
include(cmake/fccedmCPack.cmake)

#--- target for Doxygen documentation ------------------------------------------
if(fccedm_documentation)
  include(cmake/fccedmDoxygen.cmake)
endif()

#--- add version files ---------------------------------------------------------
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fccedmVersion.h
               ${CMAKE_CURRENT_BINARY_DIR}/fccedmVersion.h )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/fccedmVersion.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/fccedm )

#--- Declare PODIO dependency --------------------------------------------------
find_package(podio REQUIRED HINTS $ENV{PODIO})
message(STATUS "Found podio: ${podio_DIR}")
# Make sure the library is found. (Not the case if LD_LIBRARY_PATH is wrong)
find_library(PODIOLIB podio PATHS $ENV{PODIO}/lib)
if (NOT PODIOLIB)
    message(FATAL_ERROR
      "libpodio.so(dylib) cannot be found dynamically. Make sure you have sourced PODIO init*.sh file to set up your environment to use PODIO")
endif()
link_directories(${podio_LIBRARY_DIR})
include_directories(${podio_INCLUDE_DIRS})

#--- Add all subdirectories ----------------------------------------------------
add_subdirectory(datamodel)
add_subdirectory(utilities)
add_subdirectory(examples)

#--- add cmake infrastructure for finding this package -------------------------
include(cmake/fccedmCreateConfig.cmake)
