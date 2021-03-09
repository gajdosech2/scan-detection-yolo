cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(BinLocalization)


find_package(Torch REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR}/libtorch)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/../libraries/include/
  ${CMAKE_CURRENT_LIST_DIR}/../libraries/include/windows_specific/
  ${CMAKE_CURRENT_LIST_DIR}/../codebase/libs/COGS/include/
  ${CMAKE_CURRENT_LIST_DIR}/../codebase/libs/Utils/include/
)

link_directories(
  ${CMAKE_CURRENT_LIST_DIR}/../libraries/lib/${CMAKE_BUILD_TYPE}/OpenCV/
  ${CMAKE_CURRENT_LIST_DIR}/TEMPLIBS/lib/${CMAKE_BUILD_TYPE}/ #TEMP
)

add_executable(${PROJECT_NAME} 
  ScanDataset.h
  ScanDataset.cpp 
  BinLocalization.cpp
  COGSToTensor.h
  Converters.h
  Converters.cpp  
  Functions.h
  networks/ClassificationNetwork.h
  networks/MergeNet.h
  networks/ModelTransformNet.h
  networks/ScanFeatureNet.h
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_range_for)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} 
  ${TORCH_LIBRARIES}
  opencv_core400
  opencv_imgproc400
  opencv_imgcodecs400
  opencv_highgui400
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  target_link_libraries(${PROJECT_NAME} COGS_msvc141_v0.1.0 Utils_msvc141_v0.1.0) 
else()  
  target_link_libraries(${PROJECT_NAME} COGS_msvc141_v0.1.0_d Utils_msvc141_v0.1.0_d) 
endif()

if (MSVC)
  file(GLOB TORCH_DLLS ${TORCH_INSTALL_PREFIX}/lib/*.dll)
  file(GLOB OPENCV_DLLS ${CMAKE_CURRENT_LIST_DIR}/../libraries/dll/${CMAKE_BUILD_TYPE}/OpenCV/*.dll)
  file(GLOB LIBCRYPTO_DLL ${CMAKE_CURRENT_LIST_DIR}/../libraries/dll/${CMAKE_BUILD_TYPE}/libcrypto-1_1-x64.dll)
  file(GLOB COGS_DLLS ${CMAKE_CURRENT_LIST_DIR}/TEMPLIBS/bin/${CMAKE_BUILD_TYPE}/*.dll)

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TORCH_DLLS} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OPENCV_DLLS} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${COGS_DLLS} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBCRYPTO_DLL} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
endif (MSVC)