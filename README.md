# Studies Cpp

A personal C-plus-plus study note.

## References

[CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[Learn Cpp](https://www.learncpp.com/)

## Practices

1. [cpp20](./learn-cpp-codes/cpp20/main.cpp): the first test case which is used for testing C++20 compiler

1. [linkage](./learn-cpp-codes/linkage/main.cpp): internal linkage vs. external linkage, printing out variables address to check differences

1. [global_const](./learn-cpp-codes/global_const/main.cpp): C++17 `inline constexpr`

1. [constexpr_consteval_fn](./learn-cpp-codes/constexpr_consteval_fn/main.cpp): constexpr & consteval functions

1. [fn_template](./learn-cpp-codes/fn_template/main.cpp): function template

1. [ref_ptr](./learn-cpp-codes/ref_ptr/main.cpp): reference & pointer

1. [struct_size](./learn-cpp-codes/struct_size/main.cpp): struct size & deduction guild

1. [fn_ptr](./learn-cpp-codes/fn_ptr/main.cpp): function pointer

1. [algo](./learn-cpp-codes/algo/main.cpp): `#include <algorithm>` standard library usage

1. [class](./learn-cpp-codes/class/main.cpp): class declaration. Non-reusable class under its usage file; otherwise, split into `.h` and `.cpp` file (one for declaration and one for implementation)

1. [friend_fn_cls](./learn-cpp-codes/friend_fn_cls/main.cpp): `friend` keyword can be used on a class or a member function. The former one means granting all members' accessibility; the latter one means granting specified member function the accessibility

1. [composition](./learn-cpp-codes/composition/main.cpp)

1. [aggregation](./learn-cpp-codes/aggregation/main.cpp)

1. [association](./learn-cpp-codes/association/main.cpp)

1. [timing](./learn-cpp-codes/timing/main.cpp): a simple helper tool to collect elapsed time

1. [multiple_inheritance](./learn-cpp-codes/multiple_inheritance/main.cpp): differences among `public`/`protected`/`private` and the usage of mixin

1. [virtual_covariant_rtn](./learn-cpp-codes/virtual_covariant_rtn/main.cpp): virtual function's covariant return type

1. [virtual_quiz](./learn-cpp-codes/virtual_quiz/main.cpp): class inheritance with virtual function and operation<<

1. [std_init_list](./learn-cpp-codes/std_init_list/main.cpp): using `std::initializer_list` as a constructor's parameter, and by overloading operator= and operator[], customize a container class

1. [partial_template_spec](./learn-cpp-codes/partial_template_spec/main.cpp): partial template specification for pointer and full template specification for `char*`

1. [template_quiz](./learn-cpp-codes/template_quiz/main.cpp)

1. [exception](./learn-cpp-codes/exception/main.cpp): customized exception (class/enum class)

## Vscode settings

- C++ format in `settings.json`:

  ```json
  "clang-format.executable": "/opt/homebrew/bin/clang-format",
  "clang-format.style": "google",
  "clang-format.language.c.enable": true,
  "[c]": {
    "editor.defaultFormatter": "xaver.clang-format",
    "editor.wordBasedSuggestions": false,
    "editor.suggest.insertMode": "replace",
    "editor.semanticHighlighting.enabled": true
  }
  ```

  Note "clang-format.executable" directory can be found by `whereis clang-format`.

- Vscode user setting in order to solve [pointer-alignment issue](https://stackoverflow.com/a/52200544): `"C_Cpp.clang_format_fallbackStyle": "{ ColumnLimit: 120, PointerAlignment: Left}"`.

- Vscode setting `.vscode/tasks.json` (auto generated by vscode, but should be manually modified, [reference](https://www.cnblogs.com/gundam00/p/13447602.html))

  - Mac, for each task's `args`:

    ```json
    "args": [
      "-std=c++2a",
      "-fcolor-diagnostics",
      "-fansi-escape-codes",
      "-g",
      "${workspaceFolder}/cpp20/*.cpp",
      "-o",
      "${fileDirname}/${fileBasenameNoExtension}"
    ]
    ```

  - Ubuntu, for each task's `args`:

    ```json
    "args": [
      "-std=c++2a",
      "-fdiagnostics-color=always",
      "-g",
      "${workspaceFolder}/cpp20/*.cpp",
      "-o",
      "${fileDirname}/${fileBasenameNoExtension}"
    ]
    ```

  - Note, `-std=c++2a` means to use C++20 to compile; `"${workspaceFolder}/cpp20/*.cpp"` means to scan all the .cpp file under `/cpp20` directory.

- Each time adding an executable, add a new task as well.

- Vscode intellisense `.vscode/c_cpp_properties.json`

  - Ubuntu:

    ```json
    "configurations": [
      {
        ...
        "configurationProvider": "ms-vscode.makefile-tools",
        "compileCommands": "${workspaceFolder}/build/compile_commands.json"
      }
    ]
    ```

## Todo

- [catch2 test framework](https://github.com/catchorg/Catch2)
- [vscode with googletest](https://computingonplains.wordpress.com/building-c-applications-with-visual-studio-code-unit-testing-with-googletest/)
- [upgrade ubuntu version on wsl](https://dev.to/equiman/upgrade-ubuntu-version-on-wsl-3h10)
- [discussion on googletest with CMake](https://stackoverflow.com/questions/62910867/how-to-run-tests-and-debug-google-test-project-in-vs-code)
