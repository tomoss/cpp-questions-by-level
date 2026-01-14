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
    // Calls Shape's draw(), not Circle's
    myShape.draw();

    // No slicing: reference preserves dynamic type
    Shape& ref = myCircle;
    ref.draw();   // Calls Circle::draw()

    // No slicing: pointer preserves dynamic type
    Shape* ptr = &myCircle;
    ptr->draw();  // Calls Circle::draw()
}