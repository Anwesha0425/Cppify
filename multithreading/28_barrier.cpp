// 28_barrier.cpp
// Topic: std::barrier (A magical gate that works over and over again!)
// To compile: g++ -std=c++20 28_barrier.cpp -pthread

#include <iostream>
#include <thread>
#include <barrier> // The reusable gate tool (C++20)
#include <vector>

using namespace std;

// A barrier is like a latch, BUT it is REUSABLE!
// Imagine a magical race track with multiple phases. 
// At the end of Phase 1, a gate drops down. It won't open until all 3 racers arrive!
// When it opens, they start Phase 2. At the end of Phase 2, the same gate drops down again!

// We can even tell the gate to do a special trick right when it opens.
auto open_gate_trick = []() noexcept {
    cout << "--- DING DING! Gate opens! Moving to next phase... ---" << endl;
};

// Create a barrier for 3 racers, and tell it to do the trick when it opens.
barrier race_gate(3, open_gate_trick);

void worker(int id) {
    cout << "Racer " << id << " is running Phase 1..." << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    
    // "arrive_and_wait" means: "I am at the gate! Now I will wait for the others."
    race_gate.arrive_and_wait();
    
    // Once the gate opens, everyone runs Phase 2!
    cout << "Racer " << id << " is running Phase 2..." << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    
    // We can reuse the EXACT SAME gate for the end of Phase 2!
    race_gate.arrive_and_wait();
    
    cout << "Racer " << id << " crossed the finish line!" << endl;
}

int main() {
    vector<thread> threads;
    // 3 racers start the race at the same time.
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(worker, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}

/*
EXPECTED OUTPUT:
Racer 1 is running Phase 1...
Racer 2 is running Phase 1...
Racer 3 is running Phase 1...
--- DING DING! Gate opens! Moving to next phase... ---
Racer 1 is running Phase 2...
Racer 2 is running Phase 2...
Racer 3 is running Phase 2...
--- DING DING! Gate opens! Moving to next phase... ---
Racer 1 crossed the finish line!
...
*/
