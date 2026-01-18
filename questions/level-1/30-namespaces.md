# 30. What are namespaces in C++? Why do we use them?

## 💡Definition

In C++, a **namespace** is a mechanism that allows the logical grouping of identifiers (variables, functions, classes, and other entities) under a common name.

**Namespaces** prevent name conflicts between identifiers that have the same name but originate from different parts of a program or different libraries.

---

## 💡 Why namespaces matter

Imagine you're building a graphics application and you include two libraries:

```cpp
// Library A defines:
class Vector {
    // Represents a mathematical vector
};

// Library B also defines:
class Vector {
    // Represents a collection/container
};

// Without namespaces, this causes a compilation error!
Vector v; // Which Vector? Compiler doesn't know!
```

With namespaces, this problem is solved:

```cpp
namespace Math {
    class Vector {
        // Mathematical vector
    };
}

namespace Collections {
    class Vector {
        // Container
    };
}

// Now it's clear which one you want:
Math::Vector mathVec;
Collections::Vector container;
```

---

## 💡 Defining and using namespaces

You create a namespace using the ```namespace``` keyword.

```cpp
// Create a namespace 'MyMath'
namespace MyMath {
    const double PI = 3.14159;

    int add(int a, int b) {
        return a + b;
    }

    class Calculator {
        // ... class definition
    };
}
```

### 🔹Namespace and classes

**Good Practice:** Wrap both declaration and definition in the namespace → don't just wrap the header or only the source file. It ensures consistency and avoids linkage issues.

In header file (calculator.h):

```cpp
namespace MyMath {
    class Calculator {
    public:
        int multiply(int a, int b);  // Declaration
    };
}
```

In source file (calculator.cpp):

```cpp
#include "calculator.h"

namespace MyMath {
    int Calculator::multiply(int a, int b) {  // Definition
        return a * b;
    }
}
```

### 🔹Accessing members

#### 1️⃣ Scope Resolution Operator ( ```::``` )

**Best for:** General use, especially in header files.

This is the safest and most explicit method. You fully qualify the name by prefixing it with the namespace.

```cpp
#include <iostream>

int main() {
    double circ = 2 * MyMath::PI * 10.0;
    int sum = MyMath::add(5, 3);
    
    std::cout << "Sum: " << sum << std::endl; // Using the 'std' namespace
}
```

#### 2️⃣ ```using``` Declaration

**Best for:** Use inside source files (.cpp) or within a function to simplify code without causing broad name conflicts.

This brings **one specific member** from a namespace into the current scope. It's a safe, targeted way to avoid retyping the namespace prefix for identifiers you use frequently.

```cpp
#include <iostream>

// Bring only 'cout' and 'endl' into this file's scope
using std::cout;
using std::endl;

// Bring in 'add' and 'PI' from MyMath
using MyMath::add;
using MyMath::PI;

int main() {
    cout << "PI is: " << PI << endl;
    cout << "Sum: " << add(5, 3) << endl;
}
```

#### 3️⃣ ```using``` Directive (using namespace)

**Best for:** Very limited use, such as in short, simple .cpp files for tutorials or quick tests.

⛔ Never use ```using namespace``` in header files.

This brings ***all members*** from a namespace into the current scope. This is generally ***discouraged*** in modern C++ because it completely ***defeats the purpose of namespaces*** by dumping all the names into your current scope, leading to a ***high risk of name collisions*** and ***ambiguity***.

```cpp
#include <iostream>

// DANGER: Brings in ALL names from std (cout, endl, string, vector, etc.)
// and all names from MyMath (PI, add, Calculator).
using namespace std;
using namespace MyMath;

int main() {
    // Ambiguity could easily happen here.
    // What if another included library also had a function named 'add'?
    cout << "Sum: " << add(5, 3) << endl;
}
```

---

## 💡 Best practices

* ✅ DO → Use namespaces to group related code logically.
* ✅ DO → Use namespace aliases for readability.
* ✅ DO → Use using declarations only inside functions or limited scopes.
* 🚫 AVOID → Declaring everything in the global namespace, without wrapping them inside a namespace.
* 🚫 AVOID → Using ```using namespace``` in headers.
* 🚫 AVOID → Putting ```using namespace``` in global scope (causes ambiguity).

---

## 💡 Global Scope Qualifier

If you have a local variable ```x``` and a global variable ```x```, how do you reach the global one?

**Solution:** ```::x``` (with no namespace before the colons).

```cpp
int x = 42;

int main()
{
    int x = 43;

    std::cout << ::x << std::endl; // 42
    std::cout << x << std::endl; // 43
}
```

**Note:** While ```::x``` is useful to know, having shadowing variables (local and global with the same name) is generally considered poor practice.

---

## 💡 Nested namespaces

You can nest namespaces to create more complex hierarchies.

```cpp
namespace Outer {
    namespace Inner {
        void func() {
            std::cout << "Inside Inner Namespace" << std::endl;
        }
    }
}

int main() {
    Outer::Inner::func();
}
```

C++17 shorthand:

```cpp
namespace Outer::Inner {
    void func() {
        std::cout << "Inside Inner Namespace" << std::endl;
    }
}
```

---

## 💡 Namespace aliases

Useful when the namespace name is long:

```cpp
namespace Deeply::Nested::Project {
    void run() { std::cout << "Running...\n"; }
}

namespace P = Deeply::Nested::Project; // alias
P::run();
```

---

## 💡 Anonymous (unnamed) namespaces

An unnamed namespace automatically gives internal linkage to everything inside it — meaning it’s visible only in the current translation unit (file).

In simpler terms, an unnamed namespace makes its contents visible only within the current file. Think of it as a way to create "file-private" functions and variables.

**Why use it:** Instead of marking things as ```static``` to limit their visibility to one file, you can put them in an anonymous namespace.

```cpp
// In myfile.cpp
namespace {
    int secret = 100;  // Only visible in this file
    
    void helperFunction() {
        // This function can't be called from other files
    }
}

int main() {
    std::cout << secret;  // OK - we're in the same file
    helperFunction();     // OK - we're in the same file
    return 0;
}
```

---

## 💡 Inline namespaces (C++11)

* Allows versioning within namespaces.
* Used to expose a default version of an API, while keeping older versions accessible.

```cpp
namespace Library {
    inline namespace V1 {  // Default namespace version
        void hello() {
            std::cout << "Library Version 1" << std::endl;
        }
    }
    
    namespace V2 {
        void hello() {
            std::cout << "Library Version 2" << std::endl;
        }
    }
}

int main() {
    Library::hello();  // Calls V1::hello() by default
    Library::V2::hello();  // Calls V2::hello()
}
```

---

