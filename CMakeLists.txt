cmake_minimum_required(VERSION 3.5)

project(cpp-starter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(t_cpp20 t_cpp20/main.cpp)
add_executable(t_linkage_t t_linkage/main.cpp)

install(
  TARGETS t_cpp20 t_linkage_t
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION bin/
)
