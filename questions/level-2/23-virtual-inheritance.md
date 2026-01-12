# 23. Explain virtual inheritance.

## 💡Definition

**Virtual inheritance** is a C++ feature that solves the diamond problem by ensuring that only one copy of the common base class exists in the derived class, even when inherited through multiple paths.

---

## 💡Example

```cpp
#include <iostream>
using namespace std;

class A {
public:
    void show() { cout << "A" << endl; }
};

class B : public A { };
class C : public A { };
class D : public B, public C { };

int main() {
    D obj;
    // obj.show(); // ❌ Ambiguous: show() exists in both B::A and C::A
}
```

**Problem:** Class D ends up with two separate copies of A, one via B, one via C.

**Solution:** We use virtual inheritance so that B and C share a single instance of A.

```cpp
#include <iostream>
using namespace std;

class A {
public:
    void show() { cout << "A" << endl; }
};

class B : virtual public A { };
class C : virtual public A { };
class D : public B, public C { };

int main() {
    D obj;
    obj.show(); // ✅ No ambiguity: only one A in memory
}
```

---

## 🧪 Code example
- [`../../examples/level-2/23-virtual-inheritance`](../../examples/level-2/23-virtual-inheritance)
