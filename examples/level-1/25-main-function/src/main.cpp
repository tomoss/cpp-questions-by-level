#include <iostream>

// Valid main() function - standard entry point
int main() {
    std::cout << "Standard main() function called\n";
    return 0;
}

// COMPILATION ERROR: Attempting to overload main()
// Uncommenting the code below will cause a compilation error
/*
int main(int x) {
    std::cout << "Overloaded main() with int parameter: " << x << "\n";
    return 0;
}

int main(double d) {
    std::cout << "Overloaded main() with double parameter: " << d << "\n";
    return 0;
}
*/