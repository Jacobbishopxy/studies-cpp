cmake_minimum_required(VERSION 3.5)

project(cpp-starter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp20 learn-cpp-codes/cpp20/main.cpp)
add_executable(linkage_t learn-cpp-codes/linkage/main.cpp)
add_executable(global_const learn-cpp-codes/global_const/main.cpp)
add_executable(constexpr_consteval_fn learn-cpp-codes/constexpr_consteval_fn/main.cpp)
add_executable(fn_template learn-cpp-codes/fn_template/main.cpp)
add_executable(ref_ptr learn-cpp-codes/ref_ptr/main.cpp)
add_executable(struct_size learn-cpp-codes/struct_size/main.cpp)
add_executable(algo learn-cpp-codes/algo/main.cpp)
add_executable(class_decl learn-cpp-codes/class_decl/main.cpp)
add_executable(friend_fn_cls learn-cpp-codes/friend_fn_cls/main.cpp)
add_executable(timing learn-cpp-codes/timing/main.cpp)
add_executable(composition learn-cpp-codes/composition/main.cpp)
add_executable(aggregation learn-cpp-codes/aggregation/main.cpp)
add_executable(association learn-cpp-codes/association/main.cpp)
add_executable(virtual_covariant_rtn learn-cpp-codes/virtual_covariant_rtn/main.cpp)
add_executable(move_cst_asg learn-cpp-codes/move_cst_asg/main.cpp)
add_executable(stl_traits learn-cpp-codes/stl_traits/main.cpp)

install(
  TARGETS
  cpp20
  linkage_t
  global_const
  constexpr_consteval_fn
  fn_template
  ref_ptr
  struct_size
  algo
  class_decl
  friend_fn_cls
  timing
  composition
  aggregation
  association
  virtual_covariant_rtn
  move_cst_asg
  stl_traits
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
  