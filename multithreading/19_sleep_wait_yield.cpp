// 19_sleep_wait_yield.cpp
// Topic: std::this_thread::yield (Being polite and letting others go first!)
// To compile: g++ -std=c++11 19_sleep_wait_yield.cpp -pthread

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// sleep_for: "I am taking a nap for exactly 5 seconds."
// wait: "I am going to sleep until someone wakes me up with a walkie-talkie."
// yield: "I am being polite. If anyone else wants to use the computer's brain right now, they can go ahead of me! Otherwise, I'll keep going."

void yieldTask(int workerID) {
    for (int i = 0; i < 5; ++i) {
        cout << "Worker " << workerID << " is doing a chore..." << endl;
        
        // "Yield" means stepping aside in the lunch line to let someone else grab food.
        // It helps keep the computer from freezing up if this worker has a really long, boring job.
        this_thread::yield(); 
    }
}

int main() {
    // Both workers are very polite!
    thread t1(yieldTask, 1);
    thread t2(yieldTask, 2);
    
    t1.join();
    t2.join();
    
    return 0;
}

/*
EXPECTED OUTPUT:
(Because they are yielding to each other, they will usually take turns nicely!)
Worker 1 is doing a chore...
Worker 2 is doing a chore...
Worker 1 is doing a chore...
Worker 2 is doing a chore...
*/
