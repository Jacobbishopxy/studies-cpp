# @file:	CMakeLists.txt
# @author:	Jacob Xie
# @date:	2023/12/27 15:57:40 Wednesday
# @brief:


add_executable(cpp20 cpp20/main.cpp cpp20/udf.cpp)

add_executable(linkage linkage/main.cpp linkage/animal_e.cpp linkage/animal_i.cpp)

add_executable(global_const global_const/main.cpp global_const/constants.h)

add_executable(constexpr_consteval_fn constexpr_consteval_fn/main.cpp)

add_executable(fn_template fn_template/main.cpp)

add_executable(ref_ptr ref_ptr/main.cpp)

add_executable(struct_size struct_size/main.cpp)

add_executable(algo algo/main.cpp)

add_executable(class_decl class_decl/main.cpp class_decl/DateProClass.cpp)

add_executable(friend_fn_cls friend_fn_cls/main.cpp friend_fn_cls/Point3d.cpp friend_fn_cls/Vector3d.cpp)

add_executable(timing timing/main.cpp)

add_executable(composition composition/main.cpp composition/Creature.h composition/Point2D.h)

add_executable(aggregation aggregation/main.cpp)

add_executable(association association/main.cpp association/car_driver.h association/doctor_patient.h)

add_executable(virtual_covariant_rtn virtual_covariant_rtn/main.cpp)

add_executable(move_cst_asg move_cst_asg/main.cpp move_cst_asg/arr_cp.h move_cst_asg/arr_mv.h)

add_executable(stl_traits stl_traits/main.cpp)

add_executable(crtp crtp/main.cpp)

add_executable(crtp_et crtp/expression_templates.cpp)
