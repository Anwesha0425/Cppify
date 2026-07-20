// 29_false_sharing.cpp
// Topic: False Sharing (When two workers bump elbows because they sit too close!)
// To compile: g++ -std=c++11 29_false_sharing.cpp -pthread

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

// Imagine the computer's memory is a giant bookshelf.
// The computer likes to grab a whole SHELF (called a "cache line") of books at once.
// If Worker A wants Book A, and Worker B wants Book B, but they are on the SAME shelf...
// Every time Worker A touches their book, the computer pulls the whole shelf away from Worker B!
// This constant tug-of-war is called "False Sharing" and it makes the computer very slow.

// Scenario 1: False Sharing! 'a' and 'b' are right next to each other on the same shelf.
struct FalseSharingData {
    atomic<int> a{0};
    atomic<int> b{0};
};

// Scenario 2: No False Sharing! We put a bunch of empty space ("padding") between them.
// "alignas(64)" forces the computer to put them on totally DIFFERENT shelves (64 bytes apart).
struct PaddedData {
    alignas(64) atomic<int> a{0};
    alignas(64) atomic<int> b{0};
};

void work_a(atomic<int>& a) {
    for (int i = 0; i < 10000000; ++i) {
        a.fetch_add(1, memory_order_relaxed); // Worker A reads their book 10 million times
    }
}

void work_b(atomic<int>& b) {
    for (int i = 0; i < 10000000; ++i) {
        b.fetch_add(1, memory_order_relaxed); // Worker B reads their book 10 million times
    }
}

int main() {
    FalseSharingData crowded_desk;
    PaddedData spacious_desk;
    
    // Test 1: Crowded Desk (False Sharing)
    auto start = chrono::high_resolution_clock::now();
    thread t1(work_a, ref(crowded_desk.a));
    thread t2(work_b, ref(crowded_desk.b));
    t1.join();
    t2.join();
    auto end = chrono::high_resolution_clock::now();
    cout << "Time on a Crowded Desk (False Sharing): " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds.\n";
         
    // Test 2: Spacious Desk (Padded)
    start = chrono::high_resolution_clock::now();
    thread t3(work_a, ref(spacious_desk.a));
    thread t4(work_b, ref(spacious_desk.b));
    t3.join();
    t4.join();
    end = chrono::high_resolution_clock::now();
    cout << "Time on a Spacious Desk (Padded): " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds.\n";

    return 0;
}

/*
EXPECTED OUTPUT:
(The Padded version will be much, much faster because the workers aren't bumping elbows!)
Time on a Crowded Desk (False Sharing): 150 milliseconds.
Time on a Spacious Desk (Padded): 30 milliseconds.
*/
