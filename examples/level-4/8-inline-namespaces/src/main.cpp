#include "geometry.h"
#include <iostream>

int main() {
    // Modern code (uses v2 by default)
    Geometry::Point p1{0, 0, 0}; // 3D point
    Geometry::Point p2{3, 4, 5}; // 3D point
    double d = Geometry::distance(p1, p2);
    std::cout << "3D distance: " << d << "\n";

    // Legacy code (explicitly use v1)
    Geometry::v1::Point old_p1{0, 0}; // 2D point
    Geometry::v1::Point old_p2{3, 4}; // 2D point
    double old_d = Geometry::v1::distance(old_p1, old_p2);
    std::cout << "2D distance: " << old_d << "\n";

    // This would NOT compile (type mismatch):
    // Geometry::distance(p1, old_p1);  // Error!

    return 0;
}