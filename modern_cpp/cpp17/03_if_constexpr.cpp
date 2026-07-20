// 03_if_constexpr.cpp
// Topic: if constexpr (The Wizard who deletes code before it runs!)
// To compile: g++ -std=c++17 03_if_constexpr.cpp

#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

// Normally, an 'if' statement is checked while the program is running.
// If the computer gets to the 'if', it asks a question: "Is this true or false?"
// 
// 'if constexpr' is a magical Wizard that checks the question BEFORE the program is even built!
// Whichever path is false, the Wizard literally DELETES that code so the computer never even sees it.

template <typename T>
void printValue(T value) {
    // We use a type-checker to see if the value is an integer.
    // The wizard checks this BEFORE compiling!
    if constexpr (is_integral<T>::value) {
        cout << value << " is a whole number! I can do math on it: " << value * 2 << endl;
    } 
    else {
        // If 'value' is a string, the wizard DELETES the math part above.
        // If it didn't delete it, the program would crash trying to do math on words!
        cout << value << " is NOT a whole number. It's just words or decimals." << endl;
    }
}

int main() {
    cout << "Passing an integer (10):" << endl;
    printValue(10);
    
    cout << "\nPassing a string (\"Hello\"):" << endl;
    printValue(string("Hello"));

    return 0;
}
/*
EXPECTED OUTPUT:
Passing an integer (10):
10 is a whole number! I can do math on it: 20

Passing a string ("Hello"):
Hello is NOT a whole number. It's just words or decimals.
*/
