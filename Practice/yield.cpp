#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

typedef microseconds us;
typedef steady_clock::time_point tmpt;

void littlesleep(int microsec) {
    tmpt tpstart = steady_clock::now();
    tmpt tpend = tpstart + us(microsec);

    do {
        this_thread::yield();
    } while (steady_clock::now() < tpend);
}

int main() {
    tmpt tpstartmeasure = steady_clock::now();

    littlesleep(130);

    us timeElapsed =
        duration_cast<us>(steady_clock::now() - tpstartmeasure);

    cout << "Elapsed time: "
         << timeElapsed.count()
         << " microseconds" << endl;

    return 0;
}

/*
* SUMMARY:-
* yield() is used to yield the CPU to another thread.
* It is a voluntary yielding of the CPU.
* It is a hint to the scheduler that the current thread is willing to give up the CPU.
* 
* Output:-
* Elapsed time: 131 microseconds
*/