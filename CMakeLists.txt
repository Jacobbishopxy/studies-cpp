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
add_executable(t_algo t_algo/main.cpp)
add_executable(t_class t_class/main.cpp)
add_executable(t_friend_fn_cls t_friend_fn_cls/main.cpp)
add_executable(t_timing t_timing/main.cpp)
add_executable(t_composition t_composition/main.cpp)
add_executable(t_aggregation t_aggregation/main.cpp)
add_executable(t_association t_association/main.cpp)
add_executable(t_virtual_covariant_rtn t_virtual_covariant_rtn/main.cpp)

install(
  TARGETS
  t_cpp20
  t_linkage_t
  t_global_const
  t_constexpr_consteval_fn
  t_fn_template
  t_ref_ptr
  t_struct_size
  t_algo
  t_class
  t_friend_fn_cls
  t_timing
  t_composition
  t_aggregation
  t_association
  t_virtual_covariant_rtn
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
