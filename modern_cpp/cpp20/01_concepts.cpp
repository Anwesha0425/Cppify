// 01_concepts.cpp
// Topic: C++20 Concepts (The Strict Bouncer!)
// To compile: g++ -std=c++20 01_concepts.cpp

#include <iostream>
#include <concepts> // The rulebook for the bouncer
#include <string>

using namespace std;

// Imagine a fancy club for Whole Numbers (Integers) ONLY.
// In the old days (Templates), anyone could sneak in, and the club would crash later.
// In C++20, we hire a Bouncer called a "Concept"! 

// The Bouncer checks your ID right at the door.
// 'std::integral' is the rule: "You must be a whole number!"
template <std::integral T> 
void onlyWholeNumbersAllowed(T number) {
    cout << "Welcome to the club, number " << number << "!" << endl;
}

// We can even write our own rules for the bouncer!
// Rule: You must be able to fly! (Meaning the type must have a fly() function)
template <typename T>
concept CanFly = requires(T thing) {
    thing.fly(); // If it doesn't have a fly() function, the bouncer says NO!
};

class Bird {
public:
    void fly() { cout << "Flap flap, I am flying!" << endl; }
};

class Dog {
public:
    void bark() { cout << "Woof!" << endl; }
};

// This function hires our custom Bouncer (CanFly)
template <CanFly T>
void launchIntoSky(T flyer) {
    cout << "Launching into the sky... ";
    flyer.fly();
}

int main() {
    cout << "--- The Integer Club ---" << endl;
    onlyWholeNumbersAllowed(42); // 42 is an int. The bouncer says OK!
    
    // onlyWholeNumbersAllowed(3.14); // ERROR! The bouncer stops the decimal before it even compiles!
    // onlyWholeNumbersAllowed("Hello"); // ERROR! Words are definitely not allowed!

    cout << "\n--- The Flying Club ---" << endl;
    Bird tweety;
    Dog buddy;
    
    launchIntoSky(tweety); // Tweety has a fly() function. The bouncer says OK!
    
    // launchIntoSky(buddy); // ERROR! Dogs can't fly! The bouncer stops this immediately!

    return 0;
}
/*
EXPECTED OUTPUT:
--- The Integer Club ---
Welcome to the club, number 42!

--- The Flying Club ---
Launching into the sky... Flap flap, I am flying!
*/
