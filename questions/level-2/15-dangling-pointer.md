# 15. What is a dangling pointer?

## 💡Definition

A **dangling pointer** is a pointer that points to memory that has been freed or is no longer valid.

Accessing or dereferencing a dangling pointer leads to undefined behavior, which can cause crashes, data corruption, or other unpredictable results.

⚠️ **The "Silent Killer" Risk:** UB does not guarantee a crash. In many production bugs, a dangling pointer access might "work" perfectly fine for hours (reading old data that hasn't been overwritten yet) before silently corrupting a different part of the system later.

---

## 💡Categories of dangling pointers

### 🔹Heap dangle (Use-After-Free)

Occurs when dynamically allocated memory is freed but the pointer is still used.
```cpp
int* p = new int(5);
delete p; // Memory is released
// p still holds the address (e.g., 0x5a1b0), but it doesn't own it.

*p = 10;    // ❌ DANGER: Might crash, might corrupt data, might do nothing.
```

### 🔹Stack dangle (Use-After-Scope)

Occurs when a pointer holds the address of a local variable that has gone out of scope.

```cpp
// ❌ BAD: Returning a pointer to a stack variable
int* getStackDangle() {
    int x = 42; // Lives on the Stack
    return &x;  // Returning address of memory that dies when function ends
}

// Caller receives a pointer to "dead" memory.
```

### 🔹Reallocation dangling (Iterator invalidation)

Occurs when containers reallocate their internal storage.

```cpp
std::vector<int> v = {1,2,3};
int* p = &v[0];

v.push_back(4);   // may reallocate
*p = 10;          // ❌ p may now be dangling
```

### 🔹Dangling references

References are implemented as pointers under the hood. Returning a reference to a local variable is just as fatal as returning a pointer.

```cpp
// X BAD: Returning reference to stack variable
int& getRef() {
    int x = 10;
    return x; // Warning: Reference to stack memory associated with local variable 'x' returned
}

int& ref = getRef(); 
// Accessing 'ref' is now UB.
```

### 🔹View dangles (The std::string_view trap)

Modern C++ introduced non-owning views like ```std::string_view``` and ```std::span```. These are pointers in disguise and can dangle.

```cpp
// X BAD: The std::string is temporary.
std::string_view getDanglingView() {
    return std::string("Hello World");
    // The string object is destroyed here.
    // The returned view points to garbage memory.
}
```

---

## 💡How to Prevent Dangling Pointers

### 🔹Use smart pointers

Prefer smart pointers instead of raw ```new```/```delete```.
* ```std::unique_ptr``` → exclusive ownership
* ```std::shared_ptr``` → shared ownership
* ```std::weak_ptr``` → safe observation

**The Trap: Smart pointers are not magic.**

You can still force a dangle if you extract the raw pointer carelessly.
```cpp
// ✅ Safe
std::unique_ptr<int> smart = std::make_unique<int>(10);

// ❌ Risky: Extracting the raw pointer
int* raw = smart.get(); 
// If 'smart' goes out of scope here, 'raw' instantly becomes a dangling pointer.
```

**The Trap: Smart pointers can be moved.**

Smart pointers can be moved, leaving the source in an empty state. This creates a subtle dangling pointer scenario.

```cpp
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
std::unique_ptr<int> ptr2 = std::move(ptr1);  // ptr1 is now empty!

// ❌ Accessing ptr1 after move
if (ptr1) {  // ptr1 is nullptr now
    *ptr1 = 10;  // This won't execute (good!)
}

// But what about this?
int* raw = ptr1.get();  // Returns nullptr
// If you saved 'raw' before the move, it's now dangling!
```

### 🔹Use RAII

Encapsulate every resource in an object that manages its lifetime.

```cpp
class IntOwner {
public:
    IntOwner(int v) {
        data = new int(v);
    }

    ~IntOwner() {
        delete data;   // always released
    }

    int& get() {
        return *data;
    }

private:
    int* data;
};

IntOwner createValue() {
    return IntOwner(10);   // ownership tied to object
}

void f() {
    IntOwner x = createValue();
    x.get() = 5;   // safe

}   // destructor runs → memory freed safely
```

### 🔹Safe Observation with weak_ptr

The only smart pointer designed to handle dangles gracefully. It does not keep the object alive but allows you to check if it still exists before accessing it. It only works in conjunction with ```std::shared_ptr```.

```cpp
std::shared_ptr<int> sp = std::make_shared<int>(10);
std::weak_ptr<int> wp = sp;

if (auto temp = wp.lock()) {
    // safe to use *temp
} else {
    // object already destroyed
}
```

### 🔹Nullify pointers after deletion (Partial safety)

Set pointers to nullptr after deleting them to avoid accidental use.

```cpp
int* p = new int(20);
delete p;
p = nullptr; // Marks: object is gone

// Any later access must be guarded
if (p) {
    // This will not run
}
```

This only protects ```p```. It does not protect aliases:

```cpp
int* p = new int(20);
int* q = p;  // q aliases p

delete p;
p = nullptr; // p is safe (null)

// ❌ q is still dangling! Nullifying p did not save q.
```

Nullifying is useful but not sufficient.

### 🔹Never return pointers to local variables

```cpp
int* f() {
    int x = 10;
    return &x;
}
```

Return by value or use smart pointers instead.

```cpp
std::unique_ptr<int> getSafePointer() {
    return std::make_unique<int>(30); // Safe, no dangling
}
```

### 🔹Be careful with containers

Examples of operations that invalidate pointers:

* ```vector::push_back```
* ```vector::resize```
* ```vector::erase```
* Rehashing in ```unordered_map```

**Rule:** If iterators are invalidated, pointers and references are also invalidated.

### 🔹Using tools to catch dangling pointers

**AddressSanitizer (ASan)** - Compile with ```-fsanitize=address``` (Clang/GCC). It instruments the code to detect use-after-free and use-after-scope instantly during testing.

**UndefinedBehaviorSanitizer (UBSan)** - Catches undefined behavior beyond just memory issues. Flag: ```-fsanitize=undefined```. Detects integer overflow, null pointer derefs, misaligned access, etc.

**MemorySanitizer (MSan)** - Detects reads of uninitialized memory. Flag: ```-fsanitize=memory```

**Valgrind** - Runtime tool. Slower but catches issues ASan might miss. Great for legacy code.

**Static analyzers** - Clang Static Analyzer. Cppcheck. Can find issues without running the code.

---

