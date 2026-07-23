#include <iostream>
#include <thread>
#include <string>

using namespace std;

class hello{
    public:
    void run(){
    thread t1(&hello::hlo,this,"from class");
    t1.join();
    }
   private:
   void hlo(string msg){
    cout<<msg<<endl;
   }
};

class Example{
    public:
    void operator()(string msge){
        cout<<msge<<endl;
    }
};

int main(){
    hello h;
    h.run();

    Example e;
    thread t2(e,"good day!");
    t2.join();
    return 0;
}

// output:-
// from class
// good day!



// #include <iostream>
// #include <thread>

// using namespace std;

// class hello{
//     public:
//     void run(){
//     thread t1(&hello::hlo,"from class");
//     t1.join();
//     }
//    private:
//    static void hlo(string msg){
//     cout<<msg<<endl;
//    }
// };

// int main(){
//     hello h;
//     h.run();
//     return 0;
// }

/*
 * SUMMARY: Threading with Class Member Functions
 * 
 * 1. Non-static Member Function (Method 1 & 3):
 *    - A normal member function is tied to a specific object instance (it has a hidden 'this' pointer).
 *    - When passing it to std::thread, you MUST provide the object instance it should run on.
 *    - From inside the class (Method 1), you pass `this`. 
 *    - From outside the class (Method 3), you pass the object's address (e.g., `&h`).
 *    - std::thread arguments: (Function Pointer, Object Pointer, Function Arguments...)
 * 
 * 2. Static Member Function (Method 2):
 *    - A static member function belongs to the class itself, NOT to a specific object. It has no 'this' pointer.
 *    - It behaves exactly like a normal global function.
 *    - Therefore, std::thread does NOT need an object pointer.
 *    - std::thread arguments: (Function Pointer, Function Arguments...)
 */

// output:-
// from class


// #include <iostream>
// #include <thread>

// using namespace std;

// class hello{
//    public:
//    void hlo(string msg){
//     cout<<msg<<endl;
//    }
// };

// int main(){
//     hello h;
//     thread t1(&hello::hlo,&h,"from class");
//     t1.join();
//     return 0;
// }

// output:-
// from class