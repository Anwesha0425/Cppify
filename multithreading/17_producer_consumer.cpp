// 17_producer_consumer.cpp
// Topic: Producer Consumer Problem (The Chef and the Hungry Customer!)
// To compile: g++ -std=c++11 17_producer_consumer.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue> // A line of items (like a conveyor belt)

using namespace std;

mutex mtx; // Our padlock for the kitchen door
condition_variable cv; // Our walkie-talkie
queue<int> foodBelt; // The conveyor belt for food
const unsigned int maxBeltSize = 10; // The belt can only hold 10 plates!

// The Producer is the Chef! They make food and put it on the belt.
void producer(int mealsToCook) {
    while (mealsToCook > 0) {
        unique_lock<mutex> lock(mtx);
        
        // Wait! Is the belt full? If it has 10 plates, the Chef must sleep!
        cv.wait(lock, []() { return foodBelt.size() < maxBeltSize; });
        
        foodBelt.push(mealsToCook); // Put a plate on the belt
        cout << "Chef cooked meal #" << mealsToCook << endl;
        mealsToCook--;
        
        lock.unlock(); // Unlock the kitchen door
        cv.notify_one(); // Yell on the walkie-talkie: "Food is ready!"
    }
}

// The Consumer is the Customer! They take food off the belt and eat it.
void consumer() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        
        // Wait! Is the belt empty? If there is no food, the Customer must sleep!
        cv.wait(lock, []() { return foodBelt.size() > 0; });
        
        int meal = foodBelt.front(); // Look at the first plate
        foodBelt.pop(); // Take it off the belt
        cout << "Customer ate meal #" << meal << endl;
        
        lock.unlock(); // Unlock the kitchen door
        cv.notify_one(); // Yell on the walkie-talkie: "I made space on the belt!"
        
        if (meal == 1) break; // If we ate meal #1 (the last one), we are full and go home!
    }
}

int main() {
    // Hire a Chef to cook 20 meals, and a Customer to eat them.
    thread t1(producer, 20);
    thread t2(consumer);
    
    t1.join();
    t2.join();
    
    return 0;
}

/*
EXPECTED OUTPUT:
(The Chef will cook up to 10 meals, then the Customer will eat some, taking turns!)
Chef cooked meal #20
Chef cooked meal #19
...
Customer ate meal #20
Customer ate meal #19
...
*/
