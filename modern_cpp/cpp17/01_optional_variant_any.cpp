// 01_optional_variant_any.cpp
// Topic: std::optional, std::variant, std::any (The Magic Boxes!)
// To compile: g++ -std=c++17 01_optional_variant_any.cpp

#include <iostream>
#include <optional>
#include <variant>
#include <any>
#include <string>

using namespace std;

// 1. std::optional (The "Maybe" Box)
// Sometimes a function might not have an answer. 
// For example, "Find the toy in the toybox". What if it's not there?
// std::optional is a box that either has the toy, or is completely empty!
optional<string> findToy(bool isThere) {
    if (isThere) return "Action Figure";
    return nullopt; // nullopt means "The box is empty!"
}

int main() {
    cout << "--- std::optional ---" << endl;
    auto myBox = findToy(true);
    // You can check if the box has something inside using 'has_value()'
    if (myBox.has_value()) {
        // You use '*' or '.value()' to take the item out of the box
        cout << "I found: " << *myBox << endl;
    }
    
    auto emptyBox = findToy(false);
    // You can also give a backup item just in case the box is empty!
    cout << "I found: " << emptyBox.value_or("Nothing. So I bought a new toy!") << endl;


    cout << "\n--- std::variant ---" << endl;
    // 2. std::variant (The Shape-Shifter Box)
    // This box can hold exactly ONE of the listed types. 
    // It's like a slot machine: it can hold an int, OR a double, OR a string, but only one at a time.
    variant<int, double, string> shapeShifter;
    
    shapeShifter = 10; // Right now, it holds an int
    cout << "It holds an int: " << get<int>(shapeShifter) << endl;
    
    shapeShifter = "Hello"; // Now it shapeshifts into a string! The int is gone.
    cout << "Now it holds a string: " << get<string>(shapeShifter) << endl;
    // cout << get<int>(shapeShifter); // ERROR! The int is gone, so it will crash if you try this!


    cout << "\n--- std::any ---" << endl;
    // 3. std::any (The Magic Endless Bag)
    // This bag can hold LITERALLY ANYTHING. Int, double, string, object, array... anything!
    any magicBag = 42; 
    
    // You use 'any_cast' to pull things out. You MUST guess what type is inside!
    cout << "Bag has an int: " << any_cast<int>(magicBag) << endl;
    
    magicBag = string("Pizza"); // Now we throw a string in the bag!
    cout << "Bag has a string: " << any_cast<string>(magicBag) << endl;

    return 0;
}
/*
EXPECTED OUTPUT:
--- std::optional ---
I found: Action Figure
I found: Nothing. So I bought a new toy!

--- std::variant ---
It holds an int: 10
Now it holds a string: Hello

--- std::any ---
Bag has an int: 42
Bag has a string: Pizza
*/
