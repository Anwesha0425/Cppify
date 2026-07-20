// 07_classes_and_enums.cpp
// Topics: nullptr, enum class, override, default/delete
// To compile: g++ -std=c++11 07_classes_and_enums.cpp

#include <iostream>

using namespace std;

// 1. Strongly Typed Enums (enum class)
// Old enums were messy. If you had 'Red' for an Apple and 'Red' for a Car, the computer got confused!
// 'enum class' puts them in strict gangs. "AppleColor::Red" and "CarColor::Red" never fight!
enum class AppleColor { Red, Green };
enum class CarColor { Red, Blue, Black };

// 2. Static Assert (A very strict teacher)
// "static_assert" checks things BEFORE the code even runs! 
// If it fails, the code refuses to build.
static_assert(sizeof(int) == 4, "Warning: The computer needs 4-byte integers!");

class BaseRobot {
public:
    BaseRobot(int parts) { cout << "Building Base Robot with " << parts << " parts." << endl; }
    
    virtual void speak() const { cout << "I am a robot." << endl; }
    
    // "final" means: "NOBODY is allowed to change this!"
    virtual void selfDestruct() final { cout << "BOOM!" << endl; }
};

class AdvancedRobot : public BaseRobot {
public:
    // 3. Inheriting Constructors
    // Instead of rewriting the BaseRobot constructor, we just steal it using 'using'!
    using BaseRobot::BaseRobot; 
    
    // 4. Delegating Constructors
    // If someone doesn't give us a parts number, we just call our OWN constructor with 100!
    AdvancedRobot() : AdvancedRobot(100) { 
        cout << "I used the default 100 parts!" << endl; 
    }

    // 5. Explicit Overrides (override)
    // "override" tells the computer: "Hey, make sure I didn't misspell 'speak'!"
    // If you type 'speek' by mistake, the computer yells at you!
    void speak() const override { cout << "I am an ADVANCED robot!" << endl; }
    
    // void selfDestruct() override {} // ERROR! The teacher marked this as 'final' in BaseRobot!

    // 6. Defaulted and Deleted Functions
    // "delete" means: "It is ILLEGAL to copy this robot!"
    AdvancedRobot(const AdvancedRobot&) = delete; 
    
    // "default" means: "Just do the normal assignment thing, I don't want to write it out."
    AdvancedRobot& operator=(const AdvancedRobot&) = default; 
};

// 7. nullptr (The Empty Map)
// Old C++ used 'NULL' (which is just the number 0). That was confusing!
// Modern C++ uses 'nullptr', which strictly means "This map points to nowhere."
void checkMap(int* map) {
    if (map == nullptr) { 
        cout << "This map is blank! (nullptr)" << endl;
    }
}

int main() {
    AppleColor myApple = AppleColor::Red;
    // int x = AppleColor::Red; // ERROR! The strict gang doesn't allow mixing with numbers!
    
    checkMap(nullptr);
    
    cout << "\nBuilding Robot 1:" << endl;
    AdvancedRobot r1;      // Uses the delegating constructor (100)
    
    cout << "\nBuilding Robot 2:" << endl;
    AdvancedRobot r2(50);  // Uses the inherited constructor
    
    r1.speak();
    
    // AdvancedRobot r3 = r1; // ERROR! Copying was deleted!

    return 0;
}
/*
EXPECTED OUTPUT:
This map is blank! (nullptr)

Building Robot 1:
Building Base Robot with 100 parts.
I used the default 100 parts!

Building Robot 2:
Building Base Robot with 50 parts.
I am an ADVANCED robot!
*/
