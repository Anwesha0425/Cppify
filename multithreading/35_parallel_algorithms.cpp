// 35_parallel_algorithms.cpp
// Topic: Parallel Algorithms (C++17) (Asking the computer to do the math using all its brains at once!)
// To compile (requires TBB on many systems): g++ -std=c++17 35_parallel_algorithms.cpp -ltbb

#include <iostream>
#include <vector>
#include <algorithm> // A toolbox full of helpful math and sorting tricks.
#include <execution> // C++17 toolbox that lets us say "Do this in parallel (using all CPU brains)!"
#include <chrono>    // Our super-accurate stopwatch.
#include <numeric>   // A toolbox for math with lists of numbers.

using namespace std;

int main() {
    // Create a giant list that can hold 10,000,000 (10 million) numbers!
    vector<int> data(10000000);
    
    // "iota" is a funny word, but it just means "fill the list starting from 1, then 2, then 3..."
    iota(data.begin(), data.end(), 1);

    // 1. Sequential Execution (Doing it the normal, slow way: one by one)
    // We click "Start" on our stopwatch...
    auto start = chrono::high_resolution_clock::now();
    
    // "reduce" adds all the numbers together. 
    // "execution::seq" means SEQUENTIAL (do it normally with just one worker).
    long long sum_seq = reduce(execution::seq, data.begin(), data.end(), 0LL);
    
    // Click "Stop" on the stopwatch!
    auto end = chrono::high_resolution_clock::now();
    cout << "Sequential (slow) sum: " << sum_seq << " in " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds.\n";

    // 2. Parallel Execution (Doing it the fast way: using all workers at once!)
    start = chrono::high_resolution_clock::now();
    
    // "execution::par" means PARALLEL. The computer automatically splits the 10 million numbers 
    // among all its CPU cores (brains) and adds them up super fast! No manual threads needed!
    long long sum_par = reduce(execution::par, data.begin(), data.end(), 0LL);
    
    end = chrono::high_resolution_clock::now();
    cout << "Parallel (fast) sum: " << sum_par << " in " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds.\n";

    // 3. Parallel and Unsequenced (Super-duper fast, if the computer supports it)
    start = chrono::high_resolution_clock::now();
    
    // "execution::par_unseq" means PARALLEL and UNSEQUENCED. It lets the computer use special 
    // tricks to process multiple numbers in a single swoop (called vectorization or SIMD).
    long long sum_par_unseq = reduce(execution::par_unseq, data.begin(), data.end(), 0LL);
    
    end = chrono::high_resolution_clock::now();
    cout << "Parallel Unsequenced (super fast) sum: " << sum_par_unseq << " in " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds.\n";

    return 0;
}

/*
EXPECTED OUTPUT:
(Times will vary depending on how fast your computer is, but Parallel should be much faster!)

Sequential (slow) sum: 50000005000000 in 15 milliseconds.
Parallel (fast) sum: 50000005000000 in 4 milliseconds.
Parallel Unsequenced (super fast) sum: 50000005000000 in 3 milliseconds.
*/
