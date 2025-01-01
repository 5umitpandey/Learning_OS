#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

// Shared variable
int VAR = 10;

// Semaphore names
#define SEM_CHILD "/sem_child"
#define SEM_PARENT "/sem_parent"

int main() {
    pid_t pid;

    // Initialize semaphores
    sem_t *sem_child = sem_open(SEM_CHILD, O_CREAT, 0644, 1); // Initially allow the child to run
    sem_t *sem_parent = sem_open(SEM_PARENT, O_CREAT, 0644, 0); // Initially block the parent

    if (sem_child == SEM_FAILED || sem_parent == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        for (int i = 0; i < 5; ++i) {
            sem_wait(sem_child); // Wait for the semaphore to be available
            VAR -= 2; // Decrement VAR by 2
            printf("Child process: VAR = %d\n", VAR);
            sem_post(sem_parent); // Signal the parent process to run
        }
        exit(0);
    } else {
        // Parent process
        for (int i = 0; i < 5; ++i) {
            sem_wait(sem_parent); // Wait for the semaphore to be available
            VAR += 2; // Increment VAR by 2
            printf("Parent process: VAR = %d\n", VAR);
            sem_post(sem_child); // Signal the child process to run
        }
        
        // Wait for the child process to complete
        wait(NULL);

        // Cleanup semaphores
        sem_close(sem_child);
        sem_close(sem_parent);
        sem_unlink(SEM_CHILD);
        sem_unlink(SEM_PARENT);
    }

    return 0;
}