# 36. What is RAII? Why is it important in C++?

## 💡 Definition

RAII stands for **Resource Acquisition Is Initialization**.

It's a core programming idiom in C++ where you tie the lifetime of a resource (like heap-allocated memory, a file handle, a database connection, or a mutex lock) to the lifetime of an object.

In other words:

* A resource is acquired (allocated/opened) in an object’s constructor.
* That resource is released (freed/closed) in the object’s destructor.

This ensures that resources are **automatically released** when the object goes out of scope — even if exceptions occur.

In modern C++, most application-level code avoids raw ```new``` or ```delete``` precisely because RAII objects like → ```std::unique_ptr```, ```std::shared_ptr```, ```std::vector```, ```std::string```, ```std::ifstream```, and ```std::lock_guard``` manage resources for you.

---

## 💡 Why RAII Is Important

* **Automatic cleanup** → Resources are freed automatically when objects go out of scope.
* **Exception safety** → Even if an exception is thrown, destructors run during stack unwinding, ensuring no leaks.

* **No manual cleanup code** → Less chance of human error or forgetting to free resources.

* **Deterministic destruction** → Objects are destroyed immediately and predictably when leaving scope, not at some unknown time in the future like in garbage-collected languages.

* **Prevents resource leaks** → Memory, file handles, locks, and other resources are guaranteed to be released.

---

## 💡 How to implement RAII

* Acquire resource in constructor.
* Release resource in destructor.
* Make the class non-copyable or properly handle copying/moving (Rule of Three/Five).
* Provide access to the resource through member functions.

---
## 💡 Example: File management

```cpp
class FileHandle {
    FILE* file;
public:
    FileHandle(const char* name) { 
        file = fopen(name, "r"); 
        if (!file) throw std::runtime_error("Open failed");
    }
    ~FileHandle() { 
        if (file) {
            fclose(file); 
            std::cout << "File closed automatically\n";
        }
    }
    // Delete copy, allow move (Rule of 5 implementation here...)
};
```

---

## 💡 Modern C++ Example: Smart Pointers (Rule of Zero)

```cpp
#include <iostream>
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHello() const { std::cout << "Hello from Resource\n"; }
};

class ResourceManager {
private:
    std::unique_ptr<Resource> resource;  // Smart pointer manages memory
    
public:
    // Constructor acquires the resource
    ResourceManager() : resource(std::make_unique<Resource>()) {}
    
    // Destructor is automatically generated (Rule of Zero)
    // Copy is disabled because unique_ptr is non-copyable
    // Move operations are generated automatically and are correct

    
    // Accessor to the resource
    Resource* get() const { return resource.get(); }
};

void useResource() {
    ResourceManager resMgr;  // Resource acquired
    resMgr.get()->sayHello();
} // ResourceManager goes out of scope → unique_ptr destructor runs → Resource destroyed

int main() {
    useResource();
    std::cout << "Back in main (resource was cleaned up automatically)\n";
}
```

---

## 💡 Advanced Example: Custom RAII Class (Rule of Five)

This example is intentionally written with raw ```new```/```delete``` to demonstrate how RAII works internally. In real production code, prefer standard RAII types like ```std::unique_ptr``` or ```std::shared_ptr```.

```cpp
#include <iostream>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHello() const { std::cout << "Hello from Resource\n"; }
};

class ResourceManager {
private:
    Resource* resource;
public:
    // Constructor acquires the resource
    ResourceManager() : resource(new Resource()) {}

    // Destructor releases the resource
    ~ResourceManager() {
        delete resource;
        std::cout << "ResourceManager destroyed\n";
    }

    // Accessor to the resource
    Resource* get() const {
        return resource;
    }

    // Prevent copying to avoid double deletion
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // Allow move semantics for safe transfer of ownership
    ResourceManager(ResourceManager&& other) noexcept : resource(other.resource) {
        other.resource = nullptr;
    }
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }
};

void useResource() {
    ResourceManager resMgr; // Resource acquired
    resMgr.get()->sayHello();
} // ResourceManager goes out of scope, Resource is automatically destroyed

int main() {
    useResource();
    std::cout << "Back in main\n";
}
```

**Explanation**

* **Resource Acquisition:** The ```ResourceManager``` constructor allocates a ```Resource``` object.
* **Resource Management:** The ```ResourceManager``` class manages the ```Resource``` pointer. It provides access to the resource via the ```get()``` method.
* **Resource Release:** The ```ResourceManager``` destructor deletes the ```Resource``` object, ensuring it is properly released when the ```ResourceManager``` instance goes out of scope.
* **Prevent Copying:** Copy constructor and copy assignment operator are deleted to prevent copying, which could lead to double deletion issues.
* **Move Semantics:** Move constructor and move assignment operator are provided to allow safe transfer of ownership of the resource.

---

## 🧪 Code example
- [`../../code/level-2/36-raii`](../../code/level-2/36-raii)
