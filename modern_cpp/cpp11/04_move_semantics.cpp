// 04_move_semantics.cpp
// Topic: Move Semantics (Stealing the backpack instead of copying it!)
// To compile: g++ -std=c++11 04_move_semantics.cpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Imagine you have a giant, heavy backpack full of 1,000 books.
// If you want to give it to your friend, normally the computer will COPY all 1,000 books 
// into a brand new backpack. That takes a long time!
// Move Semantics allows your friend to just STEAL the original backpack. It's super fast!

class Backpack {
private:
    string name;
public:
    // Normal Constructor
    Backpack(const string& s) : name(s) {
        cout << "Built a new backpack for: " << name << endl;
    }
    
    // Copy Constructor (The Slow Way!)
    // It creates a brand new backpack and copies everything.
    Backpack(const Backpack& other) : name(other.name) {
        cout << "COPYING the backpack (SLOW) for: " << name << endl;
    }
    
    // Move Constructor (The Fast Way!)
    // The '&&' means "This backpack is about to be thrown away, so you can steal its stuff!"
    // 'move' means stealing the data.
    Backpack(Backpack&& other) noexcept : name(move(other.name)) {
        cout << "STEALING the backpack (FAST) for: " << name << endl;
        // After stealing, 'other' is left empty.
    }
};

int main() {
    cout << "--- Creating a backpack ---" << endl;
    Backpack myBag("Giant Encyclopedia");
    
    cout << "\n--- Giving it to Friend 1 (Copying) ---" << endl;
    // We didn't use 'move', so the computer copies all the books. Slow!
    Backpack friend1Bag = myBag; 
    
    cout << "\n--- Giving it to Friend 2 (Moving/Stealing) ---" << endl;
    // We use std::move to say: "I don't need 'myBag' anymore! Friend 2, steal it!"
    Backpack friend2Bag = move(myBag); 
    
    return 0;
}
/*
EXPECTED OUTPUT:
--- Creating a backpack ---
Built a new backpack for: Giant Encyclopedia

--- Giving it to Friend 1 (Copying) ---
COPYING the backpack (SLOW) for: Giant Encyclopedia

--- Giving it to Friend 2 (Moving/Stealing) ---
STEALING the backpack (FAST) for: Giant Encyclopedia
*/
