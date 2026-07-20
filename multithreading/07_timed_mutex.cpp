// 07_timed_mutex.cpp
// Topic: std::timed_mutex (Waiting in line for a specific amount of time!)
// To compile: g++ -std=c++11 07_timed_mutex.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// timed_mutex is a special padlock. You can tell it: "I will wait for exactly 10 seconds. 
// If it's still locked after 10 seconds, I'm going home!"
timed_mutex t_mtx;
int shared_amount = 0;

void increment(int workerID) {
    // We create a stopwatch set to 1 second.
    auto timeout = chrono::seconds(1);
    
    // try_lock_for() says: "Try to unlock the door, but only wait up to 'timeout' (1 second)."
    // If we get in within 1 second, it returns 'true'.
    // If the 1 second runs out, it returns 'false' and walks away.
    if (t_mtx.try_lock_for(timeout)) {
        ++shared_amount;
        
        // We got inside! Now let's be rude and stay inside for 2 seconds.
        this_thread::sleep_for(chrono::seconds(2)); 
        
        cout << "Worker " << workerID << " entered and got a cookie!" << endl;
        t_mtx.unlock(); // Finally unlock the door.
        
    } else {
        // We waited 1 second, but the door never opened!
        cout << "Worker " << workerID << " couldn't enter (got tired of waiting for 1 second!)." << endl;
    }
}

int main() {
    // Start two workers at the exact same time.
    thread t1(increment, 1);
    thread t2(increment, 2);

    t1.join();
    t2.join();
    
    // One worker will get in first and lock the door for 2 seconds.
    // The second worker will wait outside, but their patience runs out after 1 second!
    // So the second worker gives up and leaves before the first worker even comes out!
    return 0;
}

/*
EXPECTED OUTPUT:
Worker 2 couldn't enter (got tired of waiting for 1 second!).
Worker 1 entered and got a cookie!
*/
