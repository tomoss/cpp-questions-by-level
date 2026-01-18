#include <iostream>

class Resource {
public:
    Resource() {
        std::cout << "Resource acquired\n";
    }
    ~Resource() {
        std::cout << "Resource destroyed\n";
    }
    void sayHello() const {
        std::cout << "Hello from Resource\n";
    }
};

class ResourceManager {
private:
    Resource* resource;

public:
    // Constructor acquires the resource
    ResourceManager()
        : resource(new Resource()) {}

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
    ResourceManager(ResourceManager&& other) noexcept
        : resource(other.resource) {
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

void useResourceWithException() {
    ResourceManager resMgr;                        // Resource acquired
    throw std::runtime_error("An error occurred"); // Simulate an exception
    resMgr.get()->sayHello();
} // ResourceManager goes out of scope, Resource is automatically destroyed even on exception

int main() {
    useResource();
    std::cout << "---\n";
    try {
        useResourceWithException();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }
}