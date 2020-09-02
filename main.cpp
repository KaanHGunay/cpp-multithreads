#include <iostream>
#include <thread>
#include <mutex>

std::mutex mu;

// Printlerin farklı threadlerde karışmaması için
void shared_print(std::string message, int id) {
    std::lock_guard<std::mutex> guard(mu);
    // mu.lock();
    std::cout << message << id << std::endl;
    // mu.unlock();
}

void myFunc() {
    for (int i = 0; i > -10; i--) {
        shared_print("Call from t1:", i);
    }
}

int main() {
    std::thread t1(myFunc);

    for (int i = 0; i < 10; ++i) {
        shared_print("Call from Main:", i);
    }

    t1.join();

    return 0;
}
