# 13. What is a destructor, and when is it called?

## 💡 Definition

A **destructor** in C++ is a special member function of a class that is automatically invoked when an object goes out of scope or is explicitly deleted.

Its main job is to clean up resources that the object may have acquired during its lifetime, such as dynamically allocated memory, file handles, or network connections.

## 💡 Definition from cppreference

[Destructors](https://en.cppreference.com/w/cpp/language/destructor.html)

A destructor is a special member function that is called when the lifetime of an object ends. The purpose of the destructor is to free the resources that the object may have acquired during its lifetime.

---

## 💡 Key points

* **Name** →  Same as class name, preceded by ```~```
* **Return type** → None (not even ```void```)
* **Parameters** → None
* **Overloading** → Not allowed, only one destructor per class
* **Access specifier** → ```public```, unless you have a specific reason not to
* **Virtual allowed** → Yes (for polymorphic classes)
* **No exceptions** → Destructors should not throw exceptions (marked ```noexcept``` by default in C++11+)
* **Const and Static** → Cannot be ```const``` or ```static```

---

## 💡 When destructors are called

### Local objects (Stack)

* Called automatically when the object goes out of scope.

### Dynamic objects (Heap)

* For heap objects (created using ```new```), the destructor is not called automatically. You must use operator ```delete``` explicitly.

* **Note:** When deleting an array of objects, you must use ```delete[]``` to ensure all destructors are called.

* **Note:** Destructor can also be called explicitly for an object. Not recommended. Dangerous. Not many reasons to do it: ```objectName.~className();```

### Global/Static objects

* At program termination.

---

## 💡 Explicitly defaulted destructor

You can use ```= default``` for the destructor to ensure that the compiler generates a default destructor.

```cpp
class Entity {
public:
	Entity() = default;
	~Entity() = default; // Defaulted destructor
};
```

---

## 💡 When you don't need a destructor (The Rule of Zero)

In modern C++, the goal is to write classes that don't need custom destructors. This is known as the Rule of Zero.

You achieve this by using member variables that manage their own resources, such as:

* **Smart Pointers:** ```std::unique_ptr``` or ```std::shared_ptr``` automatically manage memory.

* **STL Containers:** ```std::vector```, ```std::string``` or ```std::map``` handle their own internal memory.

---

## 💡 When you need a destructor

You need to write your own destructor in two primary situations:

* When your class directly manages a raw resource (like memory, a file, or a network connection).

* When your class is intended to be a base class in a polymorphic hierarchy.

---

## 💡 Managing Raw Resources

This is the most common reason. If your class constructor acquires a resource that needs to be manually released, the destructor is the place to release it.

This adheres to the **RAII** principle.

Common Examples:

* **Raw Memory:** If your constructor allocates memory with ```new``` or ```new[]```, your destructor must deallocate it with ```delete``` or ```delete[]```.

* **File Handles:** For example, if your constructor opens a file with ```fopen()```, your destructor should close it with ```fclose()```.

* **Network Sockets:** If you open a socket, the destructor should close it.

* **Mutexes/Locks:** If the constructor acquires a lock, the destructor should release it.

* When You Define a Copy Constructor or Assignment Operator → **Rule of Three**

---

## 💡 Polymorphism and Virtual Destructors

In an inheritance hierarchy, destructors are called in the reverse order of constructors

```
Base Constructor
Derived Constructor
Derived Destructor
Base Destructor
```

### 🔹Virtual Destructor

* If your class is designed to be used as a base class, and you might delete a derived object through a pointer of type base class, you must declare the destructor as ```virtual```.

* If the base class destructor is not ```virtual```, deleting a derived object via a base pointer results in ***undefined behavior***.

* Typically, only the base class destructor is called, and the derived class's destructor is never run.

* This means any resources managed by the derived class will be leaked.

#### Example without Virtual Destructor

```cpp
class Base {
public:
	Base() { std::cout << "Base constructor\n"; }
	~Base() { std::cout << "Base destructor\n"; }
};

class Derived : public Base {
public:
	Derived() { std::cout << "Derived constructor\n"; }
	~Derived() { std::cout << "Derived destructor\n"; }
};

int main()
{
	Base* base = new Base();
	delete base;

	std::cout << "------------\n";

	Derived* derived = new Derived();
	delete derived;

	std::cout << "------------\n";

	Base* poly = new Derived();
	delete poly;
}
```

```
Base constructor
Base destructor
------------
Base constructor
Derived constructor
Derived destructor
Base destructor
------------
Base constructor
Derived constructor
Base destructor
```

#### Example with Virtual Destructor

Making base class destructor ```virtual``` guarantees that the object of derived class is destructed properly, i.e., both base class and derived class destructors are called:

```cpp
class Base {
public:
	Base() { std::cout << "Base constructor\n"; }
	virtual ~Base() { std::cout << "Base destructor\n"; }
};

class Derived : public Base {
public:
	Derived() { std::cout << "Derived constructor\n"; }
	~Derived() { std::cout << "Derived destructor\n"; }
};

int main() {
	Base* poly = new Derived();
	delete poly;
}
```

```
Base constructor
Derived constructor
Derived destructor
Base destructor
```

### 🔹Guideline

* Any time you have a ```virtual``` function in a class, you **should** immediately add a ```virtual``` destructor (even if it does nothing). This way, you ensure against any surprises later.

* If a class is intended to be used as a base class, make its destructor ```virtual```.

* In an abstract base class (with pure virtual functions), the destructor should also be ```virtual```, and often ```virtual ~Base() = default;``` is good practice.

### 🔹How it works internally

Declaring a destructor as ```virtual``` makes the class polymorphic, meaning it maintains a vtable (virtual table), and uses dynamic dispatch to determine at runtime which destructor to call when deleting through a base pointer.

Without ```virtual ~Base()```
* ```delete``` → Calls ```~Base()```, ignoring ```~Derived()```.
* Only base part of the object is destroyed.
* Derived class resources remain unreleased (memory leak).

With ```virtual ~Base()```
* ```delete``` → Calls ```~Derived()``` first. The compiler uses dynamic dispatch (vtable) to determine the actual type of the object at runtime.
* Derived part of the object is destroyed.
* Then, ```~Base()``` is called, cleaning up the base part.

---

## 🧪 Code example
- [`../../code/level-1/13-destructor`](../../code/level-1/13-destructor)
