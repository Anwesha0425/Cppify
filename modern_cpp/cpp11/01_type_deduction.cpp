// 01_type_deduction.cpp
// Topics: auto (The Smart Detective!)
// To compile: g++ -std=c++11 01_type_deduction.cpp

#include <iostream>
#include <vector>

using namespace std;

// The detective also works for functions! "decltype(a + b)" means:
// "Look at whatever (a + b) makes, and use that type for the answer."
auto add(int a, double b) -> decltype(a + b) {
    return a + b;
}

int main() {
    // 1. 'auto' is a Smart Detective.
    // Instead of telling the computer exactly what kind of box to use (int, double, string),
    // you let the detective look at the item and pick the perfect box automatically!
    
    auto i = 42;          // The detective sees a whole number -> picks 'int' box
    auto d = 42.5;        // The detective sees a decimal -> picks 'double' box
    auto s = "Hello";     // The detective sees words -> picks 'const char*' box
    
    cout << "i: " << i << ", d: " << d << ", s: " << s << endl;

    // 'auto' is SUPER helpful when the box name is really long and annoying to type.
    vector<int> myToys = {1, 2, 3};
    
    cout << "My toys: ";
    // Instead of typing "vector<int>::iterator", we just use "auto"!
    for (auto detective = myToys.begin(); detective != myToys.end(); ++detective) {
        cout << *detective << " ";
    }
    cout << endl;

    // 2. 'decltype' is a Copycat.
    // It looks at another variable and says "I want exactly the same box as that guy!"
    int x = 10;
    decltype(x) y = 20; // x is an int, so y becomes an int too!
    
    cout << "x: " << x << ", y: " << y << endl;
    
    // Testing the add function
    auto result = add(5, 3.2); // An int + a double = a double. So result is a double!
    cout << "Result of add: " << result << endl;

    return 0;
}
/*
EXPECTED OUTPUT:
i: 42, d: 42.5, s: Hello
My toys: 1 2 3 
x: 10, y: 20
Result of add: 8.2
*/
