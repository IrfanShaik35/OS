#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void think(int id) {
    printf("Philosopher %d is thinking.\n", id);
    usleep(rand() % 500000);  // Think for a random amount of time
}

void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
    usleep(rand() % 500000);  // Eat for a random amount of time
}

void pick_up_forks(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    // Lock forks in a specific order to avoid deadlock
    if (id % 2 == 0) {
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);
    } else {
        pthread_mutex_lock(&forks[right]);
        pthread_mutex_lock(&forks[left]);
    }

    printf("Philosopher %d picked up forks %d and %d.\n", id, left, right);
}

void put_down_forks(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    pthread_mutex_unlock(&forks[left]);
    pthread_mutex_unlock(&forks[right]);

    printf("Philosopher %d put down forks %d and %d.\n", id, left, right);
}

void* philosopher(void* num) {
    int id = *((int*)num);
    free(num);

    while (1) {
        think(id);
        pick_up_forks(id);
        eat(id);
        put_down_forks(id);
    }

    return NULL;
}

int main() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}


OUTPUT

Philosopher 0 is eating.
Philosopher 2 picked up forks 2 and 3.
Philosopher 2 is eating.
Philosopher 3 put down forks 3 and 4.
Philosopher 3 is thinking.
Philosopher 2 put down forks 2 and 3.
Philosopher 2 is thinking.
Philosopher 0 put down forks 0 and 1.
Philosopher 0 is thinking.
Philosopher 4 picked up forks 4 and 0.
Philosopher 4 is eating.
Philosopher 1 picked up forks 1 and 2.
Philosopher 1 is eating.
