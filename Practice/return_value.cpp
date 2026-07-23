#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

void doublevalue(int arg,int* res){
    (*res)=2*arg;
}

void squarevalue(int arg,int & res){
    res=arg*arg;
}

int main(){
    int result[3];
    thread th1(&doublevalue,5,&result[1]);
    thread th2(&squarevalue,8,&result[2]);
    thread th3(&squarevalue,7,ref(result[0]));

    th1.join();
    th2.join();
    th3.join();
    cout<<result[1]<<" "<<result[2]<<" "<<result[0]<<endl;
    return 0;
}

// output:-
// 10 64 49