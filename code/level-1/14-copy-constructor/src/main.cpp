#include <cstring>
#include <iostream>
#include <string>

// Default copy constructor is enough
// No raw pointers; std::string handles its own memory.
class Student {
    int age;
    std::string name;

public:
    Student(int age, std::string name)
        : age(age)
        , name(name) {}

    void setName(const std::string& n) {
        name = n;
    }
    void display(const std::string& label) const {
        std::cout << label << ": Student(" << age << ", " << name << ")\n";
    }
};

void demo_default_copy() {
    std::cout << "\n==============================\n";
    std::cout << " Default copy\n";
    std::cout << "==============================\n";

    Student s1(22, "Alice");

    Student s2 = s1; // copy-initialization  — copy constructor called
    Student s3(s1);  // direct-initialization — copy constructor called

    // Modifying s1 does NOT affect s2 or s3 (std::string does deep copy)
    s1.setName("Alice MODIFIED");

    s1.display("s1");
    s2.display("s2"); // still "Alice"
    s3.display("s3"); // still "Alice"
}

// SHALLOW COPY PROBLEM
// Compiler-generated copy just copies the pointer value.
// Both objects end up pointing to the same memory — danger!
class ShallowBuffer {
public:
    char* data;

    ShallowBuffer(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        std::cout << "  [ShallowBuffer] Constructed. Data: " << (void*)data << "\n";
    }

    // No custom copy constructor — compiler generates a shallow one

    ~ShallowBuffer() {
        std::cout << "  [ShallowBuffer] Destroyed. Data: " << (void*)data << "\n";
        delete[] data; // double-delete if another object shares this pointer!
    }
};

void demo_shallow_copy_problem() {
    std::cout << "\n==============================\n";
    std::cout << " Shallow Copy Problem\n";
    std::cout << "==============================\n";

    ShallowBuffer a("hello");
    ShallowBuffer b = a; // shallow copy — b.data == a.data (same address!)

    std::cout << "  a.data @ " << (void*)a.data << "  value: " << a.data << "\n";
    std::cout << "  b.data @ " << (void*)b.data << "  value: " << b.data << "\n";
    std::cout << "  Same pointer? " << (a.data == b.data ? "YES <- danger!" : "no") << "\n";
    std::cout << "  (Nulling b.data to prevent double-delete crash in this demo)\n";
    b.data = nullptr; // in real code YOU wouldn't do this; use deep copy instead
}

// DEEP COPY — Custom copy constructor
// Each object gets its own independent allocation.
class DeepString {
    char* buffer;
    size_t length;

public:
    DeepString(const char* str) {
        length = strlen(str);
        buffer = new char[length + 1];
        strcpy(buffer, str);
        std::cout << "  [DeepString] Constructed  \"" << buffer << "\"  @ " << (void*)buffer << "\n";
    }

    // Deep copy constructor
    DeepString(const DeepString& other) {
        length = other.length;
        buffer = new char[length + 1]; // NEW allocation — independent copy
        strcpy(buffer, other.buffer);
        std::cout << "  [DeepString] Copy constructed \"" << buffer << "\"  @ " << (void*)buffer << "\n";
    }

    void setChar(size_t i, char c) {
        if (i < length)
            buffer[i] = c;
    }

    void display(const std::string& label) const {
        std::cout << "  " << label << ": \"" << buffer << "\"  @ " << (void*)buffer << "\n";
    }

    ~DeepString() {
        std::cout << "  [DeepString] Destroyed   \"" << buffer << "\"  @ " << (void*)buffer << "\n";
        delete[] buffer;
    }
};

void demo_deep_copy() {
    std::cout << "\n==============================\n";
    std::cout << " Deep Copy\n";
    std::cout << "==============================\n";

    DeepString original("hello");
    DeepString copy = original; // deep copy constructor called

    // Mutate the copy — original must be unaffected
    copy.setChar(0, 'H');

    original.display("original"); // "hello"
    copy.display("copy    ");     // "Hello"
}

// ============================================================
// DELETED COPY CONSTRUCTOR — prevent copying entirely
// ============================================================
class NonCopyable {
    int value;

public:
    explicit NonCopyable(int v)
        : value(v) {}
    NonCopyable(const NonCopyable&) = delete;            // no copy
    NonCopyable& operator=(const NonCopyable&) = delete; // no copy-assign

    void display() const {
        std::cout << "  NonCopyable(" << value << ")\n";
    }
};

void demo_deleted_copy() {
    std::cout << "\n==============================\n";
    std::cout << " Deleted Copy Constructor\n";
    std::cout << "==============================\n";

    NonCopyable a(42);
    a.display();

    // Uncommenting the line below would cause a compile error:
    // NonCopyable b = a;  // error: use of deleted function

    std::cout << "  (Copying is disabled, compile error if attempted)\n";
}

// INHERITANCE — must explicitly call Base copy constructor
class Base {
protected:
    std::string baseName;

public:
    Base(const std::string& name)
        : baseName(name) {
        std::cout << "  [Base] Constructed: " << baseName << "\n";
    }

    Base(const Base& other)
        : baseName(other.baseName) {
        std::cout << "  [Base] Copy constructed: " << baseName << "\n";
    }
};

class Derived : public Base {
    int extra;

public:
    Derived(const std::string& name, int extra)
        : Base(name)
        , extra(extra) {}

    // Explicitly forward to Base copy constructor
    Derived(const Derived& other)
        : Base(other) // <-- copies the Base subobject correctly
        , extra(other.extra) {
        std::cout << "  [Derived] Copy constructed: " << baseName << ", extra=" << extra << "\n";
    }

    void display(const std::string& label) const {
        std::cout << "  " << label << ": Derived(\"" << baseName << "\", " << extra << ")\n";
    }
};

void demo_inheritance() {
    std::cout << "\n==============================\n";
    std::cout << " 6. Inheritance\n";
    std::cout << "==============================\n";

    Derived d1("Widget", 7);
    Derived d2 = d1; // calls Derived copy ctor -> which calls Base copy ctor

    d1.display("d1");
    d2.display("d2");
}

int main() {
    demo_default_copy();
    demo_shallow_copy_problem();
    demo_deep_copy();
    demo_deleted_copy();
    demo_inheritance();
}