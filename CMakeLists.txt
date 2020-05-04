cmake_minimum_required(VERSION 3.3)
project(fccedm VERSION 0.5.4)
set(fccedm_VERSION "${fccedm_VERSION_MAJOR}.${fccedm_VERSION_MINOR}.${fccedm_VERSION_PATCH}")

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

execute_process(COMMAND python ${podio_DIR}/../../../python/podio_class_generator.py edm.yaml datamodel datamodel
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#--- Declare options -----------------------------------------------------------
option(fccedm_documentation "Whether or not to create doxygen doc target." OFF)

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")


# Use .so also on macOS so ROOT can load them
if(APPLE)
  set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif(APPLE)


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
set(ROOT_genreflex_cmd ${ROOT_genreflex_CMD})
include(${ROOT_USE_FILE})


find_package(dag REQUIRED HINTS $ENV{FCCDAG})
if(${DAG_FOUND})
  message(STATUS "Found dag: ${DAG_DIR}")
  include_directories(
          ${DAG_INCLUDE_DIRS}
  )
endif(${DAG_FOUND})



# set up include-directories
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
  ${ROOT_INCLUDE_DIR}
  ${podio_INCLUDE_DIR}
  )

# adding testing capabilities
include(CTest)


#--- enable CPack --------------------------------------------------------------
include(cmake/fccedmCPack.cmake)

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
