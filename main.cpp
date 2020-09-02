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

    try {  // Threadde herhangi bir hata olursa diğer kodları engellememesi için
        for (int i = 0; i < 10; ++i) {
            std::cout << "Main" << std::endl;
        }
    } catch (...) {
        t1.join();  // Her durumda threadleri birleştirmek için
        throw;
    }

    t1.join();

    return 0;
}
