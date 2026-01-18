#include <iostream>

/* A simple struct to represent a point */
struct Point1 {
    int x;
    int y;
};

/* A simple class to represent a point */
class Point2 {
    int x;
    int y;
};

class Base {
public:
    int val = 5;
};

struct Derived1 : Base { /* by default public Base*/
};

class Derived2 : Base { /* by default private Base*/
};

int main() {
    Point1 p1;
    p1.x = 10; // OK: x is public in struct Point1

    Point2 p2;
    // p2.x = 10; // Error: x is private in class Point2

    Derived1 d1;
    std::cout << d1.val << std::endl;
    Derived2 d2;
    // std::cout << d2.val << std::endl; ---> Not accesible
}