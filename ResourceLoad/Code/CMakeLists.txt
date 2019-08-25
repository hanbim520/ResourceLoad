PROJECT(EasyLoader CXX)
# 添加头文件的查找目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
## 生成各种目标(target)文件: 可执行文件、动态库、静态库
# 指定可执行文件的输出目录，输出到bin下面

file(GLOB_RECURSE project_headers  *.h *.hpp)
file(GLOB_RECURSE project_cpps *.cpp)
file(GLOB_RECURSE project_utils_cpps ./Utils/*.cpp)
file(GLOB_RECURSE project_utf8_cpps ./Utils/source/utf8/*.cpp )
file(GLOB_RECURSE project_win_cpps ./Windows/*.cpp )
source_group("Include" FILES ${project_headers})
set(LibraryName "EasyLoaderLibrary")
set(all_files ${project_headers} ${project_cpps} ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})
#install(${PROJECT_NAME} ${project_cpps} ${project_headers}  ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})
# shared library
add_library(${LibraryName} SHARED  ${project_cpps} ${project_headers}  ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})
#target_link_libraries(Library)
# static library
ADD_LIBRARY(${LibraryName}_static  STATIC  ${project_cpps} ${project_headers}  ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/bin)   

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/bin) 

SET_TARGET_PROPERTIES(${LibraryName}_static  PROPERTIES OUTPUT_NAME  ${PROJECT_BINARY_DIR}/${LibraryName})
SET_TARGET_PROPERTIES(${LibraryName} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(${LibraryName}_static  PROPERTIES CLEAN_DIRECT_OUTPUT 1)
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


# 设置输库出名为 ResourceLoader => libResourceLoader.a
#SET_TARGET_PROPERTIES(ResourceLoader_a PROPERTIES OUTPUT_NAME "ResourceLoader" CXX)
 