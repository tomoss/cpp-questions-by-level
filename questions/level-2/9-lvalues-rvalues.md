# 9. Difference between lvalue and rvalue?

## 💡 Definition

[Value categories](https://en.cppreference.com/w/cpp/language/value_category.html)

In C++, expressions fall into **value categories**. Informally we talk about **lvalues** and **rvalues**, but formally C++ has: lvalue, xvalue, prvalue, rvalue and glvalue.

This distinction is crucial for understanding assignments, references and modern C++ features like **move semantics** and **perfect forwarding**.

---

## 💡 lvalue 

An **lvalue** refers to an object that has a persistent identity. You can refer to the same object via different expressions or across different lines of code.

* **Identity:** Named objects/variables are always lvalues.
* **Address:** You can usually take its address with `&`.
* **Assignment:** Can appear on the Left-Hand Side (LHS) of an assignment (`x = 5`).
* **Persistence:** It exists beyond the expression where it's defined.

```cpp
int x;  // x is an lvalue
x = 10; // OK: x is on the left side and can be modified

int* p = &x; // OK: We can take the address of an lvalue.

const int cx = 5; // cx is still an lvalue
// cx = 6;        // ERROR: not assignable because const
```

---

## 💡 rvalues (prvalue + xvalue)

An **rvalue** is either:

* **prvalue**: a *pure* temporary value (e.g., literals, results of arithmetic)
* **xvalue**: an *expiring* object (often produced by `std::move`), which still refers to a real object

### 🔹prvalue

These are *temporary* in the purest sense. They are often literals or the result of a calculation that hasn't been stored yet.

* **No Identity:** You cannot take its address directly (`&5` is invalid).
* **Assignment:** A prvalue expression cannot be the left-hand side (LHS) of an assignment.
* **Usage:** Appears on the right-hand side (RHS) of assignment.

```cpp
int x = 10;        // 10 is a prvalue
int y = x + 5;     // (x + 5) is a prvalue

// 10 = x;          // ERROR: prvalue is not assignable
// int* p = &(x+5); // ERROR: cannot take address of a prvalue expression
```

### 🔹xvalue (expiring value)

An xvalue is an object that has an identity (it lives somewhere in memory) but is treated as expiring, enabling moves.

* **Source:** Most commonly created via `std::move`.
* **Important:** `std::move` does not move anything by itself, it just casts to an xvalue.
* **Assignment:** Can be on left-hand side (LHS) because they have identity. However, assigning to an xvalue is almost never what you want to do.
* **The Trap:** Even though an xvalue has identity, the language forbids taking its address with `&` to prevent you from holding a pointer to something that is about to be moved or destroyed.


```cpp
std::string s = "Hello";
std::string t = std::move(s);  // std::move(s) is an xvalue

std::move(s) = "World";        // OK: xvalue CAN be assigned to (has identity)
// int* p = &std::move(s);     // ERROR: cannot take address of xvalue (even though it has identity)
```

---

## 💡 The "Identity vs. Movability" Matrix

<table border="1" cellpadding="6" cellspacing="0">
  <tr>
    <th>Category</th>
    <th>Has Identity?</th>
    <th>Is Moveable?</th>
    <th>Example</th>
  </tr>
  <tr>
    <td>lvalue</td>
    <td>✅ Yes</td>
    <td>❌ No</td>
    <td><code>x, obj.member</code></td>
  </tr>
  <tr>
    <td>xvalue</td>
    <td>✅ Yes</td>
    <td>✅ Yes</td>
    <td><code>std::move(x)</code></td>
  </tr>
  <tr>
    <td>prvalue</td>
    <td>❌ No</td>
    <td>✅ Yes</td>
    <td><code>42, x + y</code></td>
  </tr>
</table>


---

## 💡 Lvalue References (`&`)

This is the *standard* reference you're likely familiar with. It acts as an alias for an existing lvalue.

**Rule:** An lvalue reference (`T&`) can only bind to an lvalue.

**Exception:** A const lvalue reference (`const T&`) can bind to an rvalue (extends temporary lifetime).

This exception is particularly useful for function parameters, allowing you to accept both lvalues and rvalues efficiently without copying:

```cpp
int x = 10;

int& a = x;          // OK: binds to lvalue
// int& b = 10;      // ERROR: cannot bind non-const lvalue ref to rvalue

const int& c = 10;   // OK: const lvalue ref binds to rvalue (lifetime extended)

// Common pattern: accepting both lvalues and rvalues efficiently
void process(const std::string& s) { 
    // No copy needed - works with both temporaries and named objects
}

std::string name = "Alice";
process(name);           // OK: lvalue
process("Bob");          // OK: rvalue (string literal converted to temporary)
```

## 💡 Rvalue References (`&&`)

An rvalue reference is designed to bind to rvalues (especially xvalues) and is the foundation of move semantics.

**Rule:** An rvalue reference (`T&&`) can only bind to an rvalue.

It was introduced in C++11 to enable move semantics and perfect forwarding, improving performance by avoiding unnecessary copies.

```cpp
int&& rref1 = 10;   // OK: binds to rvalue (prvalue)

int x = 10;
int&& rref3 = x;    // ERROR: x is an lvalue.

int&& rref2 = std::move(x); // OK: binds to xvalue
```

---

## 💡 Reference Binding Rules

<table border="1" cellpadding="6" cellspacing="0">
  <tr>
    <th>Reference Type</th>
    <th>Can bind to lvalue?</th>
    <th>Can bind to rvalue?</th>
  </tr>
  <tr>
    <td><code>T&</code></td>
    <td>✅ Yes</td>
    <td>❌ No</td>
  </tr>
  <tr>
    <td><code>const T&</code></td>
    <td>✅ Yes</td>
    <td>✅ Yes (Lifetime extended)</td>
  </tr>
  <tr>
    <td><code>T&&</code></td>
    <td>❌ No</td>
    <td>✅ Yes</td>
  </tr>
</table>

---
