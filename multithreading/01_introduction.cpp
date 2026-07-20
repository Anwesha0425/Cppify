// 01_introduction.cpp
// Topic: Introduction to std::thread (How to make a "mini-worker")
// To compile: g++ -std=c++11 01_introduction.cpp -pthread

#include <iostream> // Brings in the toolbox for printing text to the screen (like cout).
#include <thread>   // Brings in the toolbox for making "threads" (mini-workers in our program).
#include <chrono>   // Brings in the toolbox for time (like a digital stopwatch).

// "using namespace std" is a shortcut so we don't have to type "std::" before standard words like cout.
using namespace std;

// This is a simple job we want our mini-worker (thread) to do.
// It takes a number called 'count' and counts down.
void runTask(int count) {
    while (count-- > 0) {
        cout << "Worker is running... " << count << endl;
        // chrono::seconds(1) means exactly 1 second.
        // sleep_for tells the worker to take a nap for that long!
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// "main" is the starting line where our program begins.
int main() {
    cout << "Main program (boss) started." << endl;

    // We create a new mini-worker (thread) named 't1'.
    // We tell it to do the 'runTask' job, and give it the number 5 to start with.
    thread t1(runTask, 5);
    
    // ".join()" is the boss saying: "I will wait right here until worker t1 is completely finished."
    t1.join();
    
    cout << "Main program (boss) finished." << endl;
    return 0;
}

/*
EXPECTED OUTPUT:
Main program (boss) started.
Worker is running... 4
Worker is running... 3
Worker is running... 2
Worker is running... 1
Worker is running... 0
Main program (boss) finished.
*/
