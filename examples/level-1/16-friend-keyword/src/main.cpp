#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n), age(a) {}

    friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << "Name: " << p.name << ", Age: " << p.age;
    return out;
}

int main() {
    Person john("John Doe", 30);
    std::cout << john << std::endl;
}