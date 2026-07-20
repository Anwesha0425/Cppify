// 01_raw_pointers.cpp
// Topic: Raw Pointers (Maps to Houses)
// To compile: g++ -std=c++11 01_raw_pointers.cpp

#include <iostream>

using namespace std;

int main() {
    // Imagine the computer's memory is a giant neighborhood.
    // Every variable is a person living in a house.
    
    int age = 10; // 'age' is a person. They live in a house and their value is 10.
    
    // '&' means "Address of". It's like asking: "What is your house number?"
    cout << "The value of age is: " << age << endl;
    cout << "The house number (address) of age is: " << &age << endl;
    
    // A POINTER is just a piece of paper (a map) that has a house number written on it!
    // The '*' means "This is a map that points to an integer".
    int* mapToAge = &age; 
    
    cout << "\nOur map (pointer) says the house number is: " << mapToAge << endl;
    
    // If we want to visit the house and see who lives there, we use '*' again!
    // This is called "Dereferencing". It means "Go to the address on this map".
    cout << "Going to the house on the map... We found the value: " << *mapToAge << endl;
    
    // We can even change the value inside the house using our map!
    *mapToAge = 11; // "Go to the house and change the person's age to 11"
    
    cout << "\nAfter using the map to change the age..." << endl;
    cout << "The new value of age is: " << age << endl;
    
    return 0;
}
/*
EXPECTED OUTPUT:
(The house numbers will look like weird math, e.g., 0x7ffee...)
The value of age is: 10
The house number (address) of age is: 0x...

Our map (pointer) says the house number is: 0x...
Going to the house on the map... We found the value: 10

After using the map to change the age...
The new value of age is: 11
*/
