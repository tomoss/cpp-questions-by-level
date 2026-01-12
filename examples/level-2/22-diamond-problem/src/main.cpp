#include <iostream>

class Base {
private:
    int data;
public:
    void setData(int value) { data = value; }
    int getData() { return data; }
};

class Derived1 : public Base {};

class Derived2 : public Base {};

class FinalDerived : public Derived1, public Derived2 {
public:
    void showData() {
        // std::cout << getData() << std::endl; // ERROR: Ambiguity here
        std::cout << Derived1::getData() << std::endl;
        std::cout << Derived2::getData() << std::endl;
    }
};

int main() {
    FinalDerived obj;
    // obj.setData(5); // ERROR: Ambiguity here
    obj.Derived1::setData(10); // Set data through Derived1
    obj.Derived2::setData(20); // Set data through Derived2

    obj.showData(); // Ambiguity: Which data to print?
}