#include <iostream>
#include <string>

// CONST CONSTANTS
const float APP_VERSION = 2.1f;
const std::string APP_NAME = "ConstDemo";

// CONST REFERENCES
void printMessage(const std::string& msg) {
    // msg += "!"; // Error: msg is const
    std::cout << msg << std::endl;
}

// CONST POINTERS
void demonstrateConstPointers() {
    int a = 10, b = 20;

    // Pointer to const data - can't modify data, can reassign pointer
    const int* ptr1 = &a;
    std::cout << "ptr1 points to: " << *ptr1 << std::endl;
    // *ptr1 = 15; // ❌ Error
    ptr1 = &b; // ✅ OK
    std::cout << "ptr1 now points to: " << *ptr1 << std::endl;

    // Const pointer - can't reassign pointer, can modify data
    int* const ptr2 = &a;
    *ptr2 = 30; // ✅ OK
    std::cout << "Modified a via ptr2: " << a << std::endl;
    // ptr2 = &b;  // ❌ Error

    // Const pointer to const data - can't do either
    const int* const ptr3 = &a;
    // *ptr3 = 40; // ❌ Error
    // ptr3 = &b;  // ❌ Error
    std::cout << "ptr3 points to (read-only): " << *ptr3 << std::endl;
}

// CONST OBJECTS AND CONST METHODS
class BankAccount {
private:
    std::string owner;
    double balance;

public:
    BankAccount(const std::string& name, double initial)
        : owner(name)
        , balance(initial) {}

    // Const method - promises not to modify object state
    double getBalance() const {
        return balance;
    }

    // Const method
    std::string getOwner() const {
        return owner;
    }

    // Non-const method
    void deposit(double amount) {
        balance += amount;
    }

    // CONST OVERLOADING
    // Non-const version - returns modifiable reference
    double& getBalanceRef() {
        std::cout << "  [Non-const version called]" << std::endl;
        return balance;
    }

    // Const version - returns const reference
    const double& getBalanceRef() const {
        std::cout << "  [Const version called]" << std::endl;
        return balance;
    }
};

void printAccountInfo(const BankAccount& account) {
    // Can only call const methods on const reference
    std::cout << "Owner: " << account.getOwner() << std::endl;
    std::cout << "Balance: $" << account.getBalance() << std::endl;
    // account.deposit(100); // ❌ Error: deposit() is not const
}

// CONST REFERENCE DATA MEMBERS
class Logger {
private:
    const std::string& appName; // Const reference member

public:
    // Must initialize const reference in initializer list
    Logger(const std::string& name)
        : appName(name) {}

    void log(const std::string& message) const {
        std::cout << "[" << appName << "] " << message << std::endl;
    }
};

int main() {
    // Using const constants
    std::cout << "\nConst Constants:" << std::endl;
    std::cout << "App: " << APP_NAME << " v" << APP_VERSION << std::endl;

    // Const references
    std::cout << "\nConst References:" << std::endl;
    std::string greeting = "Hello, World";
    printMessage(greeting);

    // Demonstrating that const reference doesn't freeze the original
    int x = 5;
    const int& ref = x;
    std::cout << "ref = " << ref << std::endl;
    x = 10;
    std::cout << "After x = 10, ref = " << ref << std::endl;

    // Const pointers
    std::cout << "\nConst Pointers:" << std::endl;
    demonstrateConstPointers();

    // Const methods
    std::cout << "\nConst methods:" << std::endl;
    const BankAccount constAccount("Bob", 2000.0);
    printAccountInfo(constAccount);

    // Const reference data members
    std::cout << "\nConst Reference Data Members:" << std::endl;
    Logger logger(APP_NAME);
    logger.log("Application started");
    logger.log("Processing data...");

    // Const overloading
    std::cout << "\nConst Overloading:" << std::endl;
    BankAccount acc("Charlie", 500.0);
    const BankAccount constAcc("Diana", 750.0);

    std::cout << "Calling getBalanceRef() on non-const object:" << std::endl;
    acc.getBalanceRef() = 600.0; // Calls non-const, can modify
    std::cout << "New balance: $" << acc.getBalance() << std::endl;

    std::cout << "Calling getBalanceRef() on const object:" << std::endl;
    const double& bal = constAcc.getBalanceRef(); // Calls const version
    std::cout << "Balance: $" << bal << std::endl;
    // bal = 800.0; // ❌ Error: can't modify through const reference
}