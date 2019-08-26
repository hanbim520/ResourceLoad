# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (EasyLoader)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(Code)
# include directories
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/Code
  ${PROJECT_SOURCE_DIR}/Protobuf
  ${PROJECT_SOURCE_DIR}/Sqlite/source
)
# lib directories
LINK_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/../Protobuf/Lib
  ${PROJECT_SOURCE_DIR}/Sqlite/Lib
)
#指定protobuf
include_directories(${PROJECT_SOURCE_DIR}/protobuf)
link_directories(${PROJECT_SOURCE_DIR}/Protobuf/Lib)
#sqlite3
include_directories(${PROJECT_SOURCE_DIR}/Sqlite/source)
link_directories(${PROJECT_SOURCE_DIR}/Sqlite/Lib)

# 指定生成目标 
add_executable(EasyLoader ./ResourceLoad/main.cpp
			./ResourceLoad/DataInfoProto.pb.cc )


TARGET_LINK_LIBRARIES(EasyLoader 
	EasyLoaderLibrary
	libprotobuf.lib
	Sqlite3.lib
	)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)




MESSAGE(STSTUS "###################################")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	MESSAGE(STATUS "current platform: Linux ")
	add_definitions(
        -D TARGET_UNIX
    )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	MESSAGE(STATUS "current platform: Windows")
	add_definitions(
        -D TARGET_WIN
		-D EaseLoad_TARGET_WINDOWS
		-D _DEBUG
    )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    
MESSAGE(STSTUS "###################################")
