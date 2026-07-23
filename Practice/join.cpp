#include <iostream>
#include <thread>

using namespace std;

void task(){
    // heavy task which will take a little time
    for (int i = 0; i < 2000000000; ++i);
    cout << "Done!" << endl;
}

int main(){
    thread th(&task);
    th.join();
    cout<<"hola!!"<<endl;
    return 0;
}

/*
* SUMMARY:
* 
* "join" is like a promise: 
The boss (main) says, "I will wait for this worker (th) to finish before I go home."
* 
* Output:-
* Done!
* hola!!
*/