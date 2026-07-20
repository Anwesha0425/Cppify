// 15_async.cpp
// Topic: std::async (Hiring a worker the easy way!)
// To compile: g++ -std=c++11 15_async.cpp -pthread

#include <iostream>
#include <future> // We need this for async
#include <chrono>

using namespace std;

// This is just a normal function that returns a number. No messy "Promises" or "locks" needed!
long long int findOdd(long long int start, long long int end) {
    cout << "Worker (ID: " << this_thread::get_id() << ") is doing the math!" << endl;
    long long int oddSum = 0;
    for (long long int i = start; i <= end; ++i) {
        if (i % 2 != 0) {
            oddSum += i;
        }
    }
    return oddSum; // Just return the answer normally!
}

int main() {
    cout << "Boss (ID: " << this_thread::get_id() << ") has started." << endl;
    long long int start = 0, end = 1900000000;
    
    // std::async is a super-easy way to hire a worker! 
    // "launch::async" tells it: "Hire a new worker and start right NOW!"
    // It automatically gives us a "Future" ticket so we can get the answer later.
    future<long long int> oddFuture = async(launch::async, findOdd, start, end);
    
    cout << "Boss is waiting for the result..." << endl;
    
    // .get() pauses the boss until the worker finishes the math and hands over the answer.
    cout << "The answer is: " << oddFuture.get() << endl; 
    cout << "Done!!" << endl;
    
    return 0;
}

/*
EXPECTED OUTPUT:
Boss (ID: 1) has started.
Boss is waiting for the result...
Worker (ID: 2) is doing the math!
The answer is: 902500000000000000
Done!!
*/
