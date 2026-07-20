// 26_semaphore.cpp
// Topic: std::counting_semaphore (A bouncer at a club!)
// To compile: g++ -std=c++20 26_semaphore.cpp -pthread

#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore> // The bouncer tool! (C++20)
#include <vector>

using namespace std;

// Imagine a small club that only allows 3 people inside at the exact same time.
// A counting_semaphore is the bouncer! We tell the bouncer: "Max 3 people!"
counting_semaphore<3> bouncer(3); 

void worker(int id) {
    // "acquire" means a worker walks up to the bouncer and asks to go in.
    // If there are already 3 people inside, the bouncer makes them wait outside in line.
    // If there is room, the bouncer lets them in!
    bouncer.acquire(); 
    
    cout << "Worker " << id << " got into the club!" << endl;
    
    // They party in the club for 1 second...
    this_thread::sleep_for(chrono::seconds(1)); 
    
    cout << "Worker " << id << " is leaving the club." << endl;
    
    // "release" means the worker walks out. 
    // The bouncer sees they left, and lets the next person in line enter!
    bouncer.release(); 
}

int main() {
    vector<thread> threads;
    
    // We create 5 workers who ALL want to go to the club at the exact same time.
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(worker, i + 1);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}

/*
EXPECTED OUTPUT:
(3 workers will get in immediately. The other 2 have to wait until someone leaves!)
Worker 1 got into the club!
Worker 2 got into the club!
Worker 3 got into the club!
(Wait 1 second...)
Worker 1 is leaving the club.
Worker 4 got into the club!
...
*/
