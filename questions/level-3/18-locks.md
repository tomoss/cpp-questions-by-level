# 18. What is std::lock_guard vs std::unique_lock?

## 💡Definition

***std::lock_guard*** and ***std::unique_lock*** are both utilities for managing mutexes, but they serve different purposes and have different levels of flexibility.

Both follow the **RAII** principle, meaning they automatically lock a mutex when created and unlock it when they are destroyed (go out of scope), which is crucial for writing exception-safe code.

---

## 💡Lock Guard

***std::lock_guard*** is the simplest and most efficient way to own a mutex for a specific scope.

**What it does:** It locks the provided mutex in its constructor and unlocks it in its destructor.

**Characteristics**

* You cannot manually unlock it.
* You cannot manually lock it.
* Cannot be moved or copied.
* It cannot be used with ***std::condition_variable***.

**When to use:**

* Use it when you need to lock a mutex for the entire duration of a single block of code (like a function or a loop).

```cpp
#include <mutex>

std::mutex mtx;

void simple_function() {
    // mtx is locked here when 'guard' is created
    std::lock_guard<std::mutex> guard(mtx);
    
    // Critical section: Access shared data here...
    std::cout << "Critical section is locked!\n";
    
    // mtx is automatically unlocked here when 'guard' goes out of scope
}
```

**Note:** In C++17 and later, ***std::scoped_lock*** is often preferred over ***std::lock_guard***. It does the same thing for a single mutex but can also lock multiple mutexes at once with a deadlock-avoidance algorithm.

---

## 💡Unique Lock

***std::unique_lock*** is a general-purpose mutex wrapper. It provides all the functionality of ***std::lock_guard*** plus much more.

**What it does:** It can manage a mutex, but you have full control over it.

**Characteristics**

* **Manual Control:** You can call ```lock()``` and ```unlock()``` on it multiple times.
* **Condition Variables:** It is required for use with ***std::condition_variable***.
* **Supports deferred Locking:** You can create it without locking the mutex immediately.
* **Supports try-locking:** You can attempt to acquire the mutex without blocking.
* **Timed Locking:** You can attempt to lock for a specific duration.
* **Moveable:** Can transfer ownership.

**When to use:**

* Use it only when you need its advanced features, like with ***std::condition_variable*** or unlocking early.

```cpp
void complex_function() {
    std::unique_lock<std::mutex> lk(mtx);

    // 1. Access shared data...

    lk.unlock(); // Unlock the mutex early

    // 2. Do other non-critical work...
}
```

***std::unique_lock*** is the correct tool when you need flexible locking: defer, try, unlock early, or transfer ownership.

---

## 🧪 Code example
- [`../../examples/level-3/18-locks`](../../examples/level-3/18-locks)
