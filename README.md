# Studies Cpp

[CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[Learn Cpp](https://www.learncpp.com/)

## Study cases

- [t_cpp20](./t_cpp20/main.cpp): the first test case which is used for testing C++20 compiler

- [t_linkage](./t_linkage/main.cpp): internal linkage vs. external linkage, printing out variables address to check differences

- [t_global_const](./t_global_const/main.cpp): C++17 `inline constexpr`

- [t_constexpr_consteval_fn](./t_constexpr_consteval_fn/main.cpp): constexpr & consteval functions

- [t_fn_template](./t_fn_template/main.cpp): function template

- [t_ref_ptr](./t_ref_ptr/main.cpp): reference & pointer

- [t_struct_size](./t_struct_size/main.cpp): struct size & deduction guild

- [t_fn_ptr](./t_fn_ptr/main.cpp)

- [t_algo](./t_algo/main.cpp)

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
      "${workspaceFolder}/t_cpp20/*.cpp",
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
      "${workspaceFolder}/t_cpp20/*.cpp",
      "-o",
      "${fileDirname}/${fileBasenameNoExtension}"
    ]
    ```

  - Note, `-std=c++2a` means to use C++20 to compile; `"${workspaceFolder}/t_cpp20/*.cpp"` means to scan all the .cpp file under `/t_cpp20` directory.

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
