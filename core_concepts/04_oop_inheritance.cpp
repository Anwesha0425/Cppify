// 04_oop_inheritance.cpp
// Topic: OOP - Inheritance (Family Traits!)
// To compile: g++ -std=c++11 04_oop_inheritance.cpp

#include <iostream>
#include <string>

using namespace std;

// Pillar 3: Inheritance.
// This means a Child can inherit traits (variables and functions) from a Parent!
// If the Parent knows how to breathe, the Child automatically knows how to breathe too.
// This saves us from writing the same code over and over.

// The Parent Class (Base Class)
class Animal {
public:
    string name;
    
    void eat() {
        cout << name << " is eating food. Nom nom." << endl;
    }
    void sleep() {
        cout << name << " is sleeping. Zzz..." << endl;
    }
};

// The Child Class (Derived Class)
// "class Dog : public Animal" means: "A Dog IS AN Animal. It gets everything an Animal has!"
class Dog : public Animal {
public:
    // The Dog can do things that a normal Animal can't do!
    void bark() {
        cout << name << " says: WOOF WOOF!" << endl;
    }
};

// Another Child Class
class Cat : public Animal {
public:
    void meow() {
        cout << name << " says: MEOW!" << endl;
    }
};

int main() {
    Dog myDog;
    myDog.name = "Buddy";
    
    // Buddy inherited 'eat' and 'sleep' from the Animal parent!
    myDog.eat();
    myDog.sleep();
    
    // Buddy also has his own special Dog power!
    myDog.bark();
    
    cout << "-----------------" << endl;
    
    Cat myCat;
    myCat.name = "Whiskers";
    myCat.eat(); // Cat also inherited 'eat'!
    myCat.meow();
    
    return 0;
}
/*
EXPECTED OUTPUT:
Buddy is eating food. Nom nom.
Buddy is sleeping. Zzz...
Buddy says: WOOF WOOF!
-----------------
Whiskers is eating food. Nom nom.
Whiskers says: MEOW!
*/
