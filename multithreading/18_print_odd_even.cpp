// 18_print_odd_even.cpp
// Topic: Print Odd and Even numbers (Two workers taking turns counting!)
// To compile: g++ -std=c++11 18_print_odd_even.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx; // Padlock
condition_variable cv; // Walkie-talkie
int currentNumber = 1; // The number we are counting

// Worker 1: Only likes ODD numbers (1, 3, 5...)
void printOdd(int max_val) {
    while (currentNumber < max_val) {
        unique_lock<mutex> lock(mtx);
        
        // Wait rule: "Is the number odd?" If it's even, go to sleep!
        cv.wait(lock, []() { return (currentNumber % 2 != 0); });
        
        cout << "Odd Worker says: " << currentNumber << endl;
        currentNumber++; // Add 1 (now it's an even number!)
        
        lock.unlock();
        cv.notify_all(); // Wake up the Even Worker!
    }
}

// Worker 2: Only likes EVEN numbers (2, 4, 6...)
void printEven(int max_val) {
    while (currentNumber <= max_val) {
        unique_lock<mutex> lock(mtx);
        
        // Wait rule: "Is the number even?" If it's odd, go to sleep!
        cv.wait(lock, []() { return (currentNumber % 2 == 0); });
        
        cout << "Even Worker says: " << currentNumber << endl;
        currentNumber++; // Add 1 (now it's an odd number!)
        
        lock.unlock();
        cv.notify_all(); // Wake up the Odd Worker!
    }
}

int main() {
    int max_val = 20; // Count up to 20
    
    thread t1(printOdd, max_val);
    thread t2(printEven, max_val);
    
    t1.join();
    t2.join();
    
    return 0;
}

/*
EXPECTED OUTPUT:
Odd Worker says: 1
Even Worker says: 2
Odd Worker says: 3
Even Worker says: 4
...
Even Worker says: 20
*/
