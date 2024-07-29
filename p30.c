#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Thread function that prints a message and its thread ID
void* thread_func(void* arg) {
    int id = *((int*)arg);
    printf("Thread %d is running. Thread ID: %lu\n", id, pthread_self());
    sleep(1);  // Simulate some work
    pthread_exit(NULL);  // Exit the thread
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    // (i) Create two threads
    if (pthread_create(&thread1, NULL, thread_func, &id1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, thread_func, &id2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // (ii) Join the first thread
    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread 1");
        return 1;
    }

    // (iii) Compare thread identifiers
    if (pthread_equal(thread1, thread2)) {
        printf("Thread 1 and Thread 2 are equal (same).\n");
    } else {
        printf("Thread 1 and Thread 2 are not equal (different).\n");
    }

    // (ii) Join the second thread
    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread 2");
        return 1;
    }

    printf("All threads completed.\n");
    return 0;
}

OUTPUT

Thread 1 is running. Thread ID: 1
Thread 2 is running. Thread ID: 2
Thread 1 and Thread 2 are not equal (different).
All threads completed.
