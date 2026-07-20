// 20_shared_mutex.cpp
// Topic: std::shared_mutex (A library door: Many can read, only one can write!)
// To compile: g++ -std=c++17 20_shared_mutex.cpp -pthread

#include <iostream>
#include <thread>
#include <shared_mutex> // The special library padlock
#include <vector>

using namespace std;

// A shared_mutex is like the door to a library. 
// If people just want to READ books, we can let 100 people in at the same time!
// But if someone wants to PAINT the library (write), everyone else must leave first, and the painter locks the door alone.
shared_mutex smtx;
int libraryBook = 0; // The book everyone is reading or painting.

// Readers just look at the book.
void reader(int id) {
    for (int i = 0; i < 3; ++i) {
        // "shared_lock" means: "I just want to read. Let me in along with all the other readers!"
        shared_lock<shared_mutex> lock(smtx); 
        
        cout << "Reader " << id << " sees the book says: " << libraryBook << endl;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

// Writers want to change the book.
void writer(int id) {
    for (int i = 0; i < 3; ++i) {
        // "unique_lock" means: "I am painting! Kick everyone else out, and lock the door so nobody comes in until I'm done!"
        unique_lock<shared_mutex> lock(smtx);
        
        libraryBook++; // Changing the book
        cout << "--> Writer " << id << " changed the book to: " << libraryBook << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    // We have 3 Readers and 1 Writer.
    thread r1(reader, 1);
    thread r2(reader, 2);
    thread w1(writer, 1);
    thread r3(reader, 3);
    
    r1.join();
    r2.join();
    w1.join();
    r3.join();
    
    return 0;
}

/*
EXPECTED OUTPUT:
(Readers can read at the exact same time, but when the Writer is painting, nobody else can read!)
Reader 1 sees the book says: 0
Reader 2 sees the book says: 0
Reader 3 sees the book says: 0
--> Writer 1 changed the book to: 1
Reader 1 sees the book says: 1
...
*/
