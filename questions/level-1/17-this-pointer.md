# 17. What is the `this` pointer?

## 💡Definition
* It's a pointer that holds the memory address of the object on which the member function was called.
* A pointer to the current object.
* It points to the object that invoked the function.

---

## 💡Notes
- `this` is not available in **static member functions** (since they aren’t tied to any object).
- The type of `this`:
  - In a non-const member function: `ClassName* const`
  - In a const member function: `const ClassName* const`
- `this` itself is a const pointer, it cannot be reassigned

---

## ❓Can you use this inside a static member function? Why?

No. `this` does not exist in static member functions because they are not associated with any object instance. `this` is a pointer to a specific object. `static` member functions belong to the class and can be called without creating an object.

---

## 💡Common use cases

### 1. To diferentiate member variables from parameters

When a member function's parameter has the same name as a class member variable, you use this to specify that you're referring to the member variable.

```cpp
class Box {
private:
    double width;
    double height;
public:
    // The parameters 'width' and 'height' have the same names
    // as the member variables.
    void setDimensions(double width, double height) {
        // 'this->width' refers to the member variable of the object.
        // 'width' refers to the function parameter.
        this->width = width;
        this->height = height;
    }
};
```

### 2. To return the current object for method chaining

Member functions can return a reference to their own object by returning `*this`. This allows you to *chain* multiple function calls together in a single statement.

```cpp
class Counter {
    int value;
public:
    Counter(int v=0) : value(v) {}
    Counter& increment() { value++; return *this; }
    Counter& decrement() { value--; return *this; }
    void show() { cout << value << endl; }
};

int main() {
    Counter c;
    c.increment().increment().decrement().show(); // 1
}
```

### 3. To pass the current object to another function

A member function might need to pass a pointer to its own object to an external function. The this pointer provides a direct way to do that.

```cpp
// Member function that calls a global function with its own address
void Link::shareLink() {
    printLink(this);
}

// Global function that accepts a pointer to an object
void printLink(const Link* linkPtr) {
    // ... uses the pointer ...
}
```

### 4. To compare addresses (check if two objects are the same)

```cpp
bool isSame(const Person& other) const {
    return this == &other;
}
```

---

## 🧪 Code example
- [`../../code/level-1/17-this-pointer`](../../code/level-1/17-this-pointer)
