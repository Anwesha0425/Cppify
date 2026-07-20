// 06_std_try_lock.cpp
// Topic: std::try_lock (Trying to grab multiple toys at once!)
// To compile: g++ -std=c++11 06_std_try_lock.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// Two padlocks for two different toys.
mutex m1, m2;

void consumeXY() {
    int useCount = 5; // We want to play with both toys 5 times.
    int XplusY = 0;
    
    while(1) {
        // std::try_lock tries to grab ALL the padlocks you list (m1 and m2).
        // If it gets ALL of them, it returns -1 (meaning "Success!").
        // If it fails (maybe someone else has m2), it returns the number of the lock it failed on (like 0 for m1, or 1 for m2),
        // and it instantly drops any locks it ALREADY grabbed, so it's not being greedy!
        int lockResult = try_lock(m1, m2);
        
        if (lockResult == -1) {
            // Yay! We got both locks!
            if(useCount != 0) {
                cout << "Acquired both locks, playing with toys..." << endl;
                useCount--;
                XplusY += 1;
            }
            
            // We are done playing, so unlock both toys.
            m1.unlock();
            m2.unlock();
            
            // If we've played 5 times, we can go home.
            if (useCount == 0) break;
            
        } else {
            // Oh no, we couldn't get both toys. The lockResult tells us which one was taken!
            cout << "Failed to grab lock number: " << lockResult << ". I'll try again soon!" << endl;
        }
        
        // Take a tiny 50-millisecond nap before trying again, so we don't go crazy checking the locks a million times a second.
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

int main() {
    // Both workers want to play with the same two toys.
    thread t1(consumeXY);
    thread t2(consumeXY);

    t1.join();
    t2.join();

    return 0;
}

/*
EXPECTED OUTPUT:
(Output will be a mix of both workers succeeding and failing)
Acquired both locks, playing with toys...
Failed to grab lock number: 1. I'll try again soon!
Acquired both locks, playing with toys...
...
*/
