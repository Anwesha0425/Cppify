// 24_thread_local.cpp
// Topic: thread_local (Giving everyone their own personal backpack!)
// To compile: g++ -std=c++11 24_thread_local.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

// Normally, a global variable is shared by EVERYONE.
// But "thread_local" means: "Make a BRAND NEW copy of this for every single worker!"
// It's like giving every worker their own personal backpack.
thread_local int personal_counter = 0;

void task(int id) {
    // They are only adding to their OWN backpack! Not sharing!
    personal_counter++; 
    
    // We only use the padlock here so their printing doesn't get jumbled on the screen.
    lock_guard<mutex> lock(mtx);
    cout << "Worker " << id << " says my personal counter is: " << personal_counter << endl;
}

int main() {
    // We create 3 workers. They all run the exact same job.
    thread t1(task, 1);
    thread t2(task, 2);
    thread t3(task, 3);
    
    t1.join();
    t2.join();
    t3.join();
    
    // If they were sharing, the counter would reach 3. 
    // But since they have their own backpacks, they all print 1!
    return 0;
}

/*
EXPECTED OUTPUT:
Worker 1 says my personal counter is: 1
Worker 2 says my personal counter is: 1
Worker 3 says my personal counter is: 1
*/
