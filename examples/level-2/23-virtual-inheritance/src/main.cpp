#include <iostream>

class A {
public:
    void show() { std::cout << "A" << std::endl; }
};

class B : virtual public A { };
class C : virtual public A { };
class D : public B, public C { };

int main() {
    D obj;
    obj.show(); // ✅ No ambiguity: only one A in memory
}