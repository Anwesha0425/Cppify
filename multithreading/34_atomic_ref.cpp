// 34_atomic_ref.cpp
// Topic: std::atomic_ref (C++20) (Turning a normal thing into an unbreakable thing temporarily!)
// To compile: g++ -std=c++20 34_atomic_ref.cpp -pthread

#include <iostream>
#include <thread>
#include <atomic> // For unbreakable tools.
#include <vector>

using namespace std;

// Imagine a giant box of normal toys. Making ALL of them "unbreakable" (atomic) 
// would be too heavy and slow down the program.
// std::atomic_ref (from C++20) lets us pick up ONE normal toy, treat it as unbreakable 
// just for a moment, and put it back.

// This is our normal data. Nothing fancy here!
struct HeavyData {
    int counter1 = 0;
    int counter2 = 0;
};

// This is the job our workers will do. We pass them the normal data using "ref()" so they share the same one.
void update_data(HeavyData& data) {
    for (int i = 0; i < 10000; ++i) {
        // We use atomic_ref to say: "Treat data.counter1 as unbreakable right now!"
        atomic_ref<int> a_ref1(data.counter1);
        
        // fetch_add(1) safely adds 1 to the counter without anyone interrupting.
        a_ref1.fetch_add(1, memory_order_relaxed);
        
        // Now let's do the same for counter2.
        atomic_ref<int> a_ref2(data.counter2);
        a_ref2.fetch_add(1, memory_order_relaxed);
    }
}

int main() {
    HeavyData data; // Create our normal data
    
    // Create 10 workers
    vector<thread> threads;
    for (int i = 0; i < 10; ++i) {
        // ref(data) means "pass the actual data box, not a copy of it!"
        threads.push_back(thread(update_data, ref(data)));
    }
    
    // Wait for all 10 workers to finish
    for (auto& t : threads) {
        t.join();
    }
    
    // Since we used atomic_ref, we didn't lose any numbers even though multiple workers were adding at the same time!
    cout << "Final counter1 (expected 100000): " << data.counter1 << endl;
    cout << "Final counter2 (expected 100000): " << data.counter2 << endl;
    
    return 0;
}

/*
EXPECTED OUTPUT:
Final counter1 (expected 100000): 100000
Final counter2 (expected 100000): 100000
*/
