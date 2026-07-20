// 22_atomic.cpp
// Topic: std::atomic (The unbreakable cookie jar!)
// To compile: g++ -std=c++11 22_atomic.cpp -pthread

#include <iostream>
#include <thread>
#include <atomic> // The toolbox for making unbreakable things

using namespace std;

// "atomic" means unbreakable or indivisible. 
// Normally, adding a cookie to a jar takes 3 steps: 1) Look at jar, 2) Get cookie, 3) Put it in.
// If two workers do this at the same time without a padlock, they get confused!
// std::atomic turns those 3 steps into ONE super-fast, magic step that nobody can interrupt.
// It's like a cookie jar that perfectly handles multiple hands at once, without needing a padlock!
atomic<int> shared_counter(0);

void increment_counter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // This looks normal, but because it's atomic, it is 100% safe!
        // No padlocks (mutexes) needed! It's usually faster than using a padlock too.
        shared_counter++; 
    }
}

int main() {
    // Both workers try to add 100,000 cookies.
    thread t1(increment_counter, 100000);
    thread t2(increment_counter, 100000);

    t1.join();
    t2.join();

    // Since the jar is atomic, we never lose a cookie!
    cout << "Final Cookie Count (Expected 200000): " << shared_counter << endl;
    
    return 0;
}

/*
EXPECTED OUTPUT:
Final Cookie Count (Expected 200000): 200000
*/
