/*
DEADLOCK
Version A
*/


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;



mutex mut;
mutex mutResourceA;
mutex mutResourceB;



void foo() {
    mutResourceA.lock();
    cout << "foo acquired resource A" << endl;

    this_thread::sleep_for(seconds(1));

    mutResourceB.lock();
    cout << "foo acquired resource B" << endl;
    mutResourceB.unlock();

    mutResourceA.unlock();
}



void bar() {
    mutResourceB.lock();
    cout << "bar acquired resource B" << endl;

    this_thread::sleep_for(seconds(1));

    mutResourceA.lock();
    cout << "bar acquired resource A" << endl;
    mutResourceA.unlock();

    mutResourceB.unlock();
}

void doTask(std::string name) {
    mut.lock();

    cout << name << " acquired resource" << endl;

    // mut.unlock(); // Forget this statement ==> deadlock
}



int main() {
    thread thFoo(&doTask, "foo");
    thread thBar(&doTask, "bar");

    thFoo.join();
    thBar.join();

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}

/*
SUMMARY:

1. A deadlock occurs when one or more threads wait indefinitely
   for a resource that will never become available.

2. In this example:

       mut.lock();
       cout << name << " acquired resource" << endl;
       // mut.unlock();   <-- forgotten

   The first thread acquires the mutex and never releases it.

3. When the second thread tries to acquire the same mutex,
   it becomes blocked forever.

4. Since one thread is permanently blocked:
   - join() never returns.
   - The program never reaches the final cout statement.
   - The application appears frozen.

5. Possible execution:

   Thread foo:
      lock mutex
      print message
      exit without unlock

   Thread bar:
      waits forever for mutex

6. This demonstrates a deadlock caused by forgetting to
   release a locked resource.

7. The functions foo() and bar() show another classic
   deadlock scenario:

      foo():
         lock Resource A
         lock Resource B

      bar():
         lock Resource B
         lock Resource A

   If both threads execute simultaneously:

      foo holds A and waits for B
      bar holds B and waits for A

   Neither thread can proceed, creating a circular wait.

8. Deadlock Conditions (Coffman Conditions):

   - Mutual Exclusion
     A resource can be owned by only one thread.

   - Hold and Wait
     A thread holds one resource while waiting for another.

   - No Preemption
     Resources cannot be forcibly taken away.

   - Circular Wait
     A cycle of threads waits for each other's resources.

   All four conditions must be present for a deadlock.

9. How to Prevent Deadlocks:

   A. Always unlock mutexes.
      Prefer lock_guard or unique_lock.

   B. Lock resources in a consistent order.

      Example:
      All threads lock A first, then B.

   C. Use std::lock():

      std::lock(mutResourceA, mutResourceB);

   D. Use scoped locking:

      std::scoped_lock lock(mutResourceA, mutResourceB);

   E. Minimize time spent holding locks.

10. Best Practice:

      lock_guard<mutex> lock(mut);

   automatically releases the mutex when leaving scope,
   preventing many deadlocks caused by forgotten unlock() calls.

11. Key Concept:

   Deadlock is a situation where threads wait forever for
   resources held by one another. Proper lock management,
   consistent lock ordering, and RAII-based locking
   (lock_guard, unique_lock, scoped_lock) are the primary
   techniques used to avoid deadlocks.
*/

/*
OUTPUT (one possible run):

foo acquired resource

Program hangs forever...

OR

bar acquired resource

Program hangs forever...
*/