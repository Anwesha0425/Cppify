#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

mutex mtx;

int cnt=0;
void task(){
    this_thread::sleep_for(seconds(1));
    // lock_guard<mutex> lk(mtx);
    // unique_lock<mutex> uk(mtx);
    mtx.lock();
    for(int i=0;i<1000;i++)cnt++;
    mtx.unlock();
}

void doTask() {
    this_thread::sleep_for(seconds(1));

    if (false == mtx.try_lock()) {
        return;
    }

    for (int i = 0; i < 10000; ++i)
        ++cnt;

    mtx.unlock();
}

int main(){
    const int nm=16;
    thread_group thg;

    for(int i=0;i<nm;i++){
        thg.add_thread(new thread(&task));
    }
    thg.join_all();

    cout<<"counter == "<<cnt<<endl;
    return 0;
}

/*
SUMMARY:

1. A mutex (mutual exclusion object) is used to protect shared data
   from concurrent access by multiple threads.

2. The global variable `cnt` is shared among all threads.

3. The function `task()`:
   - Sleeps for 1 second.
   - Acquires the mutex.
   - Increments `cnt` 1000 times.
   - Releases the mutex.

4. Since only one thread can hold the mutex at a time,
   race conditions are prevented and all increments are counted correctly.

5. With:
      Number of threads = 16
      Increments per thread = 1000

   Expected result:
      16 × 1000 = 16000

6. The function `doTask()` demonstrates the use of `try_lock()`.
   - try_lock() attempts to acquire the mutex without blocking.
   - Returns true if the lock is acquired.
   - Returns false immediately if another thread already owns the mutex.
   - Useful when a thread should not wait for a lock.

7. Ways to lock a mutex:

   A. Manual Locking
      mtx.lock();
      // critical section
      mtx.unlock();

      Pros:
      - Simple and explicit.

      Cons:
      - Easy to forget unlock().
      - Unsafe if an exception occurs.

   B. lock_guard<mutex>
      lock_guard<mutex> lk(mtx);

      Features:
      - Automatically locks the mutex on creation.
      - Automatically unlocks when it goes out of scope.
      - Lightweight and efficient.
      - Cannot be manually unlocked and relocked.

      Best Use:
      - When a lock is needed for the entire scope.

   C. unique_lock<mutex>
      unique_lock<mutex> uk(mtx);

      Features:
      - Automatically locks and unlocks like lock_guard.
      - Can manually unlock() and lock() again.
      - Supports deferred locking.
      - Can transfer ownership (move semantics).
      - Required by condition_variable.

      Example:
      unique_lock<mutex> uk(mtx);
      // critical section
      uk.unlock();
      // non-critical work
      uk.lock();

      Best Use:
      - When flexible lock management is required.

8. Comparison:

   lock_guard
   ----------
   - Lightweight
   - Fastest option
   - Automatic lock/unlock
   - No manual unlock/relock
   - Preferred for simple critical sections

   unique_lock
   -----------
   - Slightly heavier
   - Automatic lock/unlock
   - Supports unlock()/lock()
   - Supports deferred locking
   - Works with condition variables
   - Preferred for advanced synchronization

9. Key Concept:
   A mutex ensures mutual exclusion, allowing only one thread
   at a time to execute a critical section. Using lock_guard
   or unique_lock is safer than manual lock()/unlock() because
   they automatically release the mutex and help prevent bugs.
*/

/*
OUTPUT:-
counter == 16000
*/


