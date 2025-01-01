#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

// Global shared variable
int shared_variable = 0;

// POSIX semaphores to control access to the critical section
sem_t sem;

void updateSharedVariable(const std::string& threadName, int updateValue) {
    for (int i = 0; i < 5; ++i) {
        sem_wait(&sem);  // Wait (P operation)

        // Critical section
        shared_variable += updateValue;
        cout << threadName << " updated shared variable to " << shared_variable << endl;

        sem_post(&sem);  // Signal (V operation)

        sleep(1);  // Simulate some work
    }
}

int main() {
    // Initialize the semaphore with a value of 1
    sem_init(&sem, 0, 1);

    // Create threads
    thread thread1(updateSharedVariable, "Thread 1", 1);
    thread thread2(updateSharedVariable, "Thread 2", -1);

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    // Destroy the semaphore
    sem_destroy(&sem);

    cout << "Final value of shared variable: " << shared_variable << endl;

    return 0;
}