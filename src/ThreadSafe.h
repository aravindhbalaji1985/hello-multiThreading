#ifndef _THREAD_SAFE_H_
#define _THREAD_SAFE_H_
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
#include <mutex>        // std::mutex

// NOTE: This code was done based on the idea detailed in
// https://stackoverflow.com/questions/2196155/is-there-anyway-to-write-the-following-as-a-c-macro
class ThreadSafeCout: public std::ostringstream
{
public:
    ThreadSafeCout(){};
    ~ThreadSafeCout()
    {
        std::lock_guard<std::mutex> guard(_mtxPrint);
        std::cout << this->str();
    }

private:
    static std::mutex _mtxPrint;
};

// Initialize the mutex
std::mutex ThreadSafeCout::_mtxPrint{};
#endif