// 03_lambdas.cpp
// Topic: Lambda Expressions (Disposable Sticky Notes!)
// To compile: g++ -std=c++11 03_lambdas.cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // A Lambda is a quick, disposable function.
    // It's like writing instructions on a sticky note instead of writing a whole book!
    // Syntax: [what_to_grab_from_outside](inputs) -> output { instructions }
    
    // 1. A super simple sticky note
    auto sayHello = []() {
        cout << "Hello from the Sticky Note!" << endl;
    };
    sayHello(); // Read the sticky note!
    
    // 2. A sticky note that does math
    auto addMath = [](int a, int b) -> int {
        return a + b;
    };
    cout << "Math sticky note says 5 + 7 = " << addMath(5, 7) << endl;
    
    // 3. Capturing by Value [=]
    // The sticky note takes a PICTURE of the outside variable 'x'. 
    // It can't change the real 'x', it only sees the picture.
    int x = 10;
    auto readPicture = [x]() {
        cout << "Sticky note picture shows x is: " << x << endl;
    };
    readPicture();
    
    // 4. Capturing by Reference [&]
    // The sticky note takes a MAP (pointer/reference) to the outside variable 'y'.
    // Now it CAN change the real 'y'!
    int y = 20;
    auto changeRealY = [&y]() {
        y += 5; // We are changing the REAL y outside!
        cout << "Sticky note changed y to: " << y << endl;
    };
    changeRealY();
    cout << "Did y really change outside? Yes, y is now: " << y << endl;
    
    // 5. Sticky notes are great for quick rules!
    vector<int> numbers = {5, 2, 9, 1, 6};
    
    // Sort the numbers. The sticky note tells it the rule: "Put bigger numbers first!"
    sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b; 
    });
    
    cout << "Sorted numbers: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}
/*
EXPECTED OUTPUT:
Hello from the Sticky Note!
Math sticky note says 5 + 7 = 12
Sticky note picture shows x is: 10
Sticky note changed y to: 25
Did y really change outside? Yes, y is now: 25
Sorted numbers: 9 6 5 2 1 
*/
