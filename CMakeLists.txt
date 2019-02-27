cmake_minimum_required(VERSION 3.3)
project(fccedm VERSION 0.5.2)
set(fccedm_VERSION "${fccedm_VERSION_MAJOR}.${fccedm_VERSION_MINOR}")

# Define basic build settings
# Use GNU-style hierarchy for installing build products
include(GNUInstallDirs)

# Define a default build type can be overriden by passing
# ``-DCMAKE_BUILD_TYPE=<type>`` when invoking CMake
if(NOT CMAKE_CONFIGURATION_TYPES)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo
      CACHE STRING "Choose the type of build, options are: None Release MinSizeRel Debug RelWithDebInfo"
      FORCE
      )
  else()
    set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}"
      CACHE STRING "Choose the type of build, options are: None Release MinSizeRel Debug RelWithDebInfo"
      FORCE
      )
  endif()
endif()

find_package(podio REQUIRED HINTS $ENV{PODIO})
# Make sure the library is found.
# Not the case if LD_LIBRARY_PATH is wrong
find_library(PODIOLIB podio PATHS ${podio_DIR}/../lib)
if (NOT PODIOLIB)
    message(FATAL_ERROR "libpodio.so(dylib) cannot be found dynamically. Make sure you have set up your environment to use PODIO")
endif()
link_directories(${podio_LIBRARY_DIR})

execute_process(COMMAND python ${podio_CMAKE_DIR}/../python/podio_class_generator.py edm.yaml datamodel datamodel
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#--- Declare options -----------------------------------------------------------
option(CREATE_DOC "Whether or not to create doxygen doc target.")

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")


if(APPLE)
  set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif(APPLE)

set(DEF_INSTALL_CMAKE_DIR cmake)
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Set up C++ Standard
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

if(NOT CMAKE_CXX_STANDARD MATCHES "14|17")
  message(FATAL_ERROR "Unsupported C++ standard: ${CMAKE_CXX_STANDARD}")
endif()

message (STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")

if (${APPLE})
    set(CPP_STANDARD_FLAGS "-std=c++${CMAKE_CXX_STANDARD}\ -stdlib=libc++")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DDROP_CGAL ${CPP_STANDARD_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-variable -Wno-unused-parameter")



#--- Declare ROOT dependency ---------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(ROOT REQUIRED COMPONENTS RIO Tree Physics)
include_directories(${ROOT_INCLUDE_DIR})
include(${ROOT_USE_FILE})

find_package(dag REQUIRED HINTS $ENV{FCCDAG})
if(${DAG_FOUND})
  message(STATUS "Found dag: ${DAG_DIR}")
  include_directories(
          ${DAG_INCLUDE_DIRS}
  )
endif(${DAG_FOUND})

link_directories(${ROOT_LIBRARY_DIR})
#add_definitions(-Wpadded)
#--temporary fix of inconsistency in ROOT CMake macros
set(ROOT_genreflex_cmd ${ROOT_genreflex_CMD})

add_definitions(-Wno-unused-variable -Wno-unused-parameter)

# set up include-directories
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
  ${ROOT_INCLUDE_DIR}
  ${podio_INCLUDE_DIRS}
  )

# adding testing capabilities
include(CTest)

#--- target for Doxygen documentation ------------------------------------------
if(fccedm_documentation)
  include(cmake/fccedmDoxygen.cmake)
endif()

configure_file(${CMAKE_SOURCE_DIR}/cmake/Datamodel.cmake
  "${CMAKE_SOURCE_DIR}/datamodel/CMakeLists.txt" @ONLY)
# Add sub-directories
add_subdirectory(datamodel)
add_subdirectory(utilities)
add_subdirectory(examples)
add_subdirectory(tests)


# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS datamodel utilities fccedm-write fccedm-read fccedm-simplewrite
  FILE "${PROJECT_BINARY_DIR}/fccedmTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE fccedm)

# Create the fccedmConfig.cmake and fccedmConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(fccedmConfig.cmake.in
  "${PROJECT_BINARY_DIR}/fccedmConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${FCCEDM_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(fccedmConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/fccedmConfig.cmake" @ONLY)
# ... for both
configure_file(fccedmConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/fccedmConfigVersion.cmake" @ONLY)

# Install the fccedmConfig.cmake and fccedmConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/fccedmConfig.cmake"
  "${PROJECT_BINARY_DIR}/fccedmConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT fccedmTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
