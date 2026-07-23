#include <iostream>
#include <thread>
#include <vector>

using namespace std;
typedef shared_ptr<thread> tptr;

void task(int index){
    cout<<"task "<<index<<" is running"<<endl;
}

int main(){
    // vector<thread> t;
    // for(int i=0;i<10;i++){
    //     t.push_back(thread(&task,i));
    // }
    // for(auto &i:t){
    //     i.join();
    // }

    const int nm=10;
    thread t[nm];
    for(int i=0;i<nm;i++){
        t[i]=thread(&task,i);
    }
    for(int i=0;i<nm;i++){
        t[i].join();
    }

    vector<tptr>lst;
    for(int i=0;i<nm;i++){
        tptr ptr=make_shared<thread>(&task,i);
        lst.push_back(ptr);
    }
    for(int i=0;i<nm;i++){
        lst[i]->join();
    }
    cout<<endl;


    thread_group tg;
    for(int i=0;i<nm;i++){
        tg.add_thread(new thread(&task,i));
        // tg.create_thread(&task,i);
    }
    tg.join_all();


    return 0;
}

/*
* SUMMARY:-
* 
* we can use a vector or an array to store the threads
* we can use a shared_ptr to store the threads
* make_shared is used to create a shared_ptr to a thread
* -> is used to access the member function of a shared_ptr
* add_thread is used to add a thread to the thread_group
* create_thread is used to create a thread and add it to the thread_group
* join_all is used to join all the threads in the thread_group
* 
* output:-
* task 0 is running
* task 1 is running
* task 2 is running
* task 3 is running
* task 4 is running
* task 5 is running
* task 6 is running
* task 7 is running
* task 8 is running
* task 9 is running


*/