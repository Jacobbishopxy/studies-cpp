#include <stdio.h>

// ==================================================
// Reference
// ==================================================
void test_ref() {
  const int x{5};
  int y{6};
  int z{7};

  /**
   * @brief Reference
   */
  int& ref0{y};
  ref0 = z; // 看似修改引用指向 z，实则将 z 赋值到 y

  printf("ref0: %d\n", ref0);
  printf("y: %d\n", y);

  /**
   * @brief Reference to a const value
   */
  const int& ref1{x};
}

// ==================================================
// Pointer
// ==================================================
void test_ptr() {
  const int x{5};
  int y{6};
  int z{7};

  /**
   * @brief Pointer
   */
  int* ptr0{&y};
  printf("ptr0: %d\n", *ptr0);

  ptr0 = &z; // 指向 z
  printf("ptr0: %d\n", *ptr0);
  printf("y: %d\n", y);
  printf("z: %d\n", z);

#if 0
  *ptr0 = y; // 修改 z 的值成为 y
  printf("ptr0: %d\n", *ptr0);
  printf("y: %d\n", y);
  printf("z: %d\n", z);
#endif

  /**
   * @brief Pointer to a const value
   *
   * 仅可以重新指向（reseat），不可以解引用修改值
   */
  const int* ptr1{&x};
  printf("ptr1: %d\n", *ptr1);

  ptr1 = &y; // 指向 y
  printf("ptr1: %d\n", *ptr1);
  printf("x: %d\n", x);
  printf("y: %d\n", y);

  // *ptr1 = z; // 即使已经指向了可变左值，也无法解引用

  /**
   * @brief Const pointer
   *
   * 仅可以解引用修改值，不可以重新指向（reseat）
   */
  int* const ptr2{&y};
  printf("ptr2: %d\n", *ptr2);

  // ptr2 = &z; // 一旦初始化了 y 的地址后便不可再被修改

#if 0
  *ptr2 = z; // 修改 y 的值成为 z
  printf("ptr2: %d\n", *ptr2);
  printf("y: %d\n", y);
  printf("z: %d\n", z);
#endif

  /**
   * @brief Const pointer to a const value
   *
   * 既不可以重新指向，也不可以解引用修改值
   */
  const int* const ptr3{&x};
  // ptr3 = &y; // 既不可以重新指向
  // *ptr3 = y; // 也不可以修改值
}

int main() {

/**
 * const 即不可再次被赋值，const 右侧为不可再次被赋值类型。
 * - const int* 意为不可解引用
 * - const ptr2{&x} 意为不可再重新指向
 */
#if 0
  int x{0};

  int* ptr0{&x};
  const int* ptr1{&x};
  int* const ptr2{&x};
  const int* const ptr3{&x};
#endif

  test_ref();
  test_ptr();

  return 0;
}
