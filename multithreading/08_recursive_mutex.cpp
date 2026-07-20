// 08_recursive_mutex.cpp
// Topic: std::recursive_mutex (A padlock that lets you lock it multiple times if you already have the key!)
// To compile: g++ -std=c++11 08_recursive_mutex.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// recursive_mutex is a magic padlock. Normally, if you lock a door, and then try to lock it again
// from the inside, you get stuck forever!
// But a recursive_mutex remembers WHO locked it. If YOU locked it, it lets you lock it again and again!
recursive_mutex r_mtx;
int buffer = 0;

// This is a "recursive" function. It's a function that calls itself!
void recursion(char workerLetter, int loopFor) {
    if (loopFor < 0) return; // Stop when we count down to zero.
    
    // Lock the door!
    r_mtx.lock();
    cout << workerLetter << " is adding to buffer: " << buffer++ << endl;
    
    // The function CALLS ITSELF here.
    // That means it will try to lock the door AGAIN while it's already locked!
    // Because we use recursive_mutex, it says: "Oh, it's you again. Go ahead!"
    recursion(workerLetter, --loopFor);
    
    // We must unlock the door exactly as many times as we locked it!
    r_mtx.unlock(); 
}

int main() {
    // Worker A and Worker B both try to do the recursive job.
    thread t1(recursion, 'A', 5);
    thread t2(recursion, 'B', 5);

    t1.join();
    t2.join();

    return 0;
}

/*
EXPECTED OUTPUT:
(One worker will finish ALL their prints from 0 to 5, and then the other will print 6 to 11)
A is adding to buffer: 0
A is adding to buffer: 1
A is adding to buffer: 2
A is adding to buffer: 3
A is adding to buffer: 4
A is adding to buffer: 5
B is adding to buffer: 6
B is adding to buffer: 7
B is adding to buffer: 8
B is adding to buffer: 9
B is adding to buffer: 10
B is adding to buffer: 11
*/
