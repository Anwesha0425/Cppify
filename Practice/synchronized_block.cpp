#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

mutex mtx;
int cnt=0;

void task(){
    this_thread::sleep_for(seconds(1));
    {
        // this is synchronized block
        unique_lock<mutex>ul(mtx);
        for(int i=0;i<1000;i++)cnt++;
    }
}

int main() {
    const int NUM_THREADS = 16;
    thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.create_thread(thread(&doTask));
    }

    lstTh.join_all();

    cout << "counter = " << counter << endl;
    // We are sure that counter = 16000

    return 0;
}

/*
SYNCHRONIZED BLOCKS

Synchronized blocks in C++ Boost threading are not supported by default.
To demonstate synchronized blocks, I use boost::unique_lock (or boost::lock_guard).

Now, let's see the code:
    {
        boost::unique_lock lk(mut);
        // Do something in the critical section
    }

The code block above is protected by a lock/mutex. That means it is synchronized on thread execution.
This code block is called "the synchronized block".
*/