# @file:	CMakeLists.txt
# @author:	Jacob Xie
# @date:	2023/12/27 15:57:49 Wednesday
# @brief:


cmake_minimum_required(VERSION 3.14)

project(studies-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ================================================================================================
# Sub dir
# ================================================================================================

add_subdirectory(./learn-cpp-codes lcc)
add_subdirectory(./eigen-tutorial et)
