# 25. What is mutable keyword in C++?

## 💡Mutable with class members

The **mutable** keyword is used to indicate that a particular member of a class can be modified even if the class instance itself is declared as const.

In other words, the **mutable** keyword allows a member variable to be modified in a const member function.

### 🔹Common use cases

* **Synchronization (Mutexes)** → A mutable ```std::mutex``` allows a const member function to lock the mutex.

```cpp
class Cache {
    mutable std::mutex mtx;
    std::map<std::string, Data> data;
    
public:
    Data get(const std::string& key) const {
        std::lock_guard<std::mutex> lock(mtx);  // Need to lock, but function is const
        return data[key];
    }
};
```

* **Logging or Debug Counters** → You might want to increment a mutable counter inside a const function to track how many times it's called.

```cpp
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
};
```

* **Caching** → Storing computed results to avoid recalculation.

```cpp
class DataAnalyzer {
private:
    std::vector<int> data;
    mutable double cachedMean;
    mutable bool meanCalculated;
    
public:
    DataAnalyzer(std::vector<int> d) 
        : data(d), meanCalculated(false), cachedMean(0.0) {}
    
    double getMean() const {  // const function
        if (!meanCalculated) {
            // Calculate mean (expensive operation)
            double sum = 0;
            for (int val : data) sum += val;
            cachedMean = sum / data.size();  // OK because mutable
            meanCalculated = true;
        }
        return cachedMean;  // Return cached result
    }
};
```

* **Lazy initialization** → Computing values only when first needed.

```cpp
class Report {
private:
    std::string reportData;
    mutable std::string formattedReport;

    std::string formatReport(const std::string& raw) const {
        // Expensive formatting logic here
        return "Formatted: " + raw;
    }
    
public:
    const std::string& getFormatted() const {
        if (formattedReport.empty()) {
            // Do expensive formatting only when first requested
            formattedReport = formatReport(reportData);
        }
        return formattedReport;
    }
};
```

### 🔹Why keep the function const?
For the caching example, you might wonder "Why not just make `getMean()` non-const?"

**Answer:** Because const correctness matters:
```cpp
void analyzeData(const DataAnalyzer& analyzer) {  // const reference
    double mean = analyzer.getMean();  // Only works if getMean() is const!
}
```
If `getMean()` weren't const, you couldn't call it on const objects or const references. The `mutable` keyword lets internal optimizations work while maintaining the logical const-ness of the function.

---

## 💡Mutable with lambdas

The keyword **mutable** in the context of a lambda expression allows the lambda to modify the variables it captures by value.

### 🔹Capture by reference (modifiable by default)

If we capture by reference, everything is fine. We can modify the value inside lambda:

```cpp
int main() {
	int x = 8;
	auto f = [&]() {
		x++;
		std::cout << x << std::endl;
	};

	f();
}
```

### 🔹Capture by value (not modifiable by default)

But if we want to capture it by value, we cannot modify ```x``` inside the lambda:

```cpp
int main() {
    int x = 5;
    auto f = [=]() {
        x++; // Compilation error: 'x': a by copy capture cannot be modified in a non-mutable lambda
        std::cout << x << std::endl;
    };
}
```

### 🔹Making captured values modifiable with mutable

To solve this problem, we can say that this lambda is mutable. What it means is that variables that you pass by a value, you can change them. The outside variable ```x``` will still be 5.


```cpp
int main() {
    int x = 5;
    auto f = [=]() mutable {
        x++;
        std::cout << x << std::endl;  // Prints: 6
    };
    f();
    std::cout << x << std::endl;  // Prints: 5 (original unchanged)
}
```

---

