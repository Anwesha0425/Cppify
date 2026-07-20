// 02_ranges.cpp
// Topic: C++20 Ranges (The Assembly Line Pipe!)
// To compile: g++ -std=c++20 02_ranges.cpp

#include <iostream>
#include <vector>
#include <ranges> // The pipes!

using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "Original numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << "\n" << endl;
    
    // Imagine an assembly line in a toy factory.
    // Instead of doing one step at a time to ALL toys, 
    // we use a Pipe '|' to send each toy through multiple machines at once!
    
    cout << "--- The Assembly Line ---" << endl;
    cout << "Rule: Only keep EVEN numbers, then MULTIPLY by 10." << endl;
    
    // The Pipe '|' connects the machines together!
    // Machine 1: std::views::filter (The Security Guard - only lets even numbers pass)
    // Machine 2: std::views::transform (The Painter - multiplies them by 10)
    
    auto assemblyLine = numbers 
                      | std::views::filter([](int n) { return n % 2 == 0; }) 
                      | std::views::transform([](int n) { return n * 10; });

    // The toys don't actually go through the machine until we ask for them! (Lazy evaluation)
    for (int toy : assemblyLine) {
        cout << toy << " ";
    }
    cout << endl;

    return 0;
}
/*
EXPECTED OUTPUT:
Original numbers: 1 2 3 4 5 6 7 8 9 10 

--- The Assembly Line ---
Rule: Only keep EVEN numbers, then MULTIPLY by 10.
20 40 60 80 100 
*/
