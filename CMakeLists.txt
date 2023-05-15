cmake_minimum_required(VERSION 3.10)  # 设置CMake最低版本要求

project(ProcessTree)  # 设置项目名称

set(CMAKE_CXX_STANDARD 17)  # 设置C++标准为C++17
set(EXPORT_COMPILE_COMMANDS ON)
add_executable(ProcessTree pstree.cc)  # 添加可执行文件
