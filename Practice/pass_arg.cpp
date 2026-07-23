#include <iostream>
#include <cstdio>
#include <thread>

using namespace std;
struct point{
    int x,y;
    point(int x,int y) : x(x),y(y){}
};
void exm(int a, double b, string c, char const* d, point e){
    char buf[50]={0};
    sprintf(buf,"%d %.1f %s %s (%d %d)",a,b,c.data(),d,e.x,e.y);
    cout<<buf<<endl;
}

void doTask(const string& msg) {
    cout << msg << endl;
}

int main(){
    thread t1(&exm,1,2,"red","blue",point(2,3));
    t1.join();
    thread t2(&exm,5,7,"green","black",point(6,6));
    t2.join();

    thread ta(&doTask, "Hello from C++");
    thread tb(&doTask, "Welcome to Multithreading");
    
    ta.join();
    tb.join();

    string s1="foo",s2="baar";
    // we used ref() to pass the address of the string
    thread tc(&doTask,ref(s1));
    tc.join();
    thread td(&doTask,ref(s2));
    td.join();
    return 0;
}

/*
SUMMARY: Passing Arguments to Threads

1. The "Perfect Replica" Rule: std::thread makes a *copy* of the arguments when the thread starts.
2. String Copy: "red" becomes a NEW string inside the thread.
3. Pointer Copy: "blue" (a const char*) is copied.
4. Struct Copy: point(2,3) is copied.

* Why? If the main thread changed "red" to "purple" *after* starting t1 but *before* t1 used it, 
  t1 would still see the old "red" (because it has a copy).
  This prevents chaotic data races.
*/

// output:-
// 1 2.0 red blue (2 3)
// 5 7.0 green black (6 6)
// Hello from C++
// Welcome to Multithreading
// foo
// baar