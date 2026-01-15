#include "geometry.h"

namespace Geometry {
    namespace v1 {
        double distance(Point a, Point b) {
            double dx = b.x - a.x;
            double dy = b.y - a.y;
            return std::sqrt(dx * dx + dy * dy);
        }
    } // namespace v1

    namespace v2 {
        double distance(Point a, Point b) {
            double dx = b.x - a.x;
            double dy = b.y - a.y;
            double dz = b.z - a.z;
            return std::sqrt(dx * dx + dy * dy + dz * dz);
        }
    } // namespace v2
} // namespace Geometry