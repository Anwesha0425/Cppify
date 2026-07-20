// 25_jthread.cpp
// Topic: std::jthread (The C++20 smart worker who knows when to quit!)
// To compile: g++ -std=c++20 25_jthread.cpp -pthread

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// In C++20, we got "jthread" (joining thread).
// It's much smarter than a regular thread. It automatically joins when it finishes,
// AND we can send it a polite message asking it to stop working early!

// "stop_token" is like a pager we give the worker. We can beep it to say "Stop!"
void interruptibleTask(stop_token stoken) {
    int count = 0;
    
    // The worker constantly checks their pager: "Did the boss ask me to stop yet?"
    while (!stoken.stop_requested()) {
        cout << "Worker is doing chore number... " << count++ << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    
    // If the loop breaks, it means the pager beeped!
    cout << "Worker checked pager: Boss said stop! Shutting down safely." << endl;
}

int main() {
    cout << "Boss is hiring a smart jthread worker..." << endl;
    
    // We create a jthread. We don't even need to pass the pager manually, it happens automatically!
    jthread jt(interruptibleTask);
    
    // The boss waits for 1 second while the worker does chores.
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Boss: Okay, time to go home. Beeping the worker's pager!" << endl;
    
    // This sends the "Stop!" message to the worker's pager.
    jt.request_stop(); 
    
    // Notice we DON'T have to type jt.join() anywhere!
    // The jthread is smart enough to clean up after itself when the program ends.
    return 0;
}

/*
EXPECTED OUTPUT:
Boss is hiring a smart jthread worker...
Worker is doing chore number... 0
Worker is doing chore number... 1
Worker is doing chore number... 2
Worker is doing chore number... 3
Worker is doing chore number... 4
Boss: Okay, time to go home. Beeping the worker's pager!
Worker checked pager: Boss said stop! Shutting down safely.
*/
