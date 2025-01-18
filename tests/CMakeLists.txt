macro(my_add_executable TARGET SRC)
  if( USE_CUDA  AND  CUDA_FOUND )
          cuda_add_executable(${TARGET} ${SRC}) # use host c++ inside to link
    set_target_properties(${TARGET} PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)
  elseif ( USE_HIP  AND  HIP_FOUND )
          hip_add_executable(${TARGET} ${SRC}) # use hipcc to link
  else()
          add_executable(${TARGET} ${SRC})
  endif()
endmacro()

######## Chroma-API units CTest ###############
set(TEST_LIST test_chroma_api)

foreach (CUR_TEST ${TEST_LIST})
  my_add_executable(${CUR_TEST} ${CUR_TEST}.cpp)
  target_link_libraries(${CUR_TEST} chroma_api)
  target_include_directories(${CUR_TEST} PRIVATE upp11) # other includes from emdone
  target_compile_features(${CUR_TEST} PUBLIC cxx_std_11)
  add_dependencies(test_all ${CUR_TEST})
  add_test(NAME ${CUR_TEST} COMMAND ${CUR_TEST})
  install(TARGETS ${CUR_TEST} RUNTIME DESTINATION bin)
endforeach(CUR_TEST)


######## LIME-API units CTest ###############
set(TEST_LIST test_clime_reader test_clime_writer)

foreach (CUR_TEST ${TEST_LIST})
  my_add_executable(${CUR_TEST} ${CUR_TEST}.cpp)
  target_link_libraries(${CUR_TEST} lime_api)
  target_include_directories(${CUR_TEST} PRIVATE upp11) # other includes from emdone
  target_compile_features(${CUR_TEST} PUBLIC cxx_std_11)
  add_dependencies(test_all ${CUR_TEST})
  add_test(NAME ${CUR_TEST} COMMAND ${CUR_TEST})
  install(TARGETS ${CUR_TEST} RUNTIME DESTINATION bin)
endforeach(CUR_TEST)