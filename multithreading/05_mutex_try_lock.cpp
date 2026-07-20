// 05_mutex_try_lock.cpp
// Topic: std::mutex::try_lock (Checking if the door is locked, and walking away if it is!)
// To compile: g++ -std=c++11 05_mutex_try_lock.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0; // Our shared cookie jar.
mutex mtx;       // Our padlock.

void increaseTheCounterFor100000Time() {
    for (int i = 0; i < 100000; ++i) {
        // try_lock() is like jiggling the doorknob.
        // It asks: "Is the door unlocked?"
        // If it IS unlocked, it locks it immediately, returns "true", and we go inside!
        // If it IS locked, it returns "false" and walks away instantly. It DOES NOT wait around!
        if (mtx.try_lock()) {
            ++counter; // Add a cookie safely.
            mtx.unlock(); // Unlock the door when done.
        } else {
            // The door was locked! 
            // Instead of standing around waiting (like .lock() does), we just shrug and skip this cookie.
            // We could go do other chores here instead!
        }
    }
}

int main() {
    // Both workers are going to try to add cookies 100,000 times each.
    thread t1(increaseTheCounterFor100000Time);
    thread t2(increaseTheCounterFor100000Time);

    t1.join();
    t2.join();

    // Because they use try_lock(), if the door was locked, they just skipped adding that cookie!
    // So the final number will almost certainly be LESS than 200,000. They missed a lot of cookies!
    cout << "Counter could increase up to: " << counter << " (Notice it is less than 200000!)" << endl;

    return 0;
}

/*
EXPECTED OUTPUT:
(The number will be random, but usually less than 200000 because workers gave up instead of waiting!)
Counter could increase up to: 145321 (Notice it is less than 200000!)
*/
