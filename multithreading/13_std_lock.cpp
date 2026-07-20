// 13_std_lock.cpp
// Topic: std::lock (A smart referee that prevents deadlocks!)
// To compile: g++ -std=c++11 13_std_lock.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex m1;
mutex m2;

void task_a() {
    // std::lock is a smart referee. You ask it to lock multiple padlocks at once.
    // It's super smart and knows exactly how to grab them WITHOUT getting stuck (deadlocking).
    lock(m1, m2);
    
    // We hand the locked padlocks to our robot helpers (lock_guard).
    // 'adopt_lock' tells the robot: "Hey, the padlock is ALREADY locked. Just remember to unlock it when you die."
    lock_guard<mutex> lock1(m1, adopt_lock);
    lock_guard<mutex> lock2(m2, adopt_lock);
    
    cout << "Worker A safely grabbed Toy 1 and Toy 2!" << endl;
}

void task_b() {
    // Worker B asks the referee for the toys in the REVERSE order.
    // Normally, this causes a deadlock! But our referee (std::lock) handles it perfectly.
    lock(m2, m1);
    
    lock_guard<mutex> lock1(m2, adopt_lock);
    lock_guard<mutex> lock2(m1, adopt_lock);
    
    cout << "Worker B safely grabbed Toy 2 and Toy 1!" << endl;
}

int main() {
    thread t1(task_a);
    thread t2(task_b);

    t1.join();
    t2.join();

    return 0;
}

/*
EXPECTED OUTPUT:
Worker A safely grabbed Toy 1 and Toy 2!
Worker B safely grabbed Toy 2 and Toy 1!
*/
