#include <iostream>

struct Base {
    Base() {
        std::cout << "Base constructor\n";
        f(); // Calls Base::f, not Derived::f
    }

    virtual void f() {
        std::cout << "Base::f\n";
    }

    virtual ~Base() {
        std::cout << "Base destructor\n";
    }
};

struct Derived : Base {
    Derived() {
        std::cout << "Derived constructor\n";
        f(); // Now calls Derived::f
    }

    void f() override {
        std::cout << "Derived::f\n";
    }

    ~Derived() override {
        std::cout << "Derived destructor\n";
    }
};

int main() {
    std::cout << "Creating Derived as Base*\n";
    Base* obj = new Derived();

    std::cout << "\nCalling virtual function after construction\n";
    obj->f(); // Calls Derived::f

    std::cout << "\nDeleting through base pointer\n";
    delete obj;
}
