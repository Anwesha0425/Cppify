// 21_thread_pool.cpp
// Topic: Thread Pool (A team of workers waiting for jobs!)
// To compile: g++ -std=c++11 21_thread_pool.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue> // A line (queue) of jobs to do
#include <functional> // Allows us to store "jobs" as variables
#include <vector> // A list of our workers

using namespace std;

// A ThreadPool is like an office full of workers. 
// Instead of hiring and firing a new worker for every single tiny job (which is slow),
// we hire a group of workers ONCE. They sit around drinking coffee until a job comes in!
class ThreadPool {
private:
    vector<thread> workers; // Our team of workers
    queue<function<void()>> tasks; // The inbox tray full of jobs
    
    mutex queue_mutex; // Padlock for the inbox tray
    condition_variable condition; // Walkie-talkie to wake up workers
    bool stop; // A sign that says "The office is closing!"

public:
    // When we open the office, we decide how many workers to hire.
    ThreadPool(size_t threads) : stop(false) {
        for(size_t i = 0; i < threads; ++i) {
            // Tell each worker what their daily routine is:
            workers.emplace_back([this] {
                while(true) { // Keep doing this all day:
                    function<void()> task; // Get ready to hold a job
                    {
                        unique_lock<mutex> lock(this->queue_mutex); // Lock the inbox tray
                        
                        // Wait until either: The office is closing, OR there is a job in the inbox.
                        this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                        
                        // If the office is closing and there are no jobs left, go home!
                        if(this->stop && this->tasks.empty())
                            return;
                            
                        // Grab the top job from the inbox
                        task = move(this->tasks.front());
                        this->tasks.pop(); // Remove it from the inbox
                    } // Unlock the inbox tray so others can check it
                    
                    // Actually DO the job!
                    task(); 
                }
            });
        }
    }
    
    // This is how the Boss puts a new job into the inbox.
    void enqueue(function<void()> task) {
        {
            unique_lock<mutex> lock(queue_mutex); // Lock the inbox tray
            tasks.push(move(task)); // Put the new job in
        }
        condition.notify_one(); // Use walkie-talkie: "Hey, there's a new job in the inbox!"
    }
    
    // When the office shuts down (destruction)
    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queue_mutex);
            stop = true; // Turn on the "Office is closing" sign
        }
        condition.notify_all(); // Wake EVERYONE up so they see the sign and go home
        
        // Wait for every worker to officially leave the building
        for(thread &worker: workers) {
            worker.join();
        }
    }
};

int main() {
    // Open an office with exactly 4 workers!
    ThreadPool pool(4); 
    
    // We have 8 jobs to do.
    for(int i = 0; i < 8; ++i) {
        // Put the job in the inbox
        pool.enqueue([i] {
            cout << "Job " << i << " is being done by worker ID " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(200)); // The job takes 0.2 seconds
        });
    }
    
    // The Boss takes a nap while the workers do the 8 jobs.
    // Notice that since there are 8 jobs and only 4 workers, some workers will have to do 2 jobs each!
    this_thread::sleep_for(chrono::seconds(2));
    
    cout << "All done! Office closing." << endl;
    return 0;
}

/*
EXPECTED OUTPUT:
(You will see 4 jobs start, and when those finish, the other 4 will start using the same workers!)
Job 0 is being done by worker ID 2
Job 1 is being done by worker ID 3
Job 2 is being done by worker ID 4
Job 3 is being done by worker ID 5
(Wait a moment...)
Job 4 is being done by worker ID 2
Job 5 is being done by worker ID 3
...
*/
