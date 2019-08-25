PROJECT(ttiger CXX)
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
set(all_files ${project_headers} ${project_cpps} ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})
#install(${PROJECT_NAME} ${project_cpps} ${project_headers}  ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})
# shared library
add_library(${PROJECT_NAME} SHARED  ${project_cpps} ${project_headers}  ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})
#target_link_libraries(Library)
# static library
ADD_LIBRARY(${PROJECT_NAME}_static  STATIC  ${project_cpps} ${project_headers}  ${project_utils_cpps} ${project_utf8_cpps} ${project_win_cpps})
SET_TARGET_PROPERTIES(${PROJECT_NAME}_static  PROPERTIES OUTPUT_NAME "loaderLibrary")
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(${PROJECT_NAME}_static  PROPERTIES CLEAN_DIRECT_OUTPUT 1)
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
		-D IL2CPP_TARGET_WINDOWS
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
 