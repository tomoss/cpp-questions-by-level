// geometry.h - Version 2.0
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>

namespace Geometry {
    // Old version (kept for backward compatibility)
    namespace v1 {
        struct Point {
            double x, y; // 2D
        };

        double distance(Point a, Point b);
    } // namespace v1

    // New version (default)
    inline namespace v2 {
        struct Point {
            double x, y, z; // 3D
        };

        double distance(Point a, Point b);
    } // namespace v2
} // namespace Geometry

#endif // GEOMETRY_H