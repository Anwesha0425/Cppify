// 03_join_detach_joinable.cpp
// Topic: join(), detach() and joinable() (Waiting vs. Letting Go)
// To compile: g++ -std=c++11 03_join_detach_joinable.cpp -pthread

#include <iostream> // For printing text.
#include <thread>   // For mini-workers (threads).
#include <chrono>   // For our stopwatch (time).

using namespace std;

// Job for the first worker.
void task1() {
    cout << "Worker 1 started its job." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Sleep for 2 seconds.
    cout << "Worker 1 finished its job." << endl;
}

// Job for the second worker.
void task2() {
    cout << "Worker 2 started its job." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Sleep for 1 second.
    cout << "Worker 2 finished its job." << endl;
}

int main() {
    thread t1(task1); // Create Worker 1
    
    // 1. joinable(): This asks, "Is this worker still tied to us and active?"
    if (t1.joinable()) {
        cout << "Worker 1 is joinable, boss is waiting..." << endl;
        // 2. join(): The boss (main program) STOPS and waits here until Worker 1 is completely done.
        t1.join(); 
    }
    
    // Once we join, the worker is no longer "joinable" (the job is over).
    if (!t1.joinable()) {
        cout << "Worker 1 is done and no longer joinable." << endl;
    }

    thread t2(task2); // Create Worker 2
    
    if (t2.joinable()) {
        cout << "Worker 2 is joinable, calling detach()..." << endl;
        // 3. detach(): The boss says "I'm cutting the string! You go do your thing in the background. I'm not waiting!"
        t2.detach(); 
    }
    
    if (!t2.joinable()) {
        cout << "Worker 2 was cut loose (detached), so it's no longer joinable." << endl;
    }

    // Since we cut Worker 2 loose, the boss will move on. 
    // We put the boss to sleep for 2 seconds just so we have enough time to see Worker 2's prints on the screen before the whole program ends!
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Main program (boss) finished." << endl;
    
    return 0;
}

/*
EXPECTED OUTPUT:
Worker 1 started its job.
Worker 1 is joinable, boss is waiting...
Worker 1 finished its job.
Worker 1 is done and no longer joinable.
Worker 2 is joinable, calling detach()...
Worker 2 was cut loose (detached), so it's no longer joinable.
Worker 2 started its job.
Worker 2 finished its job.
Main program (boss) finished.
*/
