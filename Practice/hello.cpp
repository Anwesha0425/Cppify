#include <iostream>
#include <thread>

// #define int long long
using namespace std;

void hlo(){
    cout<<"hello\n";
}

void hllo(char const* msg,int nm){
    cout<<msg<<" "<<nm<<endl;
}

int main(){
 thread t1(&hlo);
 cout<<"hello from thread"<<endl;
 t1.join();

 thread t2(&hllo,"hello!!",5);
 t2.join();
 return 0;
}

// output:-
// hello from thread
// hello
// hello!! 5