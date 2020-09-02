#include <iostream>
#include <thread>

void myFunc() {
    std::cout << "Test" << std::endl;
}

int main() {
    std::thread t1(myFunc);

//    t1.join(); // Ana thread i beklet thread bitine kadar

//    t1.detach(); // Ana thread den ayrı çıkaltır

    if (t1.joinable()) { // Join olma durumuna göre joinle
        t1.join();
    }


    return 0;
}
