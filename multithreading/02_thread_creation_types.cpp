// 02_thread_creation_types.cpp
// Topic: Types of Thread Creation (Different ways to give instructions to workers)
// To compile: g++ -std=c++11 02_thread_creation_types.cpp -pthread

#include <iostream> // For printing to the screen.
#include <thread>   // For creating mini-workers (threads).

using namespace std;

// Way 1: A normal, simple function.
void fun_ptr_task(int x) {
    cout << "1. Normal Function Worker: " << x << endl;
}

// Way 2: A "Lambda" function. It's like a quick, no-name sticky note with instructions.
// The "[]" means it's a lambda.
auto lambda_task = [](int x) {
    cout << "2. Lambda Worker: " << x << endl;
};

// Way 3: A "Functor" (Function Object). It's a whole class/blueprint pretending to be a function!
class FunctorTask {
public:
    // This special "operator()" lets us use this class like a normal function.
    void operator()(int x) {
        cout << "3. Functor Worker: " << x << endl;
    }
};

// Way 4 & 5: Functions that live inside a class (Member functions).
class Base {
public:
    // A regular member function (it needs a specific object to work).
    void member_task(int x) {
        cout << "4. Object Member Worker: " << x << endl;
    }
    
    // A "static" member function (it belongs to the class itself, not a specific object).
    static void static_member_task(int x) {
        cout << "5. Static Member Worker: " << x << endl;
    }
};

int main() {
    // Let's create workers using all 5 ways!
    
    // 1. Give the worker a normal function.
    thread t1(fun_ptr_task, 10);
    
    // 2. Give the worker the sticky-note (lambda) function.
    thread t2(lambda_task, 20);
    
    // 3. Give the worker a Functor object.
    thread t3(FunctorTask(), 30);
    
    // 4. Give the worker a member function. 
    // We also have to give it the actual object ('b') so it knows who it belongs to!
    Base b;
    thread t4(&Base::member_task, &b, 40); 
    
    // 5. Give the worker a static member function (no object needed).
    thread t5(&Base::static_member_task, 50);

    // Wait for all 5 workers to finish their jobs.
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}

/*
EXPECTED OUTPUT:
(The order might be jumbled because they are all running at the same time!)
1. Normal Function Worker: 10
2. Lambda Worker: 20
3. Functor Worker: 30
4. Object Member Worker: 40
5. Static Member Worker: 50
*/
