#include <iostream>
#include <memory>

int* bad() {
    int x = 10;
    return &x;   // ❌ returns address of local variable
}

std::unique_ptr<int> good() {
    return std::make_unique<int>(10);
}

int main() {
    int* p1 = bad();
    std::cout << *p1 << "\n";  // ❌ dangling pointer

    auto p2 = good();
    std::cout << *p2 << "\n";  // safe
}
