/*
RACE CONDITIONS
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace chrono;
using namespace std;

typedef system_clock sysclock;

void doTask(int index) {
    this_thread::sleep_for(seconds(1));
    cout << index;
}

int getResult(int N) {
    vector<bool> a;
    a.resize(N + 1, false);

    for (int i = 1; i <= N; ++i)
        if (0 == i % 2 || 0 == i % 3)
            a[i] = true;

    // result = sum of a (i.e. counting number of true values in a)
    int result = accumulate(a.begin(), a.end(), 0);
    return result;
}

void markDiv2(vector<bool> & a, int N) {
    for (int i = 2; i <= N; i += 2)
        a[i] = true;
}

void markDiv3(vector<bool> & a, int N) {
    for (int i = 3; i <= N; i += 3)
        a[i] = true;
}

int counter = 0;

void increaseCounter() {
    this_thread::sleep_for(seconds(1));
    for (int i = 0; i < 1000; ++i) {
        counter += 1;
    }
}


int cntr = 0;

void doTaskA(sysclock::time_point timePointWakeUp) {
    this_thread::sleep_until(timePointWakeUp);
    while (cntr < 10)++cntr;
    cout << "A won !!!" << endl;
}



void doTaskB(sysclock::time_point timePointWakeUp) {
    boost::this_thread::sleep_until(timePointWakeUp);

    while (counter > -10)
        --counter;

    cout << "B won !!!" << endl;
}


int main() {
    const int NUM_THREADS = 4;
    thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new thread(&doTask, i));
    }

    lstTh.join_all();

    cout << endl;


    const int N = 8;

    thread thDiv2(&markDiv2, ref(a), N);
    thread thDiv3(&markDiv3, ref(a), N);
    thDiv2.join();
    thDiv3.join();

    // result = sum of a (i.e. counting numbers of true values in a)
    int res = accumulate(a.begin(), a.end(), 0);

    int result = getResult(N);

    cout << "Number of integers that are divisible by 2 or 3 is: " << result<<" "<< res << endl;


    const int NUM_THREADS = 16;
    thread_group lstth;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstth.add_thread(new thread(&increaseCounter));
    }

    lstth.join_all();

    cout << "counter = " << counter << endl;


    sysclock::time_point tpNow = sysclock::now();
    sysclock::time_point tpWakeUp = tpNow + seconds(1);

    thread thA(&doTaskA, tpWakeUp);
    thread thB(&doTaskB, tpWakeUp);

    thA.join();
    thB.join();
    return 0;
}

/*
RACE CONDITIONS

SUMMARY:

1. A race condition occurs when multiple threads access and modify
   shared data simultaneously without proper synchronization.

2. Example 1:
   - Multiple threads execute doTask().
   - Each thread sleeps for 1 second and prints its index.
   - The order of printed indices is unpredictable because threads
     run concurrently.

3. Example 2:
   - markDiv2() marks numbers divisible by 2.
   - markDiv3() marks numbers divisible by 3.
   - Both threads modify the same vector<bool>.
   - Although the final result is often correct, concurrent writes
     to the same container are not guaranteed to be safe and may
     produce race conditions.

4. Example 3:
   - 16 threads execute increaseCounter().
   - Each thread increments the global variable counter 1000 times.
   - Expected value = 16000.
   - Actual value may be less than 16000 because multiple threads
     update counter simultaneously.
   - This demonstrates a classic race condition.

5. Example 4:
   - Thread A increases cntr until it reaches 10.
   - Thread B decreases counter until it reaches -10.
   - Both threads start at the same time.
   - The thread that completes first prints a winning message.
   - Execution order is nondeterministic.

6. Race conditions can be prevented using:
   - std::mutex
   - std::lock_guard
   - std::atomic
   - condition variables
   - other synchronization primitives

7. Key lesson:
   Concurrent access to shared variables without synchronization
   leads to undefined behavior and unpredictable results.
*/

/* output:-
0123

Number of integers that are divisible by 2 or 3 is: 5 5

counter = 14782

A won !!!
B won !!!

Another run may produce:

3102

Number of integers that are divisible by 2 or 3 is: 5 5

counter = 15931

B won !!!
A won !!!
*/


