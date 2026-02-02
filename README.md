# C++ Questions & Answers

A collection of C++ questions with answers and code examples.

## Questions

<!-- GENERATED:START -->

### Level 1

- [3. Difference between class and struct in C++? What is the difference between struct in C and in C++?](questions/level-1/3-struct-and-class.md)
- [11. What Is a Default Constructor?](questions/level-1/11-default-constructor.md)
- [12. Can constructors be virtual? Why/why not?](questions/level-1/12-virtual-constructor.md)
- [13. What is a destructor, and when is it called?](questions/level-1/13-destructor.md)
- [16. What are friend functions and friend classes?](questions/level-1/16-friend-keyword.md)
- [17. What is the `this` pointer?](questions/level-1/17-this-pointer.md)
- [22. Explain const correctness (const int*, int* const, const methods).](questions/level-1/22-const.md)
- [25. Can we overload the ```main()``` function?](questions/level-1/25-main-function.md)
- [30. What are namespaces in C++? Why do we use them?](questions/level-1/30-namespaces.md)

### Level 2

- [7. Explain Rule of 3, Rule of 5, Rule of 0.](questions/level-2/7-rule-of-three-five-zero.md)
- [15. What is a dangling pointer?](questions/level-2/15-dangling-pointer.md)
- [20. What is object slicing?](questions/level-2/20-object-slicing.md)
- [21. What is multiple inheritance? What are the problems with it?](questions/level-2/21-multiple-inheritance.md)
- [22. What is the diamond problem?](questions/level-2/22-diamond-problem.md)
- [23. Explain virtual inheritance.](questions/level-2/23-virtual-inheritance.md)
- [36. What is RAII? Why is it important in C++?](questions/level-2/36-raii.md)

### Level 3

- [18. What is std::lock_guard vs std::unique_lock?](questions/level-3/18-locks.md)
- [25. What is mutable keyword in C++?](questions/level-3/25-mutable-keyword.md)

### Level 4

- [8. Explain inline namespaces.](questions/level-4/8-inline-namespaces.md)

<!-- GENERATED:END -->

## 🏗️ Build Instructions for examples

### Configure Workspace (Run Once)

🖥️ Windows – MSVC (Visual Studio 2022) - ```cmake --preset windows-msvc-debug```

🖥️ Windows – MinGW (GCC, Debug) - ```cmake --preset windows-mingw-gcc-debug```

🖥️ Windows – MinGW (Clang, Debug) - ```cmake --preset windows-mingw-clang-debug```

🐧 Linux – GCC (Ninja, Debug) - ```cmake --preset linux-gcc-debug```

🐧 Linux – Clang (Ninja, Debug) - ```cmake --preset linux-clang-debug```

### Build All (Debug)

🖥️ Windows – MSVC - ```cmake --build --preset windows-msvc-debug --parallel```

🖥️ Windows – MinGW (GCC) - ```cmake --build --preset windows-mingw-gcc-debug --parallel```

🖥️ Windows – MinGW (Clang) - ```cmake --build --preset windows-mingw-clang-debug --parallel```

🐧 Linux – GCC - ```cmake --build --preset linux-gcc-debug --parallel```

🐧 Linux – Clang - ```cmake --build --preset linux-clang-debug --parallel```

