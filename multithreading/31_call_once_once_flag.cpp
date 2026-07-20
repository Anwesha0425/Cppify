// 31_call_once_once_flag.cpp
// Topic: std::call_once and std::once_flag (Making sure something happens ONLY ONE time)
// To compile: g++ -std=c++11 31_call_once_once_flag.cpp -pthread

// #include is how we tell the computer to bring in special toolboxes.
#include <iostream> // Brings in the toolbox for printing text to the screen (like cout).
#include <thread>   // Brings in the toolbox for making "threads" (mini-workers in our program).
#include <mutex>    // Brings in tools to keep our mini-workers from fighting over data.

// "using namespace std" is a shortcut so we don't have to type "std::" before standard words like cout.
using namespace std;

// Imagine a magic flag that starts rolled up. Once someone unrolls it, it can never be unrolled again!
// "once_flag" is that magic flag. We call ours "init_flag".
once_flag init_flag;

// This is the special job we only want to happen ONE time, no matter how many workers try to do it.
void initialize_shared_resource() {
    cout << "--> WOW! The initialization function executed! This should only print ONCE." << endl;
}

// This is the job that each of our mini-workers (threads) will do.
void worker(int id) {
    cout << "Thread " << id << " is running and trying to do the special job." << endl;
    
    // std::call_once is a magic spell. It tells the worker: 
    // "Look at the init_flag. If it's rolled up, unroll it and do 'initialize_shared_resource'. 
    // If someone else already unrolled it, skip it and do nothing!"
    call_once(init_flag, initialize_shared_resource);
    
    cout << "Thread " << id << " continues working on other things." << endl;
}

// "main" is the starting line where our program begins.
int main() {
    // We create three mini-workers (threads) named t1, t2, and t3.
    // We tell them to run the "worker" function and give them ID badges: 1, 2, and 3.
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);
    
    // ".join()" means "Hey main program, wait here until this mini-worker is finished!"
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}

/* 
EXPECTED OUTPUT:
(The order of the "running" messages might change because workers are racing, 
but the "WOW!" message will ALWAYS only show up exactly one time!)

Thread 1 is running and trying to do the special job.
--> WOW! The initialization function executed! This should only print ONCE.
Thread 1 continues working on other things.
Thread 2 is running and trying to do the special job.
Thread 2 continues working on other things.
Thread 3 is running and trying to do the special job.
Thread 3 continues working on other things.
*/
