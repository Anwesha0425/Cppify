// 06_smart_pointers.cpp
// Topic: Smart Pointers (The toys that clean themselves up!)
// To compile: g++ -std=c++11 06_smart_pointers.cpp

#include <iostream>
#include <memory> // The magic toolbox for Smart Pointers

using namespace std;

class Toy {
public:
    Toy() { cout << "Toy is taken out of the box!" << endl; }
    ~Toy() { cout << "Toy is put back in the box (Destroyed)!" << endl; }
    void play() { cout << "Playing with the toy!" << endl; }
};

int main() {
    cout << "--- unique_ptr (The Only Child) ---" << endl;
    {
        // 1. std::unique_ptr 
        // This is like an Only Child. They DO NOT share their toys!
        unique_ptr<Toy> onlyChildToy(new Toy());
        onlyChildToy->play();
        
        // unique_ptr<Toy> friendToy = onlyChildToy; // ERROR! The only child refuses to share!
        
        // But the only child CAN give the toy away completely using move()
        unique_ptr<Toy> newOwner = move(onlyChildToy); 
        
        if (!onlyChildToy) cout << "The only child has no toy anymore." << endl;
    } // When the owner goes home (out of scope), they AUTOMATICALLY put the toy away!
    
    cout << "\n--- shared_ptr (Sharing is Caring) ---" << endl;
    {
        // 2. std::shared_ptr
        // This is a group of friends who share a toy. 
        // The toy keeps a "count" of how many friends are looking at it.
        shared_ptr<Toy> friend1 = make_shared<Toy>();
        cout << "Friends looking at toy: " << friend1.use_count() << endl; // 1
        
        {
            shared_ptr<Toy> friend2 = friend1; // Sharing is allowed!
            cout << "Friends looking at toy: " << friend1.use_count() << endl; // 2
        } // Friend 2 goes home. The count goes down!
        
        cout << "Friends looking at toy: " << friend1.use_count() << endl; // 1
    } // Friend 1 goes home. The count hits 0, so the toy puts ITSELF away!

    cout << "\n--- weak_ptr (The Window Shopper) ---" << endl;
    {
        // 3. std::weak_ptr
        // This person just looks at the toy through a window. 
        // They don't officially "own" it, so they don't increase the count.
        shared_ptr<Toy> owner = make_shared<Toy>();
        weak_ptr<Toy> windowShopper = owner;
        
        cout << "Official owners: " << owner.use_count() << endl; // Still 1!
        
        // If the window shopper actually wants to play with it, they must ask nicely (lock)
        if (shared_ptr<Toy> temporaryOwner = windowShopper.lock()) {
            cout << "The toy is still there! I can play with it!" << endl;
            temporaryOwner->play();
        }
    }

    return 0;
}
/*
EXPECTED OUTPUT:
--- unique_ptr (The Only Child) ---
Toy is taken out of the box!
Playing with the toy!
The only child has no toy anymore.
Toy is put back in the box (Destroyed)!

--- shared_ptr (Sharing is Caring) ---
Toy is taken out of the box!
Friends looking at toy: 1
Friends looking at toy: 2
Friends looking at toy: 1
Toy is put back in the box (Destroyed)!

--- weak_ptr (The Window Shopper) ---
Toy is taken out of the box!
Official owners: 1
The toy is still there! I can play with it!
Playing with the toy!
Toy is put back in the box (Destroyed)!
*/
