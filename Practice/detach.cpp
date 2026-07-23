#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

void task(){
    cout<<"foo is starting"<<endl;
    this_thread::sleep_for(seconds(2));
    cout<<"foo is finished"<<endl;
}

int main(){
    thread th(&task);
    th.detach();
    this_thread::sleep_for(seconds(3));
    cout<<"Main thread is exiting"<<endl;
    return 0;
}

/*
SUMMARY:
detach() is used to detach the thread from the main thread.
When the main thread exits, the detached thread will also be terminated.

Output:-
foo is starting
Main thread is exiting
*/
