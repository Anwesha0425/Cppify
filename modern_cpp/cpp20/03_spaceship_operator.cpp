// 03_spaceship_operator.cpp
// Topic: C++20 Spaceship Operator <=> (The Ultimate Scale!)
// To compile: g++ -std=c++20 03_spaceship_operator.cpp

#include <iostream>
#include <compare> // The scale toolbox

using namespace std;

// Imagine a giant scale that weighs two boxes.
// Normally, you have to ask: "Is A bigger?" "Is A smaller?" "Are they equal?" (3 different questions!)
// The Spaceship Operator <=> asks ALL of that at once!

class Player {
public:
    int score;
    
    Player(int s) : score(s) {}
    
    // The Magic Spaceship Operator!
    // By typing '= default', we tell the computer to automatically build the scale for us.
    // Now we can use <, >, <=, >=, ==, and != for free!
    auto operator<=>(const Player& other) const = default;
};

int main() {
    Player mario(100);
    Player luigi(80);
    
    cout << "--- The Ultimate Scale (<=>) ---" << endl;
    cout << "Mario's score: " << mario.score << endl;
    cout << "Luigi's score: " << luigi.score << endl;
    
    // We put them on the scale!
    if (mario > luigi) {
        cout << "Mario is winning!" << endl;
    } 
    else if (mario < luigi) {
        cout << "Luigi is winning!" << endl;
    } 
    else { // This means (mario == luigi)
        cout << "It's a tie!" << endl;
    }
    
    // The scale can also be used directly:
    auto result = (mario <=> luigi);
    
    if (result > 0) cout << "(The scale tipped towards Mario)" << endl;
    if (result < 0) cout << "(The scale tipped towards Luigi)" << endl;
    if (result == 0) cout << "(The scale is perfectly balanced)" << endl;

    return 0;
}
/*
EXPECTED OUTPUT:
--- The Ultimate Scale (<=>) ---
Mario's score: 100
Luigi's score: 80
Mario is winning!
(The scale tipped towards Mario)
*/
