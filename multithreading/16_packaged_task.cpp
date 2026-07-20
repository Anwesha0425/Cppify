// 16_packaged_task.cpp
// Topic: std::packaged_task (Wrapping a job in a box so we can mail it to a worker!)
// To compile: g++ -std=c++11 16_packaged_task.cpp -pthread

#include <iostream>
#include <future>
#include <thread>

using namespace std;

// This is a simple math job. It takes 1 second, then returns the answer.
int add(int x, int y) {
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Worker is doing the math..." << endl;
    return x + y;
}

int main() {
    // std::packaged_task is like a magical cardboard box. 
    // We put our "add" job inside the box.
    packaged_task<int(int, int)> taskBox(add);
    
    // Just like a Promise, the box gives us a "Future" ticket so we can get the answer later.
    future<int> result = taskBox.get_future();
    
    // Now we hire a worker (thread), and hand them the WHOLE box, plus the numbers 5 and 10.
    // 'move' means we are actually giving them the box, not just a picture of it.
    thread t1(move(taskBox), 5, 10);
    
    cout << "Boss is waiting for the result..." << endl;
    
    // We use our ticket to get the answer. The boss will sleep here until the worker is done.
    cout << "The answer is: " << result.get() << endl;
    
    t1.join(); // Always wait for the worker to finish up.
    
    return 0;
}

/*
EXPECTED OUTPUT:
Boss is waiting for the result...
Worker is doing the math...
The answer is: 15
*/
