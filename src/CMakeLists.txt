######################################################################
option(USE_DEFAULT_STREAM_PER_THREAD "To use DEFAULT STREAM Per Thread" OFF)
option(USE_SINGLE_REAL "To use single real" OFF) #for hup

# Optionally glob, but only for CMake 3.12 or later:
# 定义一个宏来过滤列表中的元素
macro(filter_out pattern result)
  foreach(file ${ARGN})
    if(NOT file MATCHES "${pattern}")
      list(APPEND ${result} "${file}")
    endif()
  endforeach()
endmacro()

file(GLOB CHROMA_API_SRC chroma_api.cpp)  
file(GLOB CHROMA_API_HDR chroma_api.h)

file(GLOB LIME_API_SRC clime_*.cpp)  
file(GLOB LIME_API_HDR clime_*.h)

###################Chroma
find_package(Chroma REQUIRED)

add_library(chroma_api ${CHROMA_API_SRC}) 
#export include interface
target_link_libraries(chroma_api Chroma::chromalib)
get_target_property(CHROMA_INCLUDE_DIRS Chroma::chromalib INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "CHROMA_INCLUDE_DIRS = ${CHROMA_INCLUDE_DIRS}")
target_include_directories(chroma_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CHROMA_INCLUDE_DIRS})  

# All users of this library will need at least C++11
target_compile_features(chroma_api PUBLIC cxx_std_11)
set_target_properties(chroma_api PROPERTIES CXX_EXTENSIONS OFF)

#set_target_properties(chroma_api PROPERTIES POSITION_INDEPENDENT_CODE ON) #-fPIC
install(TARGETS chroma_api RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${CHROMA_API_HDR} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

####################CLime
find_package(CLime REQUIRED)
add_library(lime_api ${LIME_API_SRC})  
#export include interface
target_link_libraries(lime_api CLime::lime)
get_target_property(LIME_INCLUDE_DIRS CLime::lime INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "LIME_INCLUDE_DIRS = ${LIME_INCLUDE_DIRS}")
target_include_directories(lime_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LIME_INCLUDE_DIRS} )  

# All users of this library will need at least C++11
target_compile_features(lime_api PUBLIC cxx_std_11)
set_target_properties(lime_api PROPERTIES CXX_EXTENSIONS OFF)

#set_target_properties(lime_api PROPERTIES POSITION_INDEPENDENT_CODE ON) #-fPIC
install(TARGETS lime_api RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${LIME_API_HDR} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)