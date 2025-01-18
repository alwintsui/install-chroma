# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "FATAL: In-source builds are not allowed.
  You should create separate directory for build files.")
endif()

# Works with 3.11 and tested through 3.15
cmake_minimum_required(VERSION 3.11...3.16)

project (PyUSQCD VERSION 1.0.0
        DESCRIPTION "Python wrapper for USQCD packages"     )

set(APP_VER_NUM ${PROJECT_NAME}-${PROJECT_VERSION})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11) #add -std=gnu++11
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# all external libs except hup built as static
set(BUILD_SHARED_LIBS OFF)
#add -fPIC in static in order to link shared libxxx.so
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (MSVC)
    add_compile_options("$<$<CONFIG:DEBUG>:/MDd>")
else()
        add_compile_options(
    "$<$<CONFIG:RELEASE>:-Wall;${CXX_OPT}>"
    "$<$<CONFIG:DEBUG>:-g;-O0;-Wall;-DDEBUG>"
        )
        #use ';' seperate them
endif()

# This macro gets the version string for a compiler, and also extracts  compiler flags.
macro(get_compiler_info LANGUAGE BUILD_COMPILER)
    set(${BUILD_COMPILER} "${CMAKE_${LANGUAGE}_COMPILER} ${CMAKE_${LANGUAGE}_COMPILER_ID} ${CMAKE_${LANGUAGE}_COMPILER_VERSION}")
endmacro()

get_compiler_info(C BUILD_C_COMPILER)
get_compiler_info(CXX BUILD_CXX_COMPILER)

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPER)
string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

option(USE_CUDA "To use CUDA" OFF)
option(USE_HIP "To use HIP" OFF)
option(USE_OPENMP "To use OpenMP" ON)
option(USE_PYTHON "To build python module" OFF)


if(USE_CUDA)
find_package(CUDA) # for both src and tests
endif()

if(USE_HIP)
find_package(HIP)
endif()

if(USE_CUDA OR USE_HIP)
unset(USE_OPENMP CACHE)
set(USE_OPENMP OFF)
endif()

if(USE_OPENMP)
find_package(OpenMP REQUIRED)
endif()

if(USE_GPROF)
  message(STATUS "Using GPROF")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -pg")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
  set(CMAKE_LINK_LIBRARY_FILE_FLAG "${CMAKE_LINK_LIBRARY_FILE_FLAG} -g -pg ")
endif()

message(STATUS "HOME = $ENV{HOME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR = " ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "CMAKE_COMPILER_IS_GNUCXX = " ${CMAKE_COMPILER_IS_GNUCXX})
message(STATUS "CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
message(STATUS "CMAKE_INSTALL_PREFIX = " ${CMAKE_INSTALL_PREFIX})
message(STATUS "PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
message(STATUS "PROJECT_BINARY_DIR " ${PROJECT_SOURCE_DIR})
message(STATUS "CMAKE_C_COMPILER_ID = " ${CMAKE_C_COMPILER_ID})
message(STATUS "CMAKE_INSTALL_PREFIX = " ${CMAKE_INSTALL_PREFIX})

include(CheckIncludeFiles)
check_include_files(unistd.h     HAVE_UNISTD_H)
check_include_files(stdint.h     HAVE_STDINT_H)
check_include_files(inttypes.h   HAVE_INTTYPES_H)

include(CheckCXXSymbolExists)
check_cxx_symbol_exists(erfc cmath HAVE_ERFC)

#add_subdirectory(cmake)

add_subdirectory(src)

if(USE_PYTHON)
    add_subdirectory(python)
endif()

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
#BUILD_TESTING: flag set true by CTest if on.
include(CTest)
if( CMAKE_BUILD_TESTING AND BUILD_TESTING)
        # add test_all to the ALL target
    add_custom_target(test_all ALL)
    add_subdirectory(tests)
endif()
