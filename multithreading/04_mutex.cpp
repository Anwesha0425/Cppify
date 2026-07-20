// 04_mutex.cpp
// Topic: Mutex (Taking turns with a padlock!)
// To compile: g++ -std=c++11 04_mutex.cpp -pthread

#include <iostream> // For printing text.
#include <thread>   // For mini-workers.
#include <mutex>    // For the padlock (mutex).

using namespace std;

// This is our cookie jar. Both workers want to add cookies to it.
int shared_counter = 0;

// "mutex" stands for Mutual Exclusion. Think of it as a padlock on the cookie jar.
// Only ONE person can hold the key and open the jar at a time!
mutex mtx;

void increment_counter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // .lock() means "Grab the key and lock the door!" 
        // If someone else already has the key, we just wait outside the door until they are done.
        mtx.lock();
        
        // This is the "Critical Section" (the important part where we touch the cookie jar).
        // Since we locked the door, we know NOBODY else is touching the jar right now. It's totally safe!
        shared_counter++; 
        
        // .unlock() means "We are done! Put the jar down and unlock the door so the next person can use it."
        mtx.unlock();
    }
}

int main() {
    // Create two workers. They will both try to add 100,000 cookies to the same jar.
    thread t1(increment_counter, 100000);
    thread t2(increment_counter, 100000);

    // Wait for both workers to finish.
    t1.join();
    t2.join();

    // Because we used a padlock (mutex), they took turns perfectly!
    // If we didn't use a padlock, they would have bumped hands and dropped cookies, and the number would be wrong!
    cout << "Final Cookie Counter Value: " << shared_counter << endl;
    
    return 0;
}

/*
EXPECTED OUTPUT:
Final Cookie Counter Value: 200000
*/
