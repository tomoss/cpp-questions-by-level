# 8. Explain inline namespaces.

## 💡Definition

An **inline namespace** is a C++ feature (introduced in C++11) where a nested namespace is declared with the inline keyword. This makes all members of that nested namespace behave—for lookup and access purposes—as if they were members of the enclosing namespace.

---

## 💡Basic Syntax

```cpp
namespace MyLib {
    inline namespace v2 {
        void func();
    }
}
```
With this declaration, both ```MyLib::v2::func()``` and ```MyLib::func()``` refer to the same function. The inline keyword makes the nested namespace transparent from the outside.

---

## 💡Key Properties

**Transitive**: Inline namespaces are transitive. If A contains inline namespace B, 
which contains inline namespace C, then C's members are visible directly in A.

**Name Mangling:** ```MyLib::func()``` and ```MyLib::v2::func()``` both resolve to the same entity, so they produce the same mangled symbol (e.g., _ZN5MyLib2v24funcEv), which includes the version in the binary symbol even though source code can omit it.

---

## 💡Primary Use Case: Versioning

The most common use is for API versioning. You can maintain multiple versions of your library while controlling which is the default:

```cpp
namespace MyLib {
    namespace v1 {
        class Widget { /* old implementation */ };
    }
    
    inline namespace v2 {
        class Widget { /* new implementation */ };
    }
}

// Users can write:
MyLib::Widget w;  // Gets v2::Widget (the default)

// Or explicitly request the old version:
MyLib::v1::Widget oldW;  // Gets v1::Widget
```

This allows:

* New code to automatically use the latest version without changing source code.

* Each version to produce distinct binary symbols (e.g., ```MyLib::v1::Widget``` vs ```MyLib::v2::Widget```), preventing symbol collisions.

* Old binaries compiled against v1 and new binaries compiled against v2 can coexist in the same process without conflicts, as long as they don't pass versioned objects across their API boundaries.

* Source code compatibility (write MyLib::Widget) while maintaining binary versioning (symbols include version info).

---

