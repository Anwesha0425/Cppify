// 30_volatile_vs_atomic.cpp
// Topic: volatile vs std::atomic (A very important warning!)
// To compile: g++ -std=c++11 30_volatile_vs_atomic.cpp -pthread

#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// "volatile" is an old keyword. It tells the computer: 
// "Don't try to be clever and memorize this number. Always read it fresh from memory!"
// BUT!!! It does NOT stop workers from crashing into each other (Data Race).
// NEVER, EVER use 'volatile' to protect things in multithreading! It is fake armor!
volatile int fake_armor_counter = 0;

// "std::atomic" is REAL armor. It is unbreakable and perfectly safe for workers to share.
atomic<int> real_armor_counter(0);

void increment() {
    for (int i = 0; i < 100000; ++i) {
        // Two workers doing this at the same time will crash and lose numbers!
        fake_armor_counter++; 
        
        // Two workers doing this is 100% safe.
        real_armor_counter++;   
    }
}

int main() {
    // Two workers try to count to 100,000 each. The total should be 200,000.
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Expected total count: 200000" << endl;
    
    // The fake armor failed! They lost a bunch of numbers while crashing into each other.
    cout << "Fake Armor (volatile): " << fake_armor_counter << " (FAILED!)" << endl;
    
    // The real armor worked perfectly!
    cout << "Real Armor (atomic): " << real_armor_counter << " (SUCCESS!)" << endl;

    return 0;
}

/*
EXPECTED OUTPUT:
Expected total count: 200000
Fake Armor (volatile): 123456 (FAILED!)
Real Armor (atomic): 200000 (SUCCESS!)
*/
