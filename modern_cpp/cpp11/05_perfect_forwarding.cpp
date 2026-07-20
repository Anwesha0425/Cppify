// 05_perfect_forwarding.cpp
// Topic: Perfect Forwarding (The Perfect Delivery Driver!)
// To compile: g++ -std=c++11 05_perfect_forwarding.cpp

#include <iostream>
#include <utility>

using namespace std;

// We have a machine that processes packages. 
// It has two different doors: one for sturdy boxes, and one for fragile glass.
class Factory {
public:
    // Door 1: Sturdy Boxes (lvalue reference)
    void process(int& x) {
        cout << "Processed Sturdy Box (lvalue): " << x << endl;
    }
    
    // Door 2: Fragile Glass (rvalue reference '&&')
    void process(int&& x) {
        cout << "Processed Fragile Glass (rvalue): " << x << endl;
    }
};

// This is our Delivery Driver (the wrapper). 
// Their job is to take a package and hand it to the Factory.
// But if they are clumsy, they might accidentally turn Fragile Glass into a Sturdy Box!
template <typename T>
void deliveryDriver(T&& package) {
    // T&& here is a "Universal Reference". It means the driver can hold ANYTHING.
    // std::forward is the magic trick! It ensures the driver hands over the package 
    // EXACTLY the way they received it. If it was fragile, it stays fragile!
    Factory factory;
    factory.process(std::forward<T>(package));
}

int main() {
    int sturdyBox = 10;
    
    cout << "Giving driver a Sturdy Box: ";
    // sturdyBox is a regular variable (lvalue). The driver passes it perfectly!
    deliveryDriver(sturdyBox); 
    
    cout << "Giving driver Fragile Glass: ";
    // '20' is a temporary number (rvalue/fragile). The driver passes it perfectly!
    deliveryDriver(20); 
    
    cout << "Giving driver a moved box: ";
    // move() turns the sturdy box into fragile glass. The driver passes it perfectly!
    deliveryDriver(std::move(sturdyBox)); 

    return 0;
}
/*
EXPECTED OUTPUT:
Giving driver a Sturdy Box: Processed Sturdy Box (lvalue): 10
Giving driver Fragile Glass: Processed Fragile Glass (rvalue): 20
Giving driver a moved box: Processed Fragile Glass (rvalue): 10
*/
