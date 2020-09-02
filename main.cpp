#include <iostream>
#include <thread>

void myFunc() {
    std::cout << "Test" << std::endl;
}

class F {
public:
    void operator()() {
        for (int i = 0; i < 10; ++i) {
            std::cout << "Class" << std::endl;
        }
    }
};

int main() {
    F functor;

    std::thread t1(functor);

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
