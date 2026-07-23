#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;
using namespace chrono;
typedef system_clock sys;

void tsk(){
    cout<<"task is running"<<endl;
    this_thread::sleep_for(seconds(1));
    cout<<"task is finished"<<endl;
}
void dotask(string name){
    cout<<name<<" is sleeping..."<<endl;
    this_thread::sleep_for(seconds(2));
    cout<<name<<" is awake!!"<<endl;
}

void task(string name, sys::time_point tp){
    cout<<name<<" is sleeping..."<<endl;
    this_thread::sleep_until(tp);
    cout<<name<<" is awake!!"<<endl;
}

int main(){
    thread t1(&tsk);
    t1.join();

    thread t2(&dotask,"bob");
    thread t3(&dotask,"sam");

    t2.join();
    cout<<"disturb"<<endl;
    t3.join();


    sys::time_point now=sys::now();
    sys::time_point tp=now+seconds(3);
    sys::time_point tp1=tp+seconds(5);

    cout<<"kate will sleep until "<<tp<<endl;
    cout<<"alys will sleep until "<<tp1<<endl;

    thread t4(&task,"kate",tp);
    thread t5(&task,"alys",tp1);
    t4.join();
    t5.join();
    return 0;
}

/*

SUMMARY:
here we are passing the time_point to the task function,
it is very useful when we want to schedule a task to run at a specific time.
for example, we can use this to wake up the thread at a specific time.

sleep_for() is used for sleeping for a specific amount of time.

sleep_untill() is used for waking up a thread at a specific time point.
this is very useful in many real world scenarios like scheduling tasks, 
promising to wake up at a specific time, etc.
*/

// output:- 
// task is running
// task is finished
// sam is sleeping...
// bob is sleeping...
// sam is awake!!
// bob is awake!!
// disturb
// kate will sleep until 2026-07-22 14:07:03.028418191
// alys will sleep until 2026-07-22 14:07:08.028418191
// alys is sleeping...
// kate is sleeping...
// kate is awake!!
// alys is awake!!