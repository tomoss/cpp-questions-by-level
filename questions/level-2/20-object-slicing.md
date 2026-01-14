# 20. What is object slicing?

## 💡Definition

**Object slicing** occurs when a derived class object is copied or assigned to an object of the base class.

During this process, the additional attributes and methods of the derived class are lost or *"sliced"* away. What remains is just the base class subobject.

This typically happens when you:

* Pass a derived class object **by value** to a function that expects a base class object.
* Assign a derived class object to a base class variable.

---

## 💡Example

```cpp
// Base class
class Shape {
public:
    virtual void draw() const { /* draws a generic shape */ }
};

// Derived class
class Circle : public Shape {
public:
    double radius;
    void draw() const override { /* draws a circle */ }
};
```

Object slicing occurs in the following scenario:

```cpp
Circle myCircle;
myCircle.radius = 10.0;

// Slicing happens here!
Shape myShape = myCircle;

// myShape no longer has the 'radius' member.
// Calling draw() on myShape will call Shape::draw(), not Circle::draw().
myShape.draw();
```

Using **pointers** or **references** is the standard way to handle objects polymorphically in C++ and prevent object slicing.

---

## 🧪 Code example
- [`../../examples/level-2/20-object-slicing`](../../examples/level-2/20-object-slicing)
