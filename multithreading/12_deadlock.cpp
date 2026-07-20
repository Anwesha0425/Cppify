// 12_deadlock.cpp
// Topic: Deadlock (When two workers get stuck forever!)
// To compile: g++ -std=c++11 12_deadlock.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// Two padlocks for two different toys.
mutex m1;
mutex m2;

void thread1() {
    m1.lock(); // Worker 1 grabs Toy 1
    cout << "Worker 1 locked m1 (Toy 1)." << endl;
    this_thread::sleep_for(chrono::milliseconds(10)); 
    
    cout << "Worker 1 is waiting for m2 (Toy 2)..." << endl;
    // Worker 1 wants Toy 2, but Worker 2 is holding it! So Worker 1 waits forever.
    m2.lock(); 
    
    cout << "Worker 1 doing work..." << endl; // This will never happen in a deadlock!
    m2.unlock();
    m1.unlock();
}

void thread2() {
    m2.lock(); // Worker 2 grabs Toy 2
    cout << "Worker 2 locked m2 (Toy 2)." << endl;
    this_thread::sleep_for(chrono::milliseconds(10));
    
    cout << "Worker 2 is waiting for m1 (Toy 1)..." << endl;
    // Worker 2 wants Toy 1, but Worker 1 is holding it! So Worker 2 waits forever.
    m1.lock(); 
    
    cout << "Worker 2 doing work..." << endl;
    m1.unlock();
    m2.unlock();
}

int main() {
    cout << "WARNING: A Deadlock is like two dogs holding opposite ends of a stick. Neither will let go, so neither can win!" << endl;
    
    // To actually freeze your program forever, you would remove the "//" on the lines below!
    // thread t1(thread1);
    // thread t2(thread2);
    // t1.join();
    // t2.join();

    cout << "Program finished smoothly because we didn't actually run the stuck workers!" << endl;
    return 0;
}

/*
EXPECTED OUTPUT:
WARNING: A Deadlock is like two dogs holding opposite ends of a stick. Neither will let go, so neither can win!
Program finished smoothly because we didn't actually run the stuck workers!
*/
