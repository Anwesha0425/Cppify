// 27_latch.cpp
// Topic: std::latch (Waiting for everyone to arrive before the field trip starts!)
// To compile: g++ -std=c++20 27_latch.cpp -pthread

#include <iostream>
#include <thread>
#include <latch> // The field trip counter tool (C++20)
#include <vector>

using namespace std;

// A latch is like a teacher waiting for 3 specific students before starting a field trip.
// Once it counts down from 3 to 0, the trip starts!
// BUT, a latch can only be used ONCE. After the trip starts, you throw the latch away.
latch students_ready(3);

void do_work(int id) {
    cout << "Student " << id << " is getting their shoes on..." << endl;
    this_thread::sleep_for(chrono::milliseconds(500)); // Takes 0.5 seconds
    
    cout << "Student " << id << " is ready! Counting down the latch." << endl;
    
    // The student tells the teacher they are ready. The teacher crosses off one name.
    students_ready.count_down(); 
}

int main() {
    vector<thread> threads;
    
    // We have 3 students getting ready.
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(do_work, i);
    }
    
    cout << "Teacher (Main thread) is waiting for all 3 students to be ready..." << endl;
    
    // "wait()" means the teacher just stands there, blocking the door, 
    // until the latch counter hits 0.
    students_ready.wait(); 
    
    cout << "All students are ready! The field trip begins!" << endl;
    
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}

/*
EXPECTED OUTPUT:
Teacher (Main thread) is waiting for all 3 students to be ready...
Student 1 is getting their shoes on...
Student 2 is getting their shoes on...
Student 3 is getting their shoes on...
Student 1 is ready! Counting down the latch.
Student 2 is ready! Counting down the latch.
Student 3 is ready! Counting down the latch.
All students are ready! The field trip begins!
*/
