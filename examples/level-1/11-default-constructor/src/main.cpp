#include <iostream>
#include <string>

// COMPILER-GENERATED DEFAULT CONSTRUCTOR
class Entity {
 public:
  int x;
  std::string name;
  // Compiler generates: Entity() {}
};

// USER-DEFINED DEFAULT CONSTRUCTOR (No Parameters)
class Person {
  std::string name;
  int age;

 public:
  Person() : name("Unknown"), age(0) {
    std::cout << "Person default constructor called\n";
  }

  void display() const {
    std::cout << "Name: " << name << ", Age: " << age << "\n";
  }
};

// USER-DEFINED DEFAULT CONSTRUCTOR (All Parameters Have Defaults)
class Point {
  int x;
  double y;

 public:
  Point(int px = 42, double py = 3.14) : x(px), y(py) {
    std::cout << "Point constructor: x = " << x << ", y = " << y << "\n";
  }
};

// COMPILER WON'T GENERATE DEFAULT CONSTRUCTOR

// Example 1: Has a parameterized constructor
class NoDefaultBecauseOfParams {
 public:
  int value;

  NoDefaultBecauseOfParams(int v) : value(v) {
    std::cout << "Parameterized constructor called\n";
  }
  // No default constructor available!
};

// Example 2: Has const/reference members without initializers
class NoDefaultBecauseOfMembers {
 public:
  const int x;  // const without initializer
  int& ref;     // reference without initializer
  // Compiler CANNOT generate default constructor

  // Must provide explicit constructor
  NoDefaultBecauseOfMembers(int val, int& r) : x(val), ref(r) {
    std::cout << "Parameterized constructor called\n";
  }
};

// Example 3: Has const/reference members WITH initializers
class HasDefaultWithInitializers {
 public:
  const int x = 10;
  int value = 42;
  int& ref = value;
  // Compiler CAN generate default constructor
};

// CUSTOM DEFAULT + PARAMETERIZED CONSTRUCTOR
class BothConstructors {
  int id;
  std::string description;

 public:
  // Explicit default constructor
  BothConstructors() : id(0), description("Default") {
    std::cout << "Default constructor called\n";
  }

  // Parameterized constructor
  BothConstructors(int i, const std::string& desc) : id(i), description(desc) {
    std::cout << "Pparameterized constructor called\n";
  }

  void display() const {
    std::cout << "ID: " << id << ", Desc: " << description << "\n";
  }
};

// EXPLICITLY DEFAULTED CONSTRUCTOR
class ExplicitlyDefaulted {
 public:
  int x;
  std::string name;

  ExplicitlyDefaulted() = default;  // Request compiler-generated version

  // Also have a parameterized constructor
  ExplicitlyDefaulted(int val, const std::string& n) : x(val), name(n) {}
};

int main() {
  std::cout << "COMPILER-GENERATED DEFAULT CONSTRUCTOR\n";
  Entity entity1;    // Default initialization (garbage)
  Entity entity2{};  // Value initialization (zero)
  std::cout << "Entity1.x: " << entity1.x << "\n";  // Undefined behavior
  std::cout << "Entity1.name: '" << entity1.name << "'\n\n";
  std::cout << "Entity2.x: " << entity2.x << "\n";
  std::cout << "Entity2.name: '" << entity2.name << "'\n\n";

  std::cout << "USER-DEFINED DEFAULT (No Params)\n";
  Person p1;
  p1.display();
  std::cout << "\n";

  std::cout << "USER-DEFINED DEFAULT (All Params Have Defaults)\n";
  Point pt1;            // Uses default values
  Point pt2(100);       // Uses custom x, default y
  Point pt3(200, 2.5);  // Uses both custom values
  std::cout << "\n";

  std::cout << "NO DEFAULT - Has Parameterized Constructor\n";
  // NoDefaultBecauseOfParams obj2;  // ERROR! No default constructor
  NoDefaultBecauseOfParams obj1(42);
  std::cout << "\n";

  std::cout << "NO DEFAULT - const/ref Without Initializers\n";
  int external = 99;
  // NoDefaultBecauseOfMembers obj3;  // ERROR! No default constructor
  NoDefaultBecauseOfMembers obj2(10, external);
  std::cout << "\n";

  std::cout << "HAS DEFAULT - const/ref With Initializers\n";
  HasDefaultWithInitializers obj3;  // OK! Compiler generates default
  std::cout << "obj4.x: " << obj3.x << "\n\n";

  std::cout << "BOTH DEFAULT AND PARAMETERIZED\n";
  BothConstructors bc1;  // Calls default
  bc1.display();
  BothConstructors bc2(123, "Custom");  // Calls parameterized
  bc2.display();
  std::cout << "\n";

  std::cout << "EXPLICITLY DEFAULTED\n";
  ExplicitlyDefaulted ed1{};            // Uses = default
  ExplicitlyDefaulted ed2(50, "Test");  // Uses parameterized
  std::cout << "ed1.x: " << ed1.x << "\n";
  std::cout << "ed2.x: " << ed2.x << "\n";
}
