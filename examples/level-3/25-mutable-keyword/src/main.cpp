#include <iostream>

class Entity {
private:
	std::string m_name = "default";
	mutable int m_debugCount = 0;

public:
	const std::string& getName() const {
		//m_name = "Change it"; -> Can't do it, the method is const.
		m_debugCount++; // -> Can do it, despite the method being const, because m_debugCount is mutable.
		return m_name;
	}

    const int& getDebugCount() const {
        return m_debugCount;
    }
};

int main() {
    const Entity e;
    std::cout << e.getName() << std::endl;
    std::cout << e.getName() << std::endl;
    std::cout << e.getName() << std::endl;

    std::cout << "Debug count: " << e.getDebugCount() << std::endl;
}

