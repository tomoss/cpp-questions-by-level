#include <iostream>

class Box;
void printBox(const Box* box);

class Box {
  double width{};
  double height{};

 public:
  void setDimensions(double width, double height) {
    this->width = width;
    this->height = height;
    printBox(this);
  }

  double getWidth() const { return width; }
  double getHeight() const { return height; }

  bool isSame(const Box& other) const { return this == &other; }
};

void printBox(const Box* box) {
  std::cout << "Box [width = " << box->getWidth()
            << " ][height = " << box->getHeight() << " ]\n";
}

class Counter {
  int value{};

 public:
  Counter(int v = 0) : value(v) {}
  Counter& increment() {
    ++value;
    return *this;
  }
  Counter& decrement() {
    --value;
    return *this;
  }
  void show() const { std::cout << value << '\n'; }
};

int main() {
  Counter c;
  c.increment().increment().decrement().show();

  Box b;
  b.setDimensions(5, 10);
}