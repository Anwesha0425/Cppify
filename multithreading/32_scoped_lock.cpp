// 32_scoped_lock.cpp
// Topic: std::scoped_lock (Grabbing multiple toys without fighting!)
// To compile: g++ -std=c++17 32_scoped_lock.cpp -pthread

#include <iostream> // For printing to the screen.
#include <thread>   // For creating mini-workers (threads).
#include <mutex>    // For creating "locks" (like a padlock on a toy).
#include <chrono>   // For measuring time, like a super-accurate digital stopwatch.

using namespace std;

// Imagine two very special toys: Toy 1 (m1) and Toy 2 (m2).
// A "mutex" is like a padlock you put on the toy so only one person can play with it at a time.
mutex m1; 
mutex m2; 

// This is the job for our first worker.
void task_a() {
    // std::scoped_lock is a super smart robot arm that can grab MULTIPLE padlocks at the exact same time!
    // It's available in C++17. If it tries to grab m1 and m2, and someone else has one, it waits patiently
    // without getting stuck forever (a situation called a "deadlock").
    scoped_lock lock(m1, m2);
    
    cout << "Task A has locked m1 (Toy 1) and m2 (Toy 2) safely!" << endl;
    
    // chrono::milliseconds(50) means 50 tiny slices of a second.
    // this_thread::sleep_for makes the worker take a quick nap.
    this_thread::sleep_for(chrono::milliseconds(50));
}

// This is the job for our second worker.
void task_b() {
    // Notice that Task B tries to grab the toys in the REVERSE order (m2 then m1).
    // Normally, this could cause a "deadlock" where A waits for B, and B waits for A forever!
    // But scoped_lock is so smart, it prevents this from happening.
    scoped_lock lock(m2, m1);
    
    cout << "Task B has locked m2 (Toy 2) and m1 (Toy 1) safely!" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(50));
}

int main() {
    // Create two mini-workers. One does task_a, the other does task_b.
    thread t1(task_a);
    thread t2(task_b);
    
    // Wait for both workers to finish playing and put the toys away.
    t1.join();
    t2.join();
    
    cout << "Both tasks completed without getting stuck (deadlock)!" << endl;
    return 0;
}

/*
EXPECTED OUTPUT:
(Either Task A or Task B will go first, but they will never get stuck forever!)

Task A has locked m1 (Toy 1) and m2 (Toy 2) safely!
Task B has locked m2 (Toy 2) and m1 (Toy 1) safely!
Both tasks completed without getting stuck (deadlock)!
*/
