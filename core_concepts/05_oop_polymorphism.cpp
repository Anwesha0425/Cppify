// 05_oop_polymorphism.cpp
// Topic: OOP - Polymorphism (The Universal Remote!)
// To compile: g++ -std=c++11 05_oop_polymorphism.cpp

#include <iostream>
#include <vector>

using namespace std;

// Pillar 4: Polymorphism. 
// "Poly" means many, "Morph" means forms.
// This means we can have one single button, but it does different things depending on who pushes it!
// Imagine a Universal Remote with a "Speak" button. 
// If you point it at a Dog, it barks. If you point it at a Cat, it meows!

// The Parent Class
class Animal {
public:
    // 'virtual' is the magic word for Polymorphism! 
    // It tells the computer: "Wait and see what kind of animal this REALLY is before speaking."
    virtual void speak() {
        cout << "... (silent)" << endl;
    }
};

class Dog : public Animal {
public:
    // 'override' just makes sure we spelled 'speak' correctly and didn't make a typo.
    void speak() override {
        cout << "WOOF! I am a dog." << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "MEOW! I am a cat." << endl;
    }
};

class Cow : public Animal {
public:
    void speak() override {
        cout << "MOO! I am a cow." << endl;
    }
};

int main() {
    Dog myDog;
    Cat myCat;
    Cow myCow;
    
    // Here is the true power of Polymorphism!
    // We can put all these different animals into ONE list of "Animal pointers".
    // (Remember: Pointers are just maps to the objects!)
    vector<Animal*> myZoo;
    myZoo.push_back(&myDog);
    myZoo.push_back(&myCat);
    myZoo.push_back(&myCow);
    
    cout << "Pressing the 'Speak' button on every animal in the zoo!" << endl;
    
    // We go through the list, and press the SAME "speak" button on everyone.
    // The computer is smart enough to know which animal is which!
    for (Animal* animalMap : myZoo) {
        animalMap->speak(); 
    }
    
    return 0;
}
/*
EXPECTED OUTPUT:
Pressing the 'Speak' button on every animal in the zoo!
WOOF! I am a dog.
MEOW! I am a cat.
MOO! I am a cow.
*/
