// 09_lock_guard.cpp
// Topic: std::lock_guard (A robot helper that unlocks the door for you!)
// To compile: g++ -std=c++11 09_lock_guard.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx; // A normal padlock
int buffer = 0;

void task(const char* workerName, int loopFor) {
    // std::lock_guard is a smart robot. 
    // The moment you create it, it automatically locks the padlock ('mtx').
    // The best part? When the function is over and the robot is destroyed,
    // it AUTOMATICALLY unlocks the padlock! You never have to write ".unlock()" yourself!
    // This is super safe because even if the program crashes in the middle, the door still gets unlocked.
    
    lock_guard<mutex> lock(mtx); // Door is locked right HERE.
    
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        cout << workerName << " changed buffer to " << buffer << endl;
    }
    
    // The function ends here. The 'lock' robot is destroyed, and the door is AUTOMATICALLY unlocked!
}

int main() {
    thread t1(task, "Worker T1", 5);
    thread t2(task, "Worker T2", 5);

    t1.join();
    t2.join();

    return 0;
}

/*
EXPECTED OUTPUT:
(One worker finishes completely, then the next worker finishes completely)
Worker T1 changed buffer to 1
Worker T1 changed buffer to 2
Worker T1 changed buffer to 3
Worker T1 changed buffer to 4
Worker T1 changed buffer to 5
Worker T2 changed buffer to 6
Worker T2 changed buffer to 7
Worker T2 changed buffer to 8
Worker T2 changed buffer to 9
Worker T2 changed buffer to 10
*/
