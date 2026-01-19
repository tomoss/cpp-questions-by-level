# 22. Explain const correctness (const int*, int* const, const methods).

The keyword “const” is short for *constant* and specifies that something remains unchanged.

## 1️⃣ Const constants

One of the basic uses is to declare constants:

```cpp
const float l_version = 2.1f;
const std::string l_name = "A constant string";
```

These variables cannot be modified after initialization and must be initalized when declared.

## 2️⃣ Const to protect input parameters

Whenever a function/method is not meant to change a parameter that is passed as argument, it is strongly recommended to protect that parameter by declaring it const in the function/method prototype.

```cpp
int square(const int& value) {
    return value * value;
}
```
## 3️⃣ Const references

A const reference is a reference that does not allow modification of the object it refers to. It's commonly used to pass objects to functions without copying them and without allowing modification.

```cpp
void print(const std::string& text) {
    // text += "!"; // ❌ Error: text is const
    std::cout << text << std::endl;
}
```

⚠️ **Note:** A ```const int&``` means you cannot change `x` through the reference. It does not mean the underlying value is magically frozen.

```cpp
int x = 5;
const int& ref = x;
x = 10;
std::cout << ref; // 10
```

## 4️⃣ Const pointers

In C++, when working with pointers and const, you can control whether the pointer itself is constant, whether the data it points to is constant or both.

```const int* A``` → ***"A is a pointer to an int that is const."***

```int const * ptr``` → ***(Same as above) "A is a pointer to a const int."***

```int* const A``` → ***"A is a const pointer to an int."***

```const int* const A``` → ***"A is a const pointer to an int that is const."***

### 🔹Pointer to const data — data can't be changed

```const int* x``` → We can reassign the pointer to point to another address, but we cannot modify the content.

```cpp
int a = 3;
const int* x = &a;
// *x = 8; // will NOT compile
```

```cpp
int a = 3;
int b = 5;
const int* x = &a;
x = &b; // allowed
```

⚠️ ```const int * x``` does not mean that x actually points to a const variable. It just means that the compiler will not allow you to modify the pointed value through x.

```cpp
int val = 10;
const int* x = &val;
*x = 30; // this will NOT compile, you're not allowed to modify "val" through "x".
val = 30; // this will compile.
std::cout << *x << std::endl; // 30
```

### 🔹Const pointer — pointer can't change, data can

```int* const x``` → We can’t reassign the pointer to point to another address, but we can modify the content.

```cpp
int a = 3;
int b = 5;

int* const x = &a;
*x = 8;       // Allowed
// x = &b;    // ❌ Not allowed
```

### 🔹Const pointer to const data — neither can be changed

```const int* const x``` → We can’t reassign the pointer to point to another address and we can’t modify the content.

```cpp
int a = 3;
int b = 5;

const int* const x = &a;
// *x = 8;   // ❌ Not allowed
// x = &b;   // ❌ Not allowed
```

## 5️⃣ Const objects and const methods

A const object (a constant) is an object whose value cannot be changed. If we have a const object, reference or pointer to const object, the compiler will not let us call methods on that object unless those methods can guarantee they will not change the object. The way we guarantee that a method will not change the object is by making the method const.

```cpp
class Entity {
private:
	  int x;
public:
	  int getX() {
        return x;
	  }
};

void printEntity(const Entity& e) {
	  std::cout << e.getX() << std::endl;
}
```

> ❌ Error: C++ the object has type qualifiers that are not compatible with the member function object type is: const Entity.

This C++ error means you're trying to call a non-const member function on an object that is declared as const. A const object can only call member functions that are themselves marked as const, because non-const member functions could modify the object.

**Correct version, adding const to `getX()`**

```cpp
class Entity {
private:
	int x;
public:
	int getX() const {
		return x;
	}
};

void printEntity(const Entity& e) {
	std::cout << e.getX() << std::endl;
}
```

❓ Can a free function (not a class method) be const? No, free functions cannot be marked const because const applies to an implicit `this` pointer, which only exists for non-static member functions.

## 6️⃣ Const methods and mutable data members

Sometimes, a method is logically const but still needs to modify a member that doesn’t affect the observable state — like a counter for logging.

For example, we want to track how many times `getArea()` is called, but the method is const and updating the counter violates const rules.

The solution: mark the counter as mutable, allowing it to be modified inside const methods.

```cpp
class Rectangle {
private:
    int length;
    int width;
    mutable int count = 0;
public:
    Rectangle(int l, int w) : length(l), width(w) {}

    int getArea() const {
        count++;            // allowed
        return length * width;
    }
};
```

## 7️⃣ Const reference data members

Reference data members can also be const.

**Note:** If a class has a const member or a reference member, you cannot assign it in the constructor body. You must use the Member Initializer List.

```cpp
class MyClass {
private:
    const int& ref;
public:
    MyClass(const int& r) : ref(r) {}

    void print() const {
        std::cout << "ref = " << ref << std::endl;
    }
};

int main() {
    int x = 5;
    MyClass c(x);
    x = 10;
    c.print(); // 10
}
```

## 8️⃣ Const Overloading

You can provide two versions of the same method. The compiler will choose the const version if the object itself is const. This is common for getters that return references.

```cpp
class Database {
    int value = 0;
public:
    // 1. Non-const: Returns a pointer you can use to CHANGE the value
    int* getData() { return &value; }

    // 2. Const: Returns a pointer that is READ-ONLY
    const int* getData() const { return &value; }
};

void check(const Database& db) {
    // *db.getData() = 5;  // ❌ Error: Calls the const version (returns const int*)
}

int main() {
    Database db;
    *db.getData() = 10;    // ✅ Success: Calls non-const version
}
```

---

## 🧪 Code example
- [`../../code/level-1/22-const`](../../code/level-1/22-const)
