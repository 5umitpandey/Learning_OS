#include <iostream>
#include <unistd.h>

int main() {
    // Path to the executable you want to run
    const char* path = "/home/ubuntu/OS_Files/Lab_3/2"; // Change this to the actual path

    // Arguments for the executable (null-terminated array)
    char* args[] = {const_cast<char*>(path), nullptr};

    // Execute the program specified by 'path'
    execv(path, args);

    // If execv() fails, this line won't be reached
    std::cerr << "Error executing program\n";
    return 1;
}

