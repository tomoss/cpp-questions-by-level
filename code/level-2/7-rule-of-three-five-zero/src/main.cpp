#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// RULE OF FIVE: Low-level RAII wrapper for dynamic array
class DynamicBuffer {
private:
    char* data;
    size_t size;

public:
    // Constructor
    DynamicBuffer(size_t sz)
        : data(new char[sz])
        , size(sz) {
        std::memset(data, 0, size);
        std::cout << "[RuleOfFive] Constructor: allocated " << size << " bytes\n";
    }

    // Destructor
    ~DynamicBuffer() {
        delete[] data;
        std::cout << "[RuleOfFive] Destructor: freed " << size << " bytes\n";
    }

    // Copy Constructor (Deep Copy)
    DynamicBuffer(const DynamicBuffer& other)
        : data(new char[other.size])
        , size(other.size) {
        std::memcpy(data, other.data, size);
        std::cout << "[RuleOfFive] Copy Constructor: copied " << size << " bytes\n";
    }

    // Copy Assignment Operator (Deep Copy)
    DynamicBuffer& operator=(const DynamicBuffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size];
            std::memcpy(data, other.data, size);
            std::cout << "[RuleOfFive] Copy Assignment: copied " << size << " bytes\n";
        }
        return *this;
    }

    // Move Constructor (Transfer Ownership)
    DynamicBuffer(DynamicBuffer&& other) noexcept
        : data(other.data)
        , size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "[RuleOfFive] Move Constructor: transferred ownership\n";
    }

    // Move Assignment Operator (Transfer Ownership)
    DynamicBuffer& operator=(DynamicBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "[RuleOfFive] Move Assignment: transferred ownership\n";
        }
        return *this;
    }
};

// RULE OF ZERO: Modern C++ with RAII types
class Employee {
private:
    std::string name;                // RAII type manages memory
    int id;                          // Primitive type
    std::vector<std::string> skills; // RAII type manages memory

public:
    Employee(std::string n, int empId)
        : name(std::move(n))
        , id(empId) {
        std::cout << "[RuleOfZero] Employee created: " << name << "\n";
    }

    // No destructor needed!
    // No copy constructor needed!
    // No copy assignment needed!
    // No move constructor needed!
    // No move assignment needed!
    // Compiler generates all of them correctly!

    void addSkill(const std::string& skill) {
        skills.push_back(skill);
    }

    void display() const {
        std::cout << "Employee: " << name << " (ID: " << id << ")\n";
        std::cout << "Skills: ";
        for (const auto& skill : skills) {
            std::cout << skill << " ";
        }
        std::cout << "\n";
    }
};

// DEMONSTRATION FUNCTIONS
void demonstrateRuleOfFive() {
    std::cout << "\n========== RULE OF FIVE ==========\n";

    DynamicBuffer buf1(64);
    DynamicBuffer buf2 = buf1; // Copy constructor
    DynamicBuffer buf3(32);
    buf3 = buf1; // Copy assignment
    // Move operations
    std::vector<DynamicBuffer> vec;
    vec.push_back(std::move(buf1)); // Move constructor
}

void demonstrateRuleOfZero() {
    std::cout << "\n========== RULE OF ZERO ==========\n";

    Employee emp1("Alice Johnson", 1001);
    emp1.addSkill("C++");
    emp1.addSkill("Python");
    emp1.display();

    // Copy works automatically (compiler-generated)
    Employee emp2 = emp1;
    std::cout << "\nCopied employee:\n";
    emp2.display();

    // Move works automatically!
    std::vector<Employee> team;
    team.push_back(std::move(emp1));
    std::cout << "\nEmployee moved to team vector\n";
}

int main() {
    demonstrateRuleOfFive();
    demonstrateRuleOfZero();
}