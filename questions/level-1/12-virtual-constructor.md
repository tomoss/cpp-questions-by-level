# 12. Can constructors be virtual? Why/why not?

## ❓ Short Answer

No — in C++, constructors **cannot be virtual**.

Attempting to declare a constructor `virtual` will result in a compile-time error.

---

## 🧠 Why Not? The Technical Reason

A virtual function call is resolved at runtime using a special table called the virtual table (vtable).

* Every class that has at least one virtual function has its own vtable.

* Every object of that class contains a hidden pointer, the Virtual Pointer (vptr), pointing to that vtable.

Here's the crucial point: **The virtual pointer is set up by the constructor.**

This creates a classic chicken-and-egg problem:

* To make a virtual function call, you need a vptr to find the correct function in the vtable.

* The vptr is strictly bound to the class currently being constructed. When `Base()` runs, the vptr points to `Base::vtable`, effectively ignoring the fact that the object will eventually become `Derived`.

Therefore, you cannot use virtual dispatch (which relies on the vptr) inside the mechanism that creates the vptr.

---

## 🧠 Why Not? The Logical Reason

```cpp
// The type is known at compile-time from the new expression
Animal* myPet = new Dog(); // Compiler knows to call Dog::Dog()
```

When you write `new Dog()`, the compiler knows exactly which constructor to call. There is no ambiguity and no existing object to dispatch on. You cannot behave polymorphically before you exist.

---

## 🔁 What Actually Happens During Construction

**The Rule:** During the execution of a base class constructor, the object is a base class object. The derived part has not been initialized yet.

The Sequence:

 * `Base()` starts running. vptr points to `Base::vtable`.
 * Virtual calls resolve to `Base` methods (not `Derived`).
 * `Base()` finishes.
 * `Derived()` starts running. vptr updates to `Derived::vtable`.

```cpp
#include <iostream>

struct Base {
    Base() {
        f();
    }
    virtual void f() {
        std::cout << "Base::f\n";
    }

    virtual ~Base() = default;
};

struct Derived : Base {
    Derived() = default;
    ~Derived() = default;

    void f() override {
        std::cout << "Derived::f\n";
    }
};

int main() {
    Base* b = new Derived(); // Prints: Base::f
    b->f(); // Prints: Derived::f
    delete b;
}
```

This shows:

* Virtual calls inside constructors do not dispatch to derived overrides.
* Virtual dispatch is only reliable after full construction.
* Therefore constructors themselves cannot be virtual.

---

## 💡 What about creating objects polymorphically?

**The Solution:** use a Factory

The factory pattern achieves 'virtual construction behavior' and runtime selection of which object to create without requiring constructors themselves to be virtual.

This can be done using:

* Simple Factory
* Factory Method
* Abstract Factory

### Simple Factory example:

```cpp
#include <iostream>
#include <string>
#include <memory>

// Abstract base class
class Pizza {
public:
    virtual void prepare() = 0;
    virtual ~Pizza() = default;
};

// Concrete derived classes
class CheesePizza : public Pizza {
public:
    void prepare() override {
        std::cout << "Preparing Cheese Pizza.\n";
    }
};

class PepperoniPizza : public Pizza {
public:
    void prepare() override {
        std::cout << "Preparing Pepperoni Pizza.\n";
    }
};

// The Factory
struct PizzaFactory {
    static std::unique_ptr<Pizza> create(const std::string& type) {
        if (type == "cheese") return std::make_unique<CheesePizza>();
        if (type == "pepperoni") return std::make_unique<PepperoniPizza>();
        return nullptr;
    }
};

int main() {
    auto myPizza = PizzaFactory::create("cheese");

    if (myPizza) {
        myPizza->prepare(); // Calls CheesePizza::prepare()
    }
}
```

---

## 🧪 Code example
- [`../../code/level-1/12-virtual-constructor`](../../code/level-1/12-virtual-constructor)
