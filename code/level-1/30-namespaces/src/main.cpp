#include <iostream>
#include <string>
#include <vector>

// BASIC NAMESPACE DEFINITION
namespace Math {
    const double PI = 3.14159265359;

    double circleArea(double radius) {
        return PI * radius * radius;
    }

    class Vector {
    public:
        double x, y;
        Vector(double x = 0, double y = 0)
            : x(x)
            , y(y) {}

        void print() const {
            std::cout << "Math::Vector(" << x << ", " << y << ")" << std::endl;
        }
    };
} // namespace Math

// NAMESPACE COLLISION DEMONSTRATION
namespace Collections {
    class Vector {
    private:
        std::vector<int> data;

    public:
        void add(int value) {
            data.push_back(value);
        }

        void print() const {
            std::cout << "Collections::Vector: [";
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i];
                if (i < data.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]" << std::endl;
        }
    };
} // namespace Collections

// NESTED NAMESPACES
namespace Company {
    namespace Graphics {
        namespace D2 {
            void render() {
                std::cout << "Rendering 2D graphics..." << std::endl;
            }
        } // namespace D2

        namespace D3 {
            void render() {
                std::cout << "Rendering 3D graphics..." << std::endl;
            }
        } // namespace D3
    } // namespace Graphics
} // namespace Company

// C++17 style nested namespace
namespace Project::Utils::String {
    std::string toUpper(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = std::toupper(c);
        }
        return result;
    }
} // namespace Project::Utils::String

// ANONYMOUS NAMESPACE (file-private functions)
namespace {
    // These are only visible in this file
    int secretCounter = 0;

    void incrementSecret() {
        secretCounter++;
    }

    std::string getSecret() {
        return "Secret value: " + std::to_string(secretCounter);
    }
} // namespace

// INLINE NAMESPACES (API Versioning)

namespace API {
    inline namespace V2 { // V2 is the default
        class Database {
        public:
            void connect() {
                std::cout << "Connecting with V2 protocol (fast & secure)" << std::endl;
            }
        };
    } // namespace V2

    namespace V1 { // Old version still accessible
        class Database {
        public:
            void connect() {
                std::cout << "Connecting with V1 protocol (legacy)" << std::endl;
            }
        };
    } // namespace V1
} // namespace API

// NAMESPACE ALIASES
namespace VeryLongCompanyNamespaceForUtilities {
    void process() {
        std::cout << "Processing data..." << std::endl;
    }
} // namespace VeryLongCompanyNamespaceForUtilities

// Create a shorter alias
namespace Utils = VeryLongCompanyNamespaceForUtilities;

// Alias for nested namespace
namespace GFX = Company::Graphics;

// GLOBAL SCOPE QUALIFIER DEMONSTRATION
int value = 100;

void demonstrateGlobalScope() {
    int value = 200; // Local variable shadows global

    std::cout << "\n=== GLOBAL SCOPE QUALIFIER ===" << std::endl;
    std::cout << "Local value: " << value << std::endl;
    std::cout << "Global value: " << ::value << std::endl;
}

int main() {
    // SCOPE RESOLUTION OPERATOR (::)
    std::cout << "SCOPE RESOLUTION OPERATOR" << std::endl;
    std::cout << "Circle area (radius=5): " << Math::circleArea(5.0) << std::endl;
    std::cout << "PI value: " << Math::PI << std::endl;
    std::cout << std::endl;

    // NAMESPACE COLLISION RESOLUTION
    std::cout << "RESOLVING NAMESPACE COLLISIONS" << std::endl;
    Math::Vector mathVec(3.0, 4.0);
    Collections::Vector collectionVec;

    mathVec.print();
    collectionVec.add(10);
    collectionVec.add(20);
    collectionVec.add(30);
    collectionVec.print();
    std::cout << std::endl;

    // USING DECLARATION (specific members)
    std::cout << "USING DECLARATION" << std::endl;
    {
        using Math::circleArea;
        using Math::PI;

        std::cout << "With using declaration - PI: " << PI << std::endl;
        std::cout << "Circle area: " << circleArea(3.0) << std::endl;
    }
    std::cout << std::endl;

    // NESTED NAMESPACES
    std::cout << "NESTED NAMESPACES" << std::endl;
    Company::Graphics::D2::render();
    Company::Graphics::D3::render();
    std::cout << "Uppercase: " << Project::Utils::String::toUpper("hello") << std::endl;
    std::cout << std::endl;

    // ANONYMOUS NAMESPACE
    std::cout << "ANONYMOUS NAMESPACE (file-private)" << std::endl;
    incrementSecret();
    incrementSecret();
    incrementSecret();
    std::cout << getSecret() << std::endl;
    std::cout << std::endl;

    // INLINE NAMESPACES (Versioning)
    std::cout << "7. INLINE NAMESPACES (API Versioning)" << std::endl;
    API::Database db1;     // Uses V2 by default (inline)
    API::V2::Database db2; // Explicitly V2
    API::V1::Database db3; // Explicitly V1

    db1.connect();
    db2.connect();
    db3.connect();
    std::cout << std::endl;

    // NAMESPACE ALIASES
    std::cout << "NAMESPACE ALIASES" << std::endl;
    Utils::process();  // Instead of VeryLongCompanyNamespaceForUtilities::process()
    GFX::D2::render(); // Instead of Company::Graphics::D2::render()
    std::cout << std::endl;

    // GLOBAL SCOPE QUALIFIER
    demonstrateGlobalScope();
    std::cout << std::endl;
}