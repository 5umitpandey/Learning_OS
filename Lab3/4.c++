#include <iostream>
#include <unistd.h>
#include <fcntl.h> // For open() flags
#include <cstring> // For strerror()

int main() {
    const char* inputFilename = "/home/ubuntu/OS_Files/Lab_3/1.c++"; // Replace with your input file
    const char* outputFilename = "/home/ubuntu/OS_Files/Lab_3/1_.c++"; // Replace with your output file

    // Open the input file for reading
    int inputFileDescriptor = open(inputFilename, O_RDONLY);
    if (inputFileDescriptor == -1) {
        std::cerr << "Error opening " << inputFilename << ": " << strerror(errno) << std::endl;
        return 1;
    }

    // Open the output file for writing (create if not exists)
    int outputFileDescriptor = open(outputFilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFileDescriptor == -1) {
        std::cerr << "Error opening " << outputFilename << ": " << strerror(errno) << std::endl;
        close(inputFileDescriptor); // Close the input file descriptor
        return 1;
    }

    // Read from input file and write to output file
    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(inputFileDescriptor, buffer, sizeof(buffer))) > 0) {
        ssize_t bytesWritten = write(outputFileDescriptor, buffer, bytesRead);
        if (bytesWritten == -1) {
            std::cerr << "Error writing to " << outputFilename << ": " << strerror(errno) << std::endl;
            break;
        }
    }

    // Close both file descriptors
    close(inputFileDescriptor);
    close(outputFileDescriptor);

    std::cout << "Contents copied from " << inputFilename << " to " << outputFilename << std::endl;
    return 0;
}

