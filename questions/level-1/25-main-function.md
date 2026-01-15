# 25. Can we overload the ```main()``` function?

No, you **cannot** overload the ```main()``` function in C++.

**The language standard forbids it.** The C++ standard explicitly states that ```main()``` shall not be overloaded. It must have **one** of these specific signatures:

```cpp
int main()
int main(int argc, char* argv[])
```

**It would break the program's entry point.** The ```main()``` function serves as the entry point for program execution. The compiler and runtime environment look for a specific signature of ```main()``` to start your program. Overloading it would create ambiguity about which version should be called when the program starts.

Attempting to overload it causes compilation errors. If you try something like:

```cpp
int main() { return 0; }
int main(int x) { return 0; }  // Error!
```

---
