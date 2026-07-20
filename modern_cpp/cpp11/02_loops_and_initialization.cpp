// 02_loops_and_initialization.cpp
// Topics: Range-based For Loop (Handing out candy!) & Uniform Initialization
// To compile: g++ -std=c++11 02_loops_and_initialization.cpp

#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

class ToyBox {
private:
    vector<int> toys;
public:
    // This allows us to put toys in the box using curly braces {}
    ToyBox(initializer_list<int> list) {
        for (auto toy : list) {
            toys.push_back(toy);
        }
    }
    
    void showToys() {
        // Range-based for loop!
        // This is like saying: "For every single toy in the toys list, do this:"
        for (int toy : toys) {
            cout << toy << " ";
        }
        cout << endl;
    }
};

int main() {
    // 1. Uniform Initialization (The Curly Braces of Safety!)
    // Curly braces {} are a safe way to put things in boxes.
    // If you try to squeeze a giant toy (double) into a small box (int), it throws an error!
    int a{10};
    double b{3.14};
    // int c{3.14}; // ERROR! The computer will stop you from squishing the decimal!
    
    cout << "a: " << a << ", b: " << b << endl;

    // 2. Range-based For Loop with Arrays
    int candyLine[] = {1, 2, 3, 4, 5};
    
    cout << "Candy line before magic: ";
    for (int kid : candyLine) {
        cout << kid << " ";
    }
    cout << endl;
    
    // If we want to CHANGE the things in the list, we use '&' (Reference/Map).
    // This tells the computer: "Don't just look at the kid, actually give them double candy!"
    for (int& kid : candyLine) {
        kid *= 2; 
    }
    
    cout << "Candy line after magic: ";
    for (int kid : candyLine) {
        cout << kid << " ";
    }
    cout << endl;

    // 3. Using our ToyBox with curly braces!
    ToyBox myBox = {10, 20, 30, 40, 50}; 
    cout << "Toys in the box: ";
    myBox.showToys();

    return 0;
}
/*
EXPECTED OUTPUT:
a: 10, b: 3.14
Candy line before magic: 1 2 3 4 5 
Candy line after magic: 2 4 6 8 10 
Toys in the box: 10 20 30 40 50 
*/
