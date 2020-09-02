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
    std::string msg = "Test";
    std::thread t1((F()), msg);  // MOST VEXING SYNTAX
    std::thread t2 = std::move(t1);

    t2.join();

    return 0;
}
