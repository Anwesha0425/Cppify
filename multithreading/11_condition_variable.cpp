// 11_condition_variable.cpp
// Topic: std::condition_variable (A walkie-talkie for workers!)
// To compile: g++ -std=c++11 11_condition_variable.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> // Brings in our walkie-talkie!

using namespace std;

mutex mtx; // Our padlock
condition_variable cv; // Our walkie-talkie
long balance = 0; // Our bank account money

void addMoney(int money) {
    lock_guard<mutex> lock(mtx); // Lock the door
    balance += money;
    cout << "Added money! Current Balance: " << balance << endl;
    
    // notify_one() is like grabbing the walkie-talkie and yelling: 
    // "Hey, someone who is waiting! I just added money, you can wake up now!"
    cv.notify_one(); 
}

void withdrawMoney(int money) {
    unique_lock<mutex> lock(mtx); // Lock the door (unique_lock is needed for walkie-talkies!)
    
    // .wait() means: "I'm going to sleep until I get a message on the walkie-talkie AND my rule is true."
    // The rule here is: "Is the balance not zero?" 
    // While sleeping, the worker AUTOMATICALLY unlocks the door so others can come in and add money!
    // When they wake up, they automatically lock the door again.
    cv.wait(lock, [] { return (balance != 0); });
    
    if (balance >= money) {
        balance -= money;
        cout << "Deducted: " << money << endl;
    } else {
        cout << "Can't deduct that much! Balance is only " << balance << endl;
    }
    cout << "Final Balance Is: " << balance << endl;
}

int main() {
    // Worker 1 tries to withdraw 500, but they will fall asleep because balance is 0.
    thread t1(withdrawMoney, 500);
    
    // Boss takes a tiny nap to make sure Worker 1 is fast asleep.
    this_thread::sleep_for(chrono::seconds(1)); 
    
    // Worker 2 comes in and adds 500. Then they use the walkie-talkie to wake up Worker 1!
    thread t2(addMoney, 500);

    t1.join();
    t2.join();

    return 0;
}

/*
EXPECTED OUTPUT:
Added money! Current Balance: 500
Deducted: 500
Final Balance Is: 0
*/
