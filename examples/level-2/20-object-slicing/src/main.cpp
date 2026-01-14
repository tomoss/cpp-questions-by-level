#include <iostream>

// Base class
class Shape {
public:
    virtual void draw() const {
        std::cout << "Drawing a generic shape." << std::endl; 
    }
};

// Derived class
class Circle : public Shape {
public:
    double radius;
    void draw() const override { 
        std::cout << "Drawing a circle with radius: " << radius << std::endl;
    }
};

int main() {
    Circle myCircle;
    myCircle.radius = 10.0;

    // Slicing happens here!
    Shape myShape = myCircle;

    // myShape no longer has the 'radius' member.
    // Calling draw() on myShape will call Shape::draw(), not Circle::draw().
    myShape.draw();
}