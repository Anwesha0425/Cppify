// 33_atomic_flag_spinlock.cpp
// Topic: std::atomic_flag and Spinlocks (A lock that never goes to sleep)
// To compile: g++ -std=c++11 33_atomic_flag_spinlock.cpp -pthread

#include <iostream> // For printing to the screen.
#include <thread>   // For creating mini-workers (threads).
#include <atomic>   // For "atomic" tools. "Atomic" means unbreakable. If a thread does an atomic action, nobody can interrupt it!
#include <vector>   // For making a list (like a shopping list) of threads.

using namespace std;

// Imagine a bathroom door with a simple "OCCUPIED" or "VACANT" sign.
// std::atomic_flag is exactly that sign. It's the simplest unbreakable tool in C++.
class Spinlock {
    // ATOMIC_FLAG_INIT means the sign starts as "VACANT" (false).
    atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        // test_and_set() is a magic move: it checks the sign, and instantly flips it to "OCCUPIED".
        // If the sign was ALREADY "OCCUPIED" (true), it returns true, meaning we have to wait.
        // A "Spinlock" means instead of going to sleep, the worker stands at the door and spins in circles checking "Is it ready? Is it ready? Is it ready?!"
        while (flag.test_and_set(memory_order_acquire)) {
            // Spin-wait (just keep looping really fast until the door is unlocked)
        }
    }
    
    void unlock() {
        // clear() flips the sign back to "VACANT" (false).
        flag.clear(memory_order_release);
    }
};

Spinlock spinlock; // Our bathroom door lock!
int shared_counter = 0; // A jar of cookies everyone is trying to add to.

void work() {
    // Each worker tries to add 10,000 cookies to the jar.
    for (int i = 0; i < 10000; ++i) {
        spinlock.lock();   // Lock the door (spin until we get in)
        shared_counter++;  // Add a cookie!
        spinlock.unlock(); // Unlock the door for the next person
    }
}

int main() {
    // Create a list to hold 10 workers.
    vector<thread> threads;
    for (int i = 0; i < 10; ++i) {
        // Add a new worker to the list and tell them to do the "work".
        threads.push_back(thread(work));
    }
    
    // Wait for all 10 workers to finish their jobs.
    for (auto& t : threads) {
        t.join();
    }
    
    // 10 workers * 10,000 cookies = 100,000 cookies!
    cout << "Final counter value (expected 100000): " << shared_counter << endl;
    return 0;
}

/*
EXPECTED OUTPUT:
Final counter value (expected 100000): 100000
*/
