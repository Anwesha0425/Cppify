// 02_oop_encapsulation.cpp
// Topic: OOP - Encapsulation (The Piggy Bank!)
// To compile: g++ -std=c++11 02_oop_encapsulation.cpp

#include <iostream>

using namespace std;

// OOP (Object-Oriented Programming) is a way to organize code into "Objects".
// Pillar 1: Encapsulation. 
// This means hiding the important stuff inside so people can't mess with it directly.
// Imagine a Piggy Bank. You can't just reach your hand inside and grab the money!
// You HAVE to use the coin slot (to put money in) or the hammer (to get it out).

class PiggyBank {
private:
    // PRIVATE: This is hidden! Nobody outside can touch this.
    // This is the actual money sitting safely inside the pig.
    int moneyInside; 

public:
    // PUBLIC: These are the buttons/slots anyone can use!
    PiggyBank() {
        moneyInside = 0; // Starts empty
    }

    // The Coin Slot! (This is called a "Setter")
    void putMoneyIn(int amount) {
        if (amount > 0) {
            moneyInside += amount;
            cout << "Clink! Added $" << amount << " to the piggy bank." << endl;
        } else {
            cout << "Hey! You can't put fake (negative) money in!" << endl;
        }
    }

    // Checking the balance (This is called a "Getter")
    int checkBalance() {
        return moneyInside;
    }
};

int main() {
    PiggyBank myBank;
    
    myBank.putMoneyIn(5);
    myBank.putMoneyIn(10);
    
    // myBank.moneyInside = 1000000; // ERROR! The money is private! We can't cheat!
    
    cout << "Total money saved: $" << myBank.checkBalance() << endl;
    
    return 0;
}
/*
EXPECTED OUTPUT:
Clink! Added $5 to the piggy bank.
Clink! Added $10 to the piggy bank.
Total money saved: $15
*/
