#include <iostream>
#include <string>
#include <utility>

class Resource {
public:
    // 1. Lvalue Reference Overload (The "Copy" path)
    void process(const std::string& s) {
        std::cout << "[LVALUE PATH] Copying: " << s << "\n";
        data = s; // Triggers copy assignment
    }

    // 2. Rvalue Reference Overload (The "Move" path)
    void process(std::string&& s) {
        std::cout << "[RVALUE PATH] Moving/Stealing: " << s << "\n";
        // CRUCIAL: 's' is an lvalue here because it has a name.
        // std::move(s) casts it back to an xvalue so 'data' can steal the pointer.
        data = std::move(s);
    }

    const std::string& getData() const {
        return data;
    }

private:
    std::string data;
};

int main() {
    Resource res;

    // Scenario A: Standard lvalue
    std::string text = "Persistent Data";
    res.process(text); // Calls (const std::string&)

    // Scenario B: prvalue (Pure temporary)
    res.process(std::string("Temporary Data")); // Calls (std::string&&)

    // Scenario C: xvalue (Explicit move)
    res.process(std::move(text)); // Calls (std::string&&)

    // Scenario D: The "Const" Trap (Sparring Partner Addition)
    const std::string permanent = "I cannot be moved";
    res.process(std::move(permanent)); // SURPRISE: Calls (const std::string&)
    // Why? You cannot steal from a 'const' object, so it falls back to copying.
}