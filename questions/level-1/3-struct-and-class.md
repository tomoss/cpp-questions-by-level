# 3. Difference between class and struct in C++? What is the difference between struct in C and in C++?

## 📌 Overview

In C++, both `class` and `struct` are user-defined types used to group data and behavior.  
They support:

- Data members (attributes)
- Member functions (methods)
- Constructors and destructors
- Inheritance
- Access control

Despite being very similar, they differ mainly by **default access rules** and **convention of use**.

---

## ⚖️ Comparison

<table border="1" cellpadding="6" cellspacing="0">
  <tr>
    <th>Aspect</th>
    <th>Struct</th>
    <th>Class</th>
  </tr>
  <tr>
    <td>Default access</td>
    <td><code>public</code></td>
    <td><code>private</code></td>
  </tr>
  <tr>
    <td>Default inheritance</td>
    <td><code>public</code></td>
    <td><code>private</code></td>
  </tr>
  <tr>
    <td>Typical use</td>
    <td>Simple data grouping (POD types)</td>
    <td>Encapsulated objects</td>
  </tr>
  <tr>
    <td>Features</td>
    <td>Same as class</td>
    <td>Same as struct</td>
  </tr>
  <tr>
    <td>Convention</td>
    <td>Data-focused, minimal behavior</td>
    <td>Behavior-focused, data hiding</td>
  </tr>
</table>

---

## 📌 Example: Default Access Difference

```cpp
struct StructExample {
    int value;  // public by default
};

class ClassExample {
    int value;  // private by default
};

int main() {
    StructExample s;
    s.value = 10;  // OK - public access
    
    ClassExample c;
    // c.value = 10;  // ERROR: value is private
}
```

---

## 📌 Example: Default Inheritance Difference

```cpp
class Base {
public:
    int val = 5;
};

struct Derived1 : Base {   // public inheritance by default
};

class Derived2 : Base {    // private inheritance by default
};

int main() {
    Derived1 d1;
    std::cout << d1.val << std::endl;   // OK
    
    Derived2 d2;
    // std::cout << d2.val;   // ERROR: not accessible
}
```

---

## 🔹 Convention of use

**Class:** Commonly used for complex objects with internal state

```cpp
class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n), age(a) {}
    void greet() {
        std::cout << "Hello, I am " << name << std::endl;
    }
};
```

**Struct:** Commonly used as simple data containers

```cpp
struct Point {
    int x;
    int y;
};
```

---

## ✅ When to Use What

Even though a `struct` can do everything a `class` can, they are commonly used for different purposes.

### Use `struct` when:
- The object contains only simple data (primitives, C-arrays) and is safe for raw memory operations (like `memcpy`).
- You want everything public by default.
- You're modeling simple *"records"* or DTOs (Data Transfer Objects).
- The type has minimal or no behavior.

### Use `class` when:
- You want encapsulation and data hiding.
- The internal state should be protected.
- You're designing behavior-rich objects.
- You're following OOP principles.

---

## 🆚 Struct in C vs Struct in C++

### In C:

```c
struct Point {
    int x;
    int y;
};

struct Point p1;
```

- Only groups data (no methods, constructors, destructors, etc.)
- No access control.
- Pure data structure.
- Must use `struct` keyword when declaring variables, unless using `typedef`.

The `typedef` workaround:

```cpp
typedef struct Point { 
    int x; 
    int y; 
} Point;

Point p1;  // Now works in C without 'struct' keyword
```

### In C++:

```cpp
struct Point {
    int x;
    int y;
    
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

// No 'struct' keyword needed
Point p1;
```

- Can have methods, constructors, destructors, etc.
- Supports access specifiers (public, private, protected).
- Can use inheritance
- No `struct` keyword needed when declaring variables.
- Almost identical to class

---

## 🔹 Another subtle difference (with templates)

You can declare a template type parameter using `class` or `typename`, but you cannot use `struct`.

```cpp
✅ template <class T>
✅ template <typename T>
❌ template <struct T>
```

**Important note:** Despite using the keyword `class`, the template parameter T can be any type (including structs, primitives, pointers, etc.).

---

## 🧠 Key Takeaway

In C++:

> class and struct are almost identical — the only important differences are default access (public vs private) and convention (data-focused vs behavior-focused).

The choice between them is primarily about expressing intent to other developers.

---


