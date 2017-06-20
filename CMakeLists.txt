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

# Require c++14 standard and flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-fPIC -DDROP_CGAL -Wall -Wextra -Wpedantic -Wno-unused-variable -Wno-unused-parameter")

# Use .so also on macOS so ROOT can load them
if(APPLE)
  set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif()


option(fccedm_documentation "Whether or not to create doxygen doc target." OFF)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Tree Physics)
include(${ROOT_USE_FILE})
# temporary fix of inconsistency in ROOT CMake macros
set(ROOT_genreflex_cmd ${ROOT_genreflex_CMD})

find_package(dag REQUIRED HINTS $ENV{FCCDAG})
if(${DAG_FOUND})
  include_directories(
          ${DAG_INCLUDE_DIRS}
  )
endif(${DAG_FOUND})

find_package(podio REQUIRED HINTS $ENV{PODIO})
if(${podio_FOUND})
  include_directories(${podio_INCLUDE_DIRS})
  link_directories(${podio_LIBRARY_DIR})
endif()

# Regenreate datamodel when invoking cmake
execute_process(COMMAND python ${podio_LIBRARY_DIR}/../python/podio_class_generator.py edm.yaml datamodel datamodel
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

link_directories(${ROOT_LIBRARY_DIR})

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

include(cmake/fccedmCreateConfig.cmake)
