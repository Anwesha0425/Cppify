// 03_oop_abstraction.cpp
// Topic: OOP - Abstraction (The TV Remote!)
// To compile: g++ -std=c++11 03_oop_abstraction.cpp

#include <iostream>

using namespace std;

// Pillar 2: Abstraction.
// This means hiding all the complicated, messy details and only showing a simple interface.
// Think of a TV Remote. You press "Power" and the TV turns on. 
// You don't need to know how the lasers, electricity, or microchips inside work!

class TV {
private:
    // These are the complicated, messy wires inside the TV. (Hidden details)
    void connectToPowerGrid() { cout << "Connecting to power grid..." << endl; }
    void bootUpScreen() { cout << "Warming up pixels..." << endl; }
    void loadChannels() { cout << "Scanning for satellites..." << endl; }

public:
    // This is the simple button on the remote! (Simple interface)
    void pressPowerButton() {
        cout << "--- Power Button Pressed ---" << endl;
        // The simple button does all the complicated stuff for us automatically!
        connectToPowerGrid();
        bootUpScreen();
        loadChannels();
        cout << "TV is now ON! Enjoy your show." << endl;
    }
};

int main() {
    TV myLivingRoomTV;
    
    // We don't have to worry about power grids or satellites.
    // We just press the simple button! That is Abstraction!
    myLivingRoomTV.pressPowerButton();
    
    return 0;
}
/*
EXPECTED OUTPUT:
--- Power Button Pressed ---
Connecting to power grid...
Warming up pixels...
Scanning for satellites...
TV is now ON! Enjoy your show.
*/
