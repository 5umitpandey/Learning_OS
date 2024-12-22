#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>

const char* sharedMemoryName = "/mySharedMemory";
const char* semEmptyName = "/semEmpty";
const char* semFullName = "/semFull";
const char* semMutexName = "/semMutex";
const int bufferSize = 10;

struct SharedMemory {
    int buffer[bufferSize];
    int in, out;
};

void producer() {
    int shm_fd = shm_open(sharedMemoryName, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedMemory));
    SharedMemory* sharedMemory = (SharedMemory*)mmap(0, sizeof(SharedMemory), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t* semEmpty = sem_open(semEmptyName, O_CREAT, 0666, bufferSize);
    sem_t* semFull = sem_open(semFullName, O_CREAT, 0666, 0);
    sem_t* semMutex = sem_open(semMutexName, O_CREAT, 0666, 1);

    for (int i = 0; i < 20; ++i) {
        sem_wait(semEmpty);
        sem_wait(semMutex);

        sharedMemory->buffer[sharedMemory->in] = i;
        sharedMemory->in = (sharedMemory->in + 1) % bufferSize;
        std::cout << "Produced: " << i << std::endl;

        sem_post(semMutex);
        sem_post(semFull);

        sleep(1);
    }

    sem_close(semEmpty);
    sem_close(semFull);
    sem_close(semMutex);
    munmap(sharedMemory, sizeof(SharedMemory));
    close(shm_fd);
}

void consumer() {
    int shm_fd = shm_open(sharedMemoryName, O_RDONLY, 0666);
    SharedMemory* sharedMemory = (SharedMemory*)mmap(0, sizeof(SharedMemory), PROT_READ, MAP_SHARED, shm_fd, 0);

    sem_t* semEmpty = sem_open(semEmptyName, 0);
    sem_t* semFull = sem_open(semFullName, 0);
    sem_t* semMutex = sem_open(semMutexName, 0);

    for (int i = 0; i < 20; ++i) {
        sem_wait(semFull);
        sem_wait(semMutex);

        int item = sharedMemory->buffer[sharedMemory->out];
        sharedMemory->out = (sharedMemory->out + 1) % bufferSize;
        std::cout << "Consumed: " << item << std::endl;

        sem_post(semMutex);
        sem_post(semEmpty);

        sleep(2);
    }

    sem_close(semEmpty);
    sem_close(semFull);
    sem_close(semMutex);
    munmap(sharedMemory, sizeof(SharedMemory));
    close(shm_fd);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        producer();
    } else {
        sleep(1); // Ensure producer
    }
}
