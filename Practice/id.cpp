#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

void tsk(){
    this_thread::sleep_for(seconds(1));
    cout<<"tsk's id is "<<this_thread::get_id()<<endl;
}

int main(){
    thread t1(&tsk);
    cout<<"t1's id is "<<t1.get_id()<<endl;
    t1.join();
    return 0;
}

/*
* SUMMARY:-
* 
* get_id() is used to get the id of the thread.
* 
* output:-
* t1's id is 22791274936000
* tsk's id is 22791274936000
*/