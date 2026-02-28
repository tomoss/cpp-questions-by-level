# 14. What is a copy constructor? When is it called?

## 🔳 Definition

A copy constructor is a special constructor that creates a new object as a copy of an existing object of the same type.

It is automatically called when an object is initialized from another object of the same type.

## 🔳 Syntax

```cpp
ClassName(const ClassName& other);
```

* **Parameter:** Takes a const reference to an object of the same class

    * **const** → This ensures the original object (`other`) cannot be modified during the copying process.

    * **&** → The object is passed by reference. If it were passed by value, the compiler would need to call the copy constructor to initialize `other`. This creates an infinite recursive loop. Modern compilers (GCC/Clang/MSVC) will flag this as a compilation error rather than letting it crash at runtime.

* **Return type:** None

## 🔳 When is Copy Constructor called?

### 🔹 Direct initialization / Copy-initialization

When initializing a new object from an existing one.

```cpp
Student s1(22, "John");

Student s2 = s1;   // copy-initialization
Student s3(s1);    // direct-initialization
```

### 🔹 Passing an object by value

When you pass an object to a function by value, a copy is made for the function parameter.

```cpp
void func(Student s) { // Copy constructor is called
    s.display();
}
```

### 🔹 Returning an object by value

A copy/move **may** occur, but it is often **elided** (optimized away):

```cpp
Student createStudent() {
    Student s(21, "Bob");
    return s;  // copy elision is common but not guaranteed
}
```

If the compiler cannot perform **Copy Elision (RVO/NRVO)** and no **Move Constructor** is available, it falls back to a copy.

Guaranteed Copy Elision (C++17+) happens in cases like returning a prvalue temporary:

```cpp
Student createStudent() {
    return Student(21, "Bob"); // guaranteed copy elision since C++17
}
```

## 🔳 Default (implicit) copy constructor

If you don’t implement a copy constructor, the compiler may generate one that performs **member-wise copy** of all non-static data members.

***Note:*** The implicitly-generated copy constructor can be deleted if a member is not copyable (e.g. `std::unique_ptr`).

### 🔹 Member-wise copy

* Means each data member of the source object is copied to the corresponding member of the target object.

* If your class stores raw pointers, just the pointer value is copied so two objects point to the same allocation, this is called a **shallow copy**.

### 🔹 Shallow copy

* A shallow copy means copying the values of all member variables as they are, including pointer values.

* It copies the pointer values, not the actual data they point to.

* As a result, both the original object and copied objects point to the same allocated memory.

## 🔳 When the default copy is enough (Rule of 0)

If your class isn’t manually managing resources, you typically don’t need to write a copy constructor at all.

```cpp
class Student {
	int age;
	std::string name;
public:
	Student(int p_age, std::string p_name) : age(p_age), name(p_name) {}
};
```

Why this is safe?

* `int` is trivially copyable.

* `std::string` defines correct copy behavior for its internal memory.

## 🔳 When do you need to define a copy constructor

* Your class contains raw pointers / manually managed resources (heap memory, file handles, sockets, etc.) and you need **deep copy** behavior.

* You need custom behavior during copy (logging, ref-counting, validation, etc).

* You want to prevent copying (by using `= delete`).

### 🔹 Copy constructor with manually managed resources

If your class owns raw pointers and you shallow-copy them, both objects point to the same memory, which can lead to:

* Double deletion
* Dangling pointers
* Shared state

So, if your class is managing resources directly, you should implement a custom copy constructor that performs a **deep copy**

### 🔹 Deep copy

* A deep copy creates a completely independent copy of the object.

* It allocates new memory for each dynamic resource instead of just copying the pointers.

**Example**
```cpp
class String {
    char* buffer;
    size_t length;
public:
    String(const char* str) {
        length = strlen(str);
        buffer = new char[length + 1];
        strcpy(buffer, str);
    }

    // Copy constructor (deep copy)
    String(const String& other) {
        length = other.length;
        buffer = new char[length + 1];
        strcpy(buffer, other.buffer);
    }

    ~String() { delete[] buffer; }
};
```

See also [Rule of Three/Five/Zero](../level-2/7-rule-of-three-five-zero.md)

## 🔳 Explicitly defaulted copy constructor

You can explicitly default the copy constructor using the `= default` syntax. This tells the compiler to generate the default implementation for this function.

```cpp
class MyClass {
public:
	MyClass(const MyClass&) = default;
};
```

## 🔳 Private copy constructor

You can make the copy constructor **private**. This is a common technique used to prevent copying of objects.

```cpp
class MyClass {
private:
	MyClass(const MyClass&); // Copy constructor (private)
public:
	MyClass() = default;
};

int main() {
	MyClass c1;
	MyClass c2 = c1; // Can't do it
}
```

## 🔳 Deleted copy constructor

In modern C++, you can use the `= delete` syntax instead of making it `private`.

```cpp
class MyClass {
public:
	MyClass() = default;
	MyClass(const MyClass&) = delete;
};

int main() {
	MyClass c1;
	MyClass c2 = c1; // Can't do it
}
```

## 🔳 Inheritance Considerations

* If Derived copy constructor is implicitly generated / defaulted, the base subobject is copied automatically.

* If you manually define a copy constructor in a Derived class, you must explicitly call the Base copy constructor.

```cpp
class Base {
public:
    Base(const Base&) { /* ... */ }
};

class Derived : public Base {
public:
    Derived(const Derived& other) : Base(other) { /* ... */ }
};
```

If you omit `Base(other)`, the compiler will automatically call the `Base` default constructor. This means your "copied" object will have a default-initialized base state, resulting in a partial copy (data loss).

## 🧪 Code example
- [`../../code/level-1/14-copy-constructor`](../../code/level-1/14-copy-constructor)
