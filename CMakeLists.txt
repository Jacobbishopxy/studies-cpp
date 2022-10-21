cmake_minimum_required(VERSION 3.5)

project(cpp-starter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(t_cpp20 t_cpp20/main.cpp)
add_executable(t_linkage_t t_linkage/main.cpp)
add_executable(t_global_const t_global_const/main.cpp)
add_executable(t_constexpr_consteval_fn t_constexpr_consteval_fn/main.cpp)
add_executable(t_fn_template t_fn_template/main.cpp)
add_executable(t_ref_ptr t_ref_ptr/main.cpp)
add_executable(t_struct_size t_struct_size/main.cpp)

install(
  TARGETS
  t_cpp20
  t_linkage_t
  t_global_const
  t_constexpr_consteval_fn
  t_fn_template
  t_ref_ptr
  t_struct_size
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
