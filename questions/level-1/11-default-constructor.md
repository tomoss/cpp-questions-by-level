# 11. What Is a Default Constructor?

## 💡 Definition

A **default constructor** is a constructor that can be invoked **without passing any arguments**.

A constructor qualifies as a *default constructor* if:
- It has no parameters, or
- All parameters have default values

It is automatically called when an object is created without providing any arguments.

---

## 💡 Types of Default Constructors

### 1️⃣ Compiler-Generated Default Constructor (Implicit)

```cpp
class MyClass {
    // No user-declared constructors
};
// Compiler generates: MyClass::MyClass() {}
```

**Important:** 

* Performs default initialization (leaves built-in types uninitialized, i.e. indeterminate values) if called as ```MyClass c;```.
* Performs value initialization (zeroes out primitives) if called as ```MyClass c{};```.

```cpp
class Entity {
public:
    int x;
};

int main() {
    Entity e1;
    std::cout << e1.x << std::endl; // Undefined behavior (indeterminate value)

    Entity e2{};
    std::cout << e2.x << std::endl; // Output: 0
}
```

### 2️⃣ User-Defined Default Constructor (Explicit)

#### 🔹Example when it has no parameters

```cpp
class MyClass {
public:
    MyClass() {
        // initialization code
    }
};

class Person {
    std::string name;
    int age;
public:
    Person() : name("Unknown"), age(0) {}
};
```

#### 🔹Example when all its parameters have default values

```cpp
class MyClass {
public:
    MyClass(int px = 42, double py = 3.14)
        : x(px), y(py) {
        std::cout << "x = " << x << ", y = " << y << std::endl;
    }
private:
    int x;
    double y;
};

int main() {
    MyClass c;  // OK — calls default constructor
}
```

---

## 💡 Key points

**The compiler provides a default constructor**

* If you do **not** define any constructor in your class, the compiler will automatically generate one for you.

**The compiler no longer provides a default constructor**

The compiler won't generate a default constructor if:

* You **define** any kind of **constructor** (for example, one with parameters), the compiler will no longer automatically generate a default constructor.

* There are **const** or **reference** members without in-class initializers - the compiler cannot automatically generate a default constructor because these members must be initialized.

```cpp
class Example1 {
public:
    const int x; // const member without in-class initializer
    int& ref;    // reference member without in-class initializer
    // Compiler CANNOT generate a default constructor
};

class Example2 {
public:
    const int x = 10; // const member with in-class initializer
    int value = 42;
    int& ref = value; // reference member with in-class initializer
    // Compiler CAN generate a default constructor
};

int main() {
    // Example1 obj1;        // ERROR! No default constructor
    Example2 obj2;           // OK - default constructor generated
}
```

**You can define your own custom Default Constructor**

* If you need both a parameterized constructor and a default constructor, you must define the default one explicitly yourself.

---

## 💡 Explicitly defaulted constructor (C++11)

You can explicitly mark a constructor (or other special member functions) as defaulted using the ```= default``` syntax.

This instructs the compiler to automatically generate the implementation of the constructor.

```cpp
class MyClass {
public:
    MyClass() = default;  // Explicitly request compiler-generated version
};
```

#### 🔹Common uses

* When you've defined other constructors but still want a default constructor.
* To explicitly document that you want the compiler-generated version.
* Allows the constructor to remain trivial and optimizable, unlike an empty user-defined constructor.

---

