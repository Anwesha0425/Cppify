// 10_unique_lock.cpp
// Topic: std::unique_lock (A smarter, more flexible robot helper!)
// To compile: g++ -std=c++11 10_unique_lock.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
int buffer = 0;

void task(const char* workerName, int loopFor) {
    // std::unique_lock is like lock_guard's big brother.
    // It's a robot helper, but you can give it more complex instructions.
    
    // "defer_lock" tells the robot: "Hold this padlock, but DON'T lock it yet!"
    unique_lock<mutex> lock(mtx, std::defer_lock); 
    
    // Sometime later, we can tell the robot to lock it manually.
    lock.lock(); 
    
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        cout << workerName << " changed buffer to " << buffer << endl;
    }
    
    // We can also tell the robot to unlock it manually before the function ends!
    // Why? Because it's polite to unlock the door as early as possible so others can use it.
    lock.unlock(); 
    
    // (If we forgot to unlock it, unique_lock is smart enough to unlock it automatically when the function ends anyway!)
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
