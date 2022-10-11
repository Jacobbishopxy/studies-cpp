cmake_minimum_required(VERSION 3.5)

project(cpp-starter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(t_cpp20 t_cpp20/main.cpp)

install(
  TARGETS t_cpp20
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION bin/
)
