#include <iostream>
#include <thread>

void myFunc() {
    std::cout << "Test" << std::endl;
}

class F {
public:
    void operator()(const std::string& msg) {
        for (int i = 0; i < 10; ++i) {
            std::cout << "Class: " << msg  << std::endl;
        }
    }
};

int main() {
    // Oversubscription

    std::cout << std::thread::hardware_concurrency() << std::endl; // Donanıma gelen thread sayısı

    return 0;
}
