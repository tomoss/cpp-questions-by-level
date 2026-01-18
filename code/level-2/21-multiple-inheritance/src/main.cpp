#include <iostream>

class A {
public:
    void show() {
        std::cout << "A" << std::endl;
    }
};

class B {
public:
    void show() {
        std::cout << "B" << std::endl;
    }
};

class C : public A, public B {
public:
    void display() {
        // show()   // ERROR: Ambiguity
        A::show(); // Explicitly call show() from A
        B::show(); // Explicitly call show() from B
    }
};

int main() {
    C objC;
    // objC.show();  // ERROR: Ambiguity
    objC.A::show(); // Explicitly call show() from A
    objC.B::show(); // Explicitly call show() from B
}