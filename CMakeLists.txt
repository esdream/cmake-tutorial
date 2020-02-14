cmake_minimum_required(VERSION 3.7)

project(cmake_tutorial)

# 添加版本号
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置make install的位置
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# 根据CMAKE_BUILD_TYPE的值不同（Debug或Release），
# cmake会从CMAKE_CXX_FLAGS_DEBUG和CMAKE_CXX_FLAGS_RELEASE中选择对应的选项。
set( CMAKE_BUILD_TYPE "Release" )
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -Wall -g -ggdb" )
else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall" )
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )    
message( "Build Type:" ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS} )

# 检查系统是否支持pow函数,调用的是cmake提供的checkfunctionexists工具
include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
message("CMAKE_ROOT: " ${CMAKE_ROOT})
check_function_exists(pow HAVE_POW)
# 加入一个配置头文件，用于处理CMake对源码的设置
message("Value of HAVE_POW: " ${HAVE_POW})
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/config.h"
)

# 新建选项确定是否使用自己的MathFunctions库，默认选项为ON
# 正常不是应该ON是打开，OFF是关闭吗？为什么这里选择OFF的时候是使用USE_MYMATH，
# 选择ON的时候是关闭USE_MYMATH？？？？
# 而我在cmake-gui里操作时，USE_MYMATH选项打上勾就是使用，去掉勾就是关闭，这才是
# 符合人常识的啊
# option (USE_MYMATH "Use provide math implementation" ON)

# 是否加入MathFunction库
# if (NOT HAVE_POW)
include_directories ("${PROJECT_SOURCE_DIR}/math")
# 添加math子目录
add_subdirectory(math)
set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
# endif (NOT HAVE_POW)

# 查找当前目录下的所有源文件
# 并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(cmake_tutorial tutorial.cc)
# 添加链接库
message("EXTRA_LIBS: " ${EXTRA_LIBS})
target_link_libraries(cmake_tutorial ${EXTRA_LIBS})

# 指定安装路径
# 这里和math子目录CMakeLists.txt中的bin和include，
# 在Linux中默认指的是/usr/local/bin和/usr/local/include。
# 在Windows中默认是在C:/Program Files (x86)下创建project的目录。
# 这些可以通过在cmake命令中添加
# -DCMAKE_INSTALL_PREFIX=安装目录 
# 实现，可以在CMakeLists.txt中加上：set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
install (TARGETS cmake_tutorial DESTINATION bin)
install (FILES "${PROJECT_SOURCE_DIR}/config.h"
         DESTINATION include)

# 启用测试
enable_testing()

# 测试程序是否成功运行
add_test(test_run cmake_tutorial)

# # 构建一个CPack安装包
# include(InstallRequiredSystemLibraries)
# set (CPACK_RESOURCE_FILE_LICENSE
#      "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
# set (CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
# set (CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
# set (CPACK_SOURCE_GENERATOR WIX)
# # 设置版本名称
# set(PROJECT_VERSION_FULL ${VERSION_MAJOR}.${VERSION_MINOR})
# set (CPACK_SOURCE_PACKAGE_FILE_NAME cmake_tutorial-${PROJECT_VERSION_FULL})
# include (CPack)