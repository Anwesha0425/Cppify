#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

volatile bool is_running;
void task(){
    while(is_running){
        cout<<"task is running"<<endl;
    this_thread::sleep_for(seconds(2));
    }
}
int main(){
    is_running=true;
    thread th(&task);
    this_thread::sleep_for(seconds(1));
    is_running=false;
    th.join();
    cout<<"main func ends"<<endl;
    return 0;
}

/*
* SUMMARY:-
* here volatile is used to prevent the compiler from optimizing the loop
* when is_running is changed to false, the loop will terminate
* when the program ends, the thread will be terminated
* we can use volatile to prevent the compiler from optimizing the loop
*/

// output:-
// task is running
// main func ends