# to build pyusqcd/_usqcd.so
if(CMAKE_VERSION VERSION_LESS 3.12)
  find_package(PythonLibs REQUIRED) # Deprecated since version 3.12
  find_package(PythonInterp REQUIRED)
else()
  find_package(Python3 COMPONENTS Interpreter Development NumPy)
  set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
  set(PYTHON_INCLUDE_DIRS ${Python3_INCLUDE_DIRS})
  set(PYTHON_INCLUDE_DIR ${Python3_INCLUDE_DIR})
endif()

message(STATUS "PYTHON_EXECUTABLE = " ${PYTHON_EXECUTABLE})
message(STATUS "PYTHON_INCLUDE_DIRS = " ${PYTHON_INCLUDE_DIRS})
message(STATUS "Python3_NumPy_INCLUDE_DIRS = " ${Python3_NumPy_INCLUDE_DIRS})


if(NOT PYTHON_INCLUDE_DIR)
  execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig; print(distutils.sysconfig.get_config_var('INCLUDEPY'))"
         OUTPUT_VARIABLE PYTHON_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig; print(distutils.sysconfig.get_config_var('LIBDIR'))"
         OUTPUT_VARIABLE PYTHON_LIB_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig; print(distutils.sysconfig.get_config_var('LDVERSION'))"
         OUTPUT_VARIABLE PYTHON_LIB_VER OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "PYTHON_INCLUDE_DIR = " ${PYTHON_INCLUDE_DIR})
message(STATUS "PYTHON_LIB_DIR = " ${PYTHON_LIB_DIR})
message(STATUS "PYTHON_LIB_VER = " ${PYTHON_LIB_VER})

#import SWIG
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})
message(STATUS "SWIG_USE_FILE = " ${SWIG_USE_FILE})

#lime_api.i
set_property(SOURCE lime_api.i PROPERTY CPLUSPLUS ON)
swig_add_library(pylime LANGUAGE python SOURCES lime_api.i)
get_target_property(LIME_API_INCLUDE_DIRS lime_api INCLUDE_DIRECTORIES)
set_property(TARGET pylime PROPERTY SWIG_INCLUDE_DIRECTORIES ${LIME_API_INCLUDE_DIRS})
target_include_directories(pylime PUBLIC ${PROJECT_SOURCE_DIR}/src ${PYTHON_INCLUDE_DIR})
target_link_libraries(pylime lime_api python${PYTHON_LIB_VER})
#set_target_properties(pylime PROPERTIES PREFIX ""  SUFFIX ".so" LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/python/pyusqcd")

#chroma_api.i
set_property(SOURCE chroma_api.i PROPERTY CPLUSPLUS ON)
swig_add_library(pychroma LANGUAGE python SOURCES chroma_api.i)
get_target_property(CHROMA_API_INCLUDE_DIRS chroma_api INCLUDE_DIRECTORIES)
set_property(TARGET pychroma PROPERTY SWIG_INCLUDE_DIRECTORIES ${CHROMA_API_INCLUDE_DIRS})
target_include_directories(pychroma PUBLIC ${PROJECT_SOURCE_DIR}/src ${PYTHON_INCLUDE_DIR} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(pychroma chroma_api python${PYTHON_LIB_VER})