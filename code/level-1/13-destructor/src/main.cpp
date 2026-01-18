#include <iostream>
#include <memory>

// Example : Basic Destructor (Manual Resource Management)
class FileHandler {
private:
    char* buffer;
    std::string filename;

public:
    FileHandler(const std::string& name, size_t size)
        : filename(name) {
        buffer = new char[size];
        std::cout << "FileHandler created for: " << filename << "\n";
    }

    // Destructor - cleans up dynamically allocated memory
    ~FileHandler() {
        delete[] buffer;
        std::cout << "FileHandler destroyed for: " << filename << "\n";
    }
};

// Example: Rule of Zero (Modern C++ - No Custom Destructor Needed)
class ModernFileHandler {
private:
    std::unique_ptr<char[]> buffer;
    std::string filename;

public:
    ModernFileHandler(const std::string& name, size_t size)
        : buffer(std::make_unique<char[]>(size))
        , filename(name) {
        std::cout << "ModernFileHandler created for: " << filename << "\n";
    }

    // No custom destructor needed - smart pointer handles cleanup automatically!
    ~ModernFileHandler() {
        std::cout << "ModernFileHandler destroyed for: " << filename << "\n";
    }
};

// Example: Virtual Destructor for Polymorphism
class Shape {
public:
    Shape() {
        std::cout << "Shape constructor\n";
    }
    virtual ~Shape() {
        std::cout << "Shape destructor\n";
    }                        // Virtual!
    virtual void draw() = 0; // Pure virtual function
};

class Circle : public Shape {
private:
    double* radius;

public:
    Circle(double r) {
        radius = new double(r);
        std::cout << "Circle constructor (radius: " << *radius << ")\n";
    }

    ~Circle() {
        std::cout << "Circle destructor (cleaning up radius)\n";
        delete radius;
    }

    void draw() override {
        std::cout << "Drawing circle\n";
    }
};

class Rectangle : public Shape {
private:
    int* dimensions;

public:
    Rectangle(int w, int h) {
        dimensions = new int[2]{w, h};
        std::cout << "Rectangle constructor (" << w << "x" << h << ")\n";
    }

    ~Rectangle() {
        std::cout << "Rectangle destructor (cleaning up dimensions)\n";
        delete[] dimensions;
    }

    void draw() override {
        std::cout << "Drawing rectangle\n";
    }
};

// Example: Stack vs Heap Object Destruction
class Counter {
private:
    static int count;
    int id;

public:
    Counter()
        : id(++count) {
        std::cout << "Counter #" << id << " created\n";
    }

    ~Counter() {
        std::cout << "Counter #" << id << " destroyed\n";
    }
};

int Counter::count = 0;

int main() {
    std::cout << "=== Example: Manual Resource Management ===\n";
    {
        FileHandler fh("data.txt", 1024);
        // Destructor called automatically when fh goes out of scope
    }
    std::cout << "\n";

    std::cout << "=== Example: Rule of Zero (Smart Pointers) ===\n";
    {
        ModernFileHandler mfh("modern_data.txt", 2048);
        // Smart pointer automatically cleans up
    }
    std::cout << "\n";

    std::cout << "=== Example: Virtual Destructor (Polymorphism) ===\n";
    {
        Shape* shape1 = new Circle(5.0);
        Shape* shape2 = new Rectangle(10, 20);

        delete shape1; // Calls Circle destructor, then Shape destructor
        std::cout << "---\n";
        delete shape2; // Calls Rectangle destructor, then Shape destructor
    }
    std::cout << "\n";

    std::cout << "=== Example: Stack vs Heap ===\n";
    {
        std::cout << "Stack objects:\n";
        Counter c1;
        Counter c2;

        std::cout << "\nHeap object:\n";
        Counter* c3 = new Counter();
        Counter* c4 = new Counter();

        std::cout << "\nDeleting heap objects manually:\n";
        delete c3;
        delete c4;

        std::cout << "\nStack objects destroyed automatically:\n";
    }
}