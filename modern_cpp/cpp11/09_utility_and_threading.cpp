// 09_utility_and_threading.cpp
// Topics: std::tuple (The Combo Meal!), std::chrono (The Stopwatch)
// To compile: g++ -std=c++11 09_utility_and_threading.cpp

#include <iostream>
#include <chrono> // The Stopwatch
#include <tuple> // The Combo Meal
#include <string>

using namespace std;

// 1. std::tuple (The Combo Meal)
// Normally, a function can only return ONE thing (like just a burger).
// A 'tuple' lets us return a combo meal! (Burger, Fries, and a Drink!)
tuple<int, double, string> getComboMeal() {
    // We pack them all into one box using make_tuple
    return make_tuple(42, 3.14, "Delicious Burger");
}

int main() {
    cout << "--- The Combo Meal (std::tuple) ---" << endl;
    
    // We order the combo meal
    tuple<int, double, string> myMeal = getComboMeal();
    
    // We have to use "std::get<number>" to take things out of the box.
    // 0 is the burger, 1 is the fries, 2 is the drink!
    cout << "Item 0: " << get<0>(myMeal) << endl;
    cout << "Item 1: " << get<1>(myMeal) << endl;
    cout << "Item 2: " << get<2>(myMeal) << endl;


    cout << "\n--- The Stopwatch (std::chrono) ---" << endl;
    
    // 'chrono' is the ultimate stopwatch. 
    // We click the stopwatch to start!
    auto start = chrono::high_resolution_clock::now();
    
    // Let the computer do some busy work...
    cout << "Computer is doing jumping jacks..." << endl;
    for (int i = 0; i < 10000000; ++i) { 
        // Jumping jack!
    } 
    
    // We click the stopwatch to stop!
    auto end = chrono::high_resolution_clock::now();
    
    // We ask the stopwatch how many milliseconds passed.
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "It took the computer " << duration.count() << " milliseconds to finish!" << endl;

    return 0;
}
/*
EXPECTED OUTPUT:
--- The Combo Meal (std::tuple) ---
Item 0: 42
Item 1: 3.14
Item 2: Delicious Burger

--- The Stopwatch (std::chrono) ---
Computer is doing jumping jacks...
It took the computer 15 milliseconds to finish!
*/
