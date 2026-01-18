# 16. What are friend functions and friend classes?

## 💡Definition

In C++, the friend keyword is used to grant a **non-member function**, **another class**, or a **member function of another class** access to the **private** and **protected** members of a class.

Friend functions and friend classes are mechanisms that allow controlled access to the private and protected members of a class.

---

## 💡When to use friend ?

* **Operator Overloading**(e.g., ```<<``` for custom output).
* **Utility functions** that need access to private data.
* **Closely related classes** (e.g., Tree and TreeNode).

### Example → Overloading the ```<<``` operator using friend

```cpp
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n), age(a) {}

    friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << "Name: " << p.name << ", Age: " << p.age;
    return out;
}

int main() {
    Person john("John Doe", 30);
    std::cout << john << std::endl;
}
```

---

## 💡Important

* A friend function can access private and protected members of the class in which it is declared as a friend.
* Friendship is **not reciprocal** – if class A declares class B as a friend, B does not automatically consider A a friend.
* Friendship is **not inherited** – derived classes do not inherit friendship from base classes.
* Friendship is **not transitive** – if A is a friend of B and B is a friend of C, it does not mean A is a friend of C.
* Friendship is **breaking encapsulation** –  so it should be used sparingly and with caution.
* A friend function can be a *non-member function*, a *member of another class*, or even a *whole other class*.
* **You can declare an entire class as a friend**, which gives all its member functions access to the private and protected members of the other class.
* **Friend declarations can appear anywhere in the class definition** – public, private, or protected sections.

---

## 💡Friend function

A **friend function** is a function that is granted access to the private and protected members of a class. It is declared inside the class using the keyword ```friend```.

```cpp
friend return_type function_name (arguments);
```
It must be declared inside the class but defined outside.

### Example

```cpp
#include <iostream>

class Box {
private:
    int width;

public:
    Box(int w) : width(w) {}

    // Declare a friend function
    friend void printWidth(const Box& box);
};

// Friend function definition (not a member of Box)
void printWidth(const Box& box) {
    std::cout << "Box width: " << box.width << std::endl;  // Can access private member
}

int main() {
    Box b(10);
    printWidth(b);  // Output: Box width: 10
}
```

---

## 💡Friend class

A **friend class** is a class whose all member functions are given access to the private and protected members of another class that declares it as a friend.

### Example

```cpp
#include <iostream>

class Storage {
private:
    int secretData = 42;

    // Declare Display as a friend class
    friend class Display;
};

class Display {
public:
    void showSecret(const Storage& storage) {
        std::cout << "Secret data: " << storage.secretData << std::endl;  // Can access private member
    }
};

int main() {
    Storage s;
    Display d;
    d.showSecret(s);  // Output: Secret data: 42
}
```

---

## 💡Friend Member Function

You can declare **only a specific member function** of another class as a friend.

### Example

```cpp
#include <iostream>

class Storage;  // Forward declaration

class Display {
public:
    void showSecret(const Storage& storage);  // Declaration only
};

class Storage {
private:
    int secretData = 42;

    // Only Display::showSecret is a friend
    friend void Display::showSecret(const Storage&);
};

// Definition after Storage is fully defined
void Display::showSecret(const Storage& storage) {
    std::cout << "Secret data: " << storage.secretData << std::endl;
}

int main() {
    Storage s;
    Display d;
    d.showSecret(s);  // Output: Secret data: 42
}
```

---

