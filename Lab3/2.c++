#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        std::cout << "Child process: Hello from child!" << std::endl;
        exit(42); // Terminate child with exit status 42
    } else if (child_pid > 0) {
        // Parent process
        int status;
        wait(&status); // Wait for the child process to terminate
        if (WIFEXITED(status)) {
            std::cout << "Parent process: Child exited with status " << WEXITSTATUS(status) << std::endl;
        }
    } else {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    return 0;
}
