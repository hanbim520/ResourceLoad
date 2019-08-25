# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (EasyLoader)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(Code)

# 指定生成目标 
add_executable(EasyLoader ./ResourceLoad/main.cpp)

# include directories
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/Code
)

# lib directories
LINK_DIRECTORIES(
  ${PROJECT_BINARY_DIR}/lib
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)