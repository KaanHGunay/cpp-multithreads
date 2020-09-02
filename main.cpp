#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

class LogFile {
    std::mutex mutex;
    std::ofstream ofstream;

public:
    LogFile() {
        ofstream.open("log.txt");  // Ofstream'e threadlerin hepsi birlikte ulaşmaması için class içine tanımlayarak
        // işlemler yapılır.
    }
    void shared_print(std::string id, int value) {
        std::lock_guard<std::mutex> lockGuard(mutex);
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
        logFile.shared_print("Call from Main:", i);
    }

    t1.join();

    return 0;
}
