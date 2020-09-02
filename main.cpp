#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

/*
 * Dead Lock 2 mutexin ayrı ayrı kullanacakları iki parametrenin lock edilmesi nedeniyle 2 parametreninde
 * diğerinin unlock edilmesini beklemesi nedeniyle lockta kalması
 */
class LogFile {
    std::mutex mutex;
    std::mutex mutex2;
    std::ofstream ofstream;

public:
    LogFile() {
        ofstream.open("log.txt");  // Ofstream'e threadlerin hepsi birlikte ulaşmaması için class içine tanımlayarak
        // işlemler yapılır.
    }
    void shared_print(const std::string& id, int value) {
        std::lock_guard<std::mutex> lockGuard(mutex);
        std::lock_guard<std::mutex> lockGuard2(mutex2);
        ofstream << "From " << id << " : " << value << std::endl;
    }
    void shared_print2(const std::string& id, int value) {
//        std::lock_guard<std::mutex> lockGuard2(mutex2);
//        std::lock_guard<std::mutex> lockGuard(mutex);
//      Dead Locka düşmemek için lock aynı sıra ile yapılmalı
        std::lock_guard<std::mutex> lockGuard(mutex);
        std::lock_guard<std::mutex> lockGuard2(mutex2);
        ofstream << "From " << id << " : " << value << std::endl;
    }
};

void myFunc(LogFile& logFile) {
    for (int i = 0; i > -10; i--) {
        logFile.shared_print("Call from t1:", i);
    }
}

int main() {
    LogFile logFile;

    std::thread t1(myFunc, std::ref(logFile));

    for (int i = 0; i < 10; ++i) {
        logFile.shared_print2("Call from Main:", i);
    }

    t1.join();

    return 0;
}
