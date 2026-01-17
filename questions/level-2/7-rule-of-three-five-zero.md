# 7. Explain Rule of 3, Rule of 5, Rule of 0.

## 💡 Definition

Rule of Three, Rule of Five, and Rule of Zero are C++ programming guidelines related to how a class should handle resource management, specifically by defining (or not defining) its special member functions.

[The rule of three/five/zero - cppreference](https://en.cppreference.com/w/cpp/language/rule_of_three.html)

---

## 💡 Rule of Three

If a class requires a user-defined destructor, a user-defined copy constructor, or a user-defined copy assignment operator, it almost certainly requires all three.

The three special member functions are:

* Destructor → ```~ClassName()```
* Copy Constructor → ```ClassName(const ClassName& other)```
* Copy Assignment Operator → ```ClassName& operator=(const ClassName& other)```

### 🔹Why This Rule Exists

If a class manages resources manually (such as dynamic memory allocation with new/delete, file handles, or network sockets), the compiler-generated copy operations will perform memberwise copy, which is shallow for raw pointers. This means they copy pointer values rather than the underlying resources, leading to serious problems like double deletion, memory leaks or dangling pointers.

By explicitly defining all three functions, you ensure proper deep copying and resource cleanup.

---

## 💡 Rule of Five (C++11 and later)

C++11 introduced move semantics - a way to efficiently transfer resources from one object to another instead of copying them. This is particularly valuable for expensive-to-copy objects. This updated the rule.

Now there are two more special member functions to consider:

* Move Constructor → ```ClassName(ClassName&& other) noexcept```
* Move Assignment Operator → ```ClassName& operator=(ClassName&& other) noexcept```

If a class has a user-defined destructor, copy-constructor, or copy-assignment operator present, the compiler will not automatically generate the move constructor or move assignment operator.

This means that if you follow the Rule of Three, but not the Rule of Five, your class will become copy-only and lose the performance benefits of moving. You must explicitly add the move operations.

Unlike Rule of Three, failing to provide move constructor and move assignment operator is usually not an error, but a missed optimization opportunity.

---

## 💡 Rule of Zero (C++11 and later)

If your class doesn’t directly manage resources, don’t define any special member functions — let the compiler generate them automatically.

This is the modern C++ approach and should be your default choice.

This rule emphasizes that your class shouldn’t handle manual resource management in the first place. Instead, you should use dedicated RAII types that manage their resources automatically and internally as member variables.

Examples include: ```std::unique_ptr```, ```std::shared_ptr```, ```std::vector```, ```std::string```, ```std::fstream`` and other standard types that follow RAII principle.

---

## 💡 Examples

### 🔹Example of Rule of Three

```cpp
class RuleOfThree {
private:
    int* data;
public:
    // Constructor
    RuleOfThree(int value) : data(new int(value)) {}

    // Destructor
    ~RuleOfThree() {
        delete data;
    }

    // Copy Constructor (Deep Copy)
    RuleOfThree(const RuleOfThree& other) {
        data = new int(*other.data);
    }

    // Copy Assignment Operator (Deep Copy)
    RuleOfThree& operator=(const RuleOfThree& other) {
        if (this != &other) {  // Prevent self-assignment
            delete data;  // Clean up existing resource
            data = new int(*other.data);
        }
        return *this;
    }
};
```

### 🔹Example of Rule of Five

```cpp
class RuleOfFive {
private:
    int* data;
public:
    // Constructor
    RuleOfFive(int value) : data(new int(value)) {}

    // Destructor
    ~RuleOfFive() {
        delete data;
    }

    // Copy Constructor (Deep Copy)
    RuleOfFive(const RuleOfFive& other) {
        data = new int(*other.data);
    }

    // Copy Assignment Operator (Deep Copy)
    RuleOfFive& operator=(const RuleOfFive& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    // Move Constructor (Transfers Ownership)
    RuleOfFive(RuleOfFive&& other) noexcept : data(other.data) {
        other.data = nullptr;  // Leave other in a valid state
    }

    // Move Assignment Operator (Transfers Ownership)
    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};
```

Why ```noexcept```? Move operations should be marked ```noexcept``` because many standard library containers (like ```std::vector```) will only use move operations if they're guaranteed not to throw. Otherwise, they fall back to copying for exception safety.

### 🔹Example of Rule of Zero

```cpp
#include <memory>

class RuleOfZero {
private:
    std::unique_ptr<int> data;  // Smart pointer handles memory

public:
    // Constructor
    RuleOfZero(int value) : data(std::make_unique<int>(value)) {}

    // No need to define destructor, copy/move constructors, or assignment operators!
};
```

Important: Since ```std::unique_ptr``` is move-only, this class is also move-only (cannot be copied). If you need copying, use ```std::shared_ptr``` for shared ownership or another RAII wrapper if you need deep copies.

Since ```std::unique_ptr``` automatically handles memory cleanup, we don't need to manually define special functions. This approach prevents resource leaks and avoids errors like double deletion.

**Another example:**

```cpp
class RuleOfZeroBuffer {
    std::vector<int> data; // manages dynamic memory internally
    std::string name; // manages its own buffer
public:
    RuleOfZeroBuffer(std::string n, int count) : name(std::move(n)), data(count, 0) {}


    void set(int index, int value) {
        data.at(index) = value; // bounds-checked access
    }

    int get(int index) const {
        return data.at(index);
    }
};
```

---

## 💡 Key Takeaways

* If you manage resources manually → think Rule of Three/Five.

* If you don’t → follow Rule of Zero.

* Prefer composition from RAII types over owning raw resources.

* Modern C++ code should default to Rule of Zero.

---

## 🧪 Code example
- [`../../examples/level-2/7-rule-of-three-five-zero`](../../examples/level-2/7-rule-of-three-five-zero)
