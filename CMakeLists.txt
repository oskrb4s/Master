cmake_minimum_required(VERSION 3.1.0)

project(Master_v3)
find_package(ITK REQUIRED)
FILE(GLOB Header "*.h")
FILE(GLOB Sources "*.cpp")
include(${ITK_USE_FILE})
ADD_EXECUTABLE(Master3 MACOSX_BUNDLE ${Sources} ${Header})
target_link_libraries(Master3 ${ITK_LIBRARIES})

