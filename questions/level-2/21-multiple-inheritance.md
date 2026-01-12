# 21. What is multiple inheritance? What are the problems with it?

## 💡Definition

Multiple inheritance in C++ is the mechanism that allows a derived class to simultaneously inherit from more than one base class.

This approach enables the derived class to combine the traits and functionalities of its parent classes, but it can also introduce notable complexities, such as ***ambiguities*** or the ***diamond problem***.

---

## 💡Syntax

```cpp
class DerivedClass : access-specifier BaseClass1, access-specifier BaseClass2, ... {
    // Derived class members
};
```

---

## 💡Key points

* **Combining Features:** Multiple inheritance allows a derived class to combine the features of multiple base classes.

* **Ambiguity Resolution:** If two base classes have members with the same name, the compiler will throw an ambiguity error unless explicitly resolved using the scope resolution operator (```::```).

```cpp
class A {
public:
    void show() { std::cout << "A" << std::endl; }
};

class B {
public:
    void show() { std::cout << "B" << std::endl; }
};

class C : public A, public B {
public:
    void display() {
        //show()   // ERROR: Ambiguity
        A::show(); // Explicitly call show() from A
        B::show(); // Explicitly call show() from B
    }
};

int main() {
    C objC;
    //objC.show();  // ERROR: Ambiguity
    objC.A::show(); // Explicitly call show() from A
    objC.B::show(); // Explicitly call show() from B
}
```

* **Diamond Problem:** Occurs when a class derives from two parent classes which both inherit from the same common base class. This hierarchy results in the final derived class having multiple copies of the common base, leading to ambiguity. In C++, this is resolved using virtual inheritance.

---

## 💡Best Practices

* **Composition over inheritance:** Avoid multiple inheritance unless absolutely necessary. Prefer composition (having members of other classes) instead of inheriting from multiple classes.

* **Prefer interfaces (pure abstract classes):** Safe because no data members, so no ambiguity or duplication. This approach avoids the diamond problem (as interfaces rarely inherit from other classes) and clearly defines what your class can do.

---

## 🧪 Code example
- [`../../examples/level-2/21-multiple-inheritance`](../../examples/level-2/21-multiple-inheritance)
