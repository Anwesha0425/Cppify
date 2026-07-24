/*
EXECUTOR SERVICES AND THREAD POOLS
*/

#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include <boost/bind.hpp>

using namespace std;

void doTask() {
    cout << "Hello the Executor Service" << endl;
}

class MyFunctor {
public:
    void operator()() const {
        cout << "Hello Multithreading" << endl;
    }
};

void f(char id){
    cout<<"Task "<<id<<" is starting"<<endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout<<"Task "<<id<<" is finished"<<endl;
}

int main() {
    // Create a thread pool with 2 worker threads
    boost::asio::thread_pool pool(2);

    // Submit tasks
    boost::asio::post(pool, doTask);
    boost::asio::post(pool, MyFunctor());

    // Wait for all tasks to finish
    pool.join();


    const int numthread=2;
    const int numtask=5;

    boost::asio::thread_pool thpool(numthread);
    for(int i=0;i<numtask;i++){
        boost::asio::post(thpool,boost::bind(&f,'A'+i));
    }
    cout<<"All tasks are submitted"<<endl;
    thpool.join();
    cout<<"All tasks are completed"<<endl;
    thpool.stop();

    return 0;
}


/*
* SUMMARY: Thread Pools and Executor Services
* 
* - A Thread Pool creates a fixed number of threads in advance.
* - Instead of manually creating and destroying threads for every task (which is slow), 
*   we submit (or "post") tasks to the pool.
* - The threads in the pool wait for tasks in a queue, execute them, and then wait for the next task.
* - `boost::asio::thread_pool` provides this functionality.
* - `boost::asio::post` submits a task to the thread pool for execution.
* - `pool.join()` blocks the main thread until all submitted tasks have completed.
*/
// output:- (Note: Order may vary due to concurrency)
// Hello the Executor Service
// Hello Multithreading
// All tasks are submitted
// Task A is starting
// Task B is starting
// Task A is finished
// Task B is finished
// Task C is starting
// Task D is starting
// Task C is finished
// Task D is finished
// Task E is starting
// Task E is finished
// All tasks are completed
