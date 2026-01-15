#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;
int counter = 0;

void increment() {
    std::lock_guard<std::mutex> lock(m);
    ++counter;
    std::cout << "increment -> " << counter << "\n";
}

void decrement() {
    std::unique_lock<std::mutex> lock(m);
    --counter;
    std::cout << "decrement -> " << counter << "\n";
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void try_increment() {
    std::unique_lock<std::mutex> lock(m, std::try_to_lock);
    if (!lock) {
        // try_increment -> busy, skipped
        return;
    }
    ++counter;
    std::cout << "try_increment -> " << counter << "\n";
}

void deferred_increment() {
    std::unique_lock<std::mutex> lock(m, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // prep work
    lock.lock();
    ++counter;
    std::cout << "deferred_increment -> " << counter << "\n";
}

int main() {
    std::thread t1(increment);
    std::thread t2(deferred_increment);
    std::thread t3(decrement);
    std::thread t4(try_increment);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
