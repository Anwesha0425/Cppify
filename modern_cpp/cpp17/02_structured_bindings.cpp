// 02_structured_bindings.cpp
// Topic: Structured Bindings (Unpacking a Combo Meal instantly!)
// To compile: g++ -std=c++17 02_structured_bindings.cpp

#include <iostream>
#include <tuple>
#include <string>
#include <map>

using namespace std;

// Remember std::tuple from C++11? The Combo Meal!
tuple<string, string, int> getHappyMeal() {
    return {"Cheeseburger", "Fries", 5};
}

int main() {
    cout << "--- C++11 Way (The Slow Way) ---" << endl;
    // In C++11, we had to grab the box, and then take things out one by one.
    tuple<string, string, int> box = getHappyMeal();
    string food = get<0>(box);
    string side = get<1>(box);
    int toyCount = get<2>(box);
    cout << "I got a " << food << ", " << side << ", and " << toyCount << " toys." << endl;


    cout << "\n--- C++17 Way (Structured Bindings - The Fast Way!) ---" << endl;
    // In C++17, we can unpack the box directly into variables IN ONE LINE!
    // The brackets [mainItem, sideItem, toys] instantly grab the 3 items from the box.
    auto [mainItem, sideItem, toys] = getHappyMeal();
    
    cout << "I got a " << mainItem << ", " << sideItem << ", and " << toys << " toys." << endl;
    
    
    cout << "\n--- Iterating through Maps easily ---" << endl;
    // Structured bindings are AMAZING for maps (dictionaries).
    map<string, int> scores = {{"Alice", 100}, {"Bob", 85}};
    
    // Instead of saying "player.first" and "player.second", we just unpack them!
    for (const auto& [name, score] : scores) {
        cout << name << " got a score of " << score << endl;
    }

    return 0;
}
/*
EXPECTED OUTPUT:
--- C++11 Way (The Slow Way) ---
I got a Cheeseburger, Fries, and 5 toys.

--- C++17 Way (Structured Bindings - The Fast Way!) ---
I got a Cheeseburger, Fries, and 5 toys.

--- Iterating through Maps easily ---
Alice got a score of 100
Bob got a score of 85
*/
