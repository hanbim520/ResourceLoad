
# 添加头文件的查找目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
## 生成各种目标(target)文件: 可执行文件、动态库、静态库
# 指定可执行文件的输出目录，输出到bin下面

file(GLOB_RECURSE project_headers  *.h *.hpp)
file(GLOB_RECURSE project_cpps *.cpp)
source_group("Include" FILES ${project_headers})
set(all_files ${project_headers} ${project_cpps})

add_executable(${PROJECT_NAME} ${project_cpps} ${project_headers})
target_link_libraries(${PROJECT_NAME})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

MESSAGE(STSTUS "###################################")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	MESSAGE(STATUS "current platform: Windows")
	
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

MESSAGE(STSTUS "###################################")


# 设置输库出名为 ResourceLoader => libResourceLoader.a
#SET_TARGET_PROPERTIES(ResourceLoader_a PROPERTIES OUTPUT_NAME "ResourceLoader" CXX)
