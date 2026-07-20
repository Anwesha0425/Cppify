// 08_variadic_templates.cpp
// Topic: Variadic Templates (The Magic Endless Bag!)
// To compile: g++ -std=c++11 08_variadic_templates.cpp

#include <iostream>

using namespace std;

// Imagine a Magic Endless Bag. You can put 1 toy, 5 toys, or 100 toys in it!
// Variadic Templates let us write ONE function that can take ANY number of arguments.

// 1. The Base Case (The Empty Bag)
// When there are no toys left in the bag, we just print a new line and stop.
void printAll() {
    cout << endl;
}

// 2. The Magic Bag (Takes 1 item out, and leaves the rest in the bag)
// 'T' is the first item we pull out. 'Args...' is the rest of the items still in the bag.
template <typename T, typename... Args>
void printAll(T first, Args... rest) {
    cout << first; // Look at the first item
    
    // If there are still items left in the bag, print a comma
    if (sizeof...(rest) > 0) {
        cout << ", ";
    }
    
    // Throw the rest of the bag back into the machine! (Recursion)
    printAll(rest...);
}

// Let's do another one: Adding up numbers from the bag!
template <typename T>
T sumBag(T singleItem) {
    return singleItem; // Base case: only 1 item left!
}

template <typename T, typename... Rest>
T sumBag(T first, Rest... rest) {
    // Add the first item to whatever the rest of the bag adds up to!
    return first + sumBag(rest...);
}

int main() {
    cout << "Emptying the magic bag: ";
    // We can put an int, a double, a string, a char, AND a boolean in the same bag!
    printAll(10, 3.14, "Hello", 'A', true);
    
    cout << "Adding up a bag of integers: " << sumBag(1, 2, 3, 4, 5) << endl;
    cout << "Adding up a bag of decimals: " << sumBag(1.1, 2.2, 3.3) << endl;

    return 0;
}
/*
EXPECTED OUTPUT:
Emptying the magic bag: 10, 3.14, Hello, A, 1
Adding up a bag of integers: 15
Adding up a bag of decimals: 6.6
*/
