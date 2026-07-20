// 14_promise_and_future.cpp
// Topic: std::promise and std::future (Making a promise to deliver a package!)
// To compile: g++ -std=c++11 14_promise_and_future.cpp -pthread

#include <iostream>
#include <thread>
#include <chrono>
#include <future> // Brings in our Promise and Future tools

using namespace std;

// This worker takes a "Promise" box. It promises to put the final answer in this box later!
void findOdd(promise<long long int>&& oddSumPromise, long long int start, long long int end) {
    long long int oddSum = 0;
    // Add up all the odd numbers...
    for (long long int i = start; i <= end; ++i) {
        if (i % 2 != 0) {
            oddSum += i;
        }
    }
    // .set_value() means: "I finished the math! I'm putting the answer inside the Promise box now!"
    oddSumPromise.set_value(oddSum);
}

int main() {
    long long int start = 0, end = 1900000000; // A HUGE number!
    
    // 1. The boss creates an empty "Promise" box.
    promise<long long int> oddSum;
    
    // 2. The boss takes a "Future" ticket linked to the box. 
    // This ticket says: "I will use this to get the answer later."
    future<long long int> oddFuture = oddSum.get_future();
    
    cout << "Sending worker to do the hard math..." << endl;
    // The boss passes the empty box (using 'move') to the worker.
    thread t1(findOdd, move(oddSum), start, end);
    
    cout << "Boss is waiting for the result..." << endl;
    
    // .get() means: "I am using my ticket now! If the box is still empty, I will sleep here until the worker puts the answer inside."
    cout << "The answer is: " << oddFuture.get() << endl; 
    
    cout << "Done!" << endl;
    t1.join(); // Always wait for the worker to leave the building.
    
    return 0;
}

/*
EXPECTED OUTPUT:
Sending worker to do the hard math...
Boss is waiting for the result...
The answer is: 902500000000000000
Done!
*/
