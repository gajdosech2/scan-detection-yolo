cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(HIROVisualizer)


include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/HIRO/include/
  ${CMAKE_CURRENT_LIST_DIR}/HIRO/ThirdParty/include/
)

link_directories(
  ${CMAKE_CURRENT_LIST_DIR}/HIRO/lib/Release
  ${CMAKE_CURRENT_LIST_DIR}/HIRO/ThirdParty/lib/Release
)

add_executable(${PROJECT_NAME} 
  main.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} 
  COGS_msvc141_v0.1.0
  GEOM_msvc141_v0.1.0
  GLW_msvc141_v0.1.0
  GUIP_msvc141_v0.1.0
  HIRO_DRAW_msvc141_v0.1.0
  HIRO_msvc141_v0.4.2
  Utils_msvc141_v0.1.0
  assimp-vc140-mt
  CEGUIBase-0
  CEGUICoreWindowRendererSet
  CEGUIExpatParser
  CEGUIOpenGLRenderer-0
  CEGUISILLYImageCodec
  DevIL
  glbinding
  glfw3
  ILU
  ILUT
)

if (MSVC)
  file(GLOB COGS_DLLS ${CMAKE_CURRENT_LIST_DIR}/HIRO/bin/Release/*.dll)
  file(GLOB THIRDPARTY_DLLS ${CMAKE_CURRENT_LIST_DIR}/HIRO/ThirdParty/bin/Release/*.dll)

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${COGS_DLLS} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${THIRDPARTY_DLLS} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
endif (MSVC)