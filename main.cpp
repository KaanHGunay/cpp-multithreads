#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

class LogFile {
    std::mutex mutex;
    std::mutex mutex2;
    std::ofstream ofstream;

public:
    LogFile() {
        ofstream.open("log.txt");
    }
    void shared_print(const std::string& id, int value) {
        std::lock(mutex, mutex2);
        std::lock_guard<std::mutex> lockGuard(mutex, std::adopt_lock);
        std::lock_guard<std::mutex> lockGuard2(mutex2, std::adopt_lock);
        ofstream << "From " << id << " : " << value << std::endl;
    }
    void shared_print2(const std::string& id, int value) {
        {
            std::lock_guard<std::mutex> lockGuard(mutex, std::adopt_lock);
            // ...
        }
        {
            std::lock_guard<std::mutex> lockGuard2(mutex2, std::adopt_lock);
            // ...
        }
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
