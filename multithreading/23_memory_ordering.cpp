// 23_memory_ordering.cpp
// Topic: Memory Ordering Basics (When the computer tries to be TOO smart!)
// To compile: g++ -std=c++11 23_memory_ordering.cpp -pthread

#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// Two unbreakable flags and a counter.
atomic<bool> x, y;
atomic<int> z;

void write_x() {
    // "memory_order_relaxed" means we tell the computer: 
    // "Just make sure this is unbreakable, but I don't care what order you do it in."
    x.store(true, memory_order_relaxed);
}

void write_y() {
    y.store(true, memory_order_relaxed);
}

void read_x_then_y() {
    // Wait until x is true
    while (!x.load(memory_order_relaxed));
    // If y is also true, add to z
    if (y.load(memory_order_relaxed)) {
        ++z;
    }
}

void read_y_then_x() {
    // Wait until y is true
    while (!y.load(memory_order_relaxed));
    // If x is also true, add to z
    if (x.load(memory_order_relaxed)) {
        ++z;
    }
}

int main() {
    // The computer's brain (CPU) is very tricky. To make things run faster, 
    // it sometimes re-arranges the order of our code behind our backs!
    x = false;
    y = false;
    z = 0;
    
    thread a(write_x);
    thread b(write_y);
    thread c(read_x_then_y);
    thread d(read_y_then_x);
    
    a.join();
    b.join();
    c.join();
    d.join();
    
    // Because we used "relaxed", the computer might have scrambled the order so badly 
    // that BOTH readers saw the first flag as true, but the second as false!
    // This is super advanced stuff. Normally, C++ uses "seq_cst" (Sequential Consistency), 
    // which forces the computer to play strictly by the rules and not scramble things.
    cout << "Value of z (Could be 0, 1, or 2 depending on the computer's mood!): " << z << endl;

    return 0;
}

/*
EXPECTED OUTPUT:
(Output will be 0, 1, or 2 randomly)
Value of z (Could be 0, 1, or 2 depending on the computer's mood!): 1
*/
