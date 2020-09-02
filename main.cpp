#include <iostream>
#include <thread>

void myFunc() {
    std::cout << "Test" << std::endl;
}

int main() {
    std::thread t1(myFunc);

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
