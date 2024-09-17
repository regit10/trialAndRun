#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

pthread_mutex_t mtx;
pthread_cond_t cond;
bool isOdd = true;
int count = 0;

void* printOdd(void* arg) {
    while (count < 100) {
        pthread_mutex_lock(&mtx);

        // Wait until it's the turn to print odd numbers
        while (!isOdd) {
            pthread_cond_wait(&cond, &mtx);
        }

        printf("%d\n", count);
        ++count;

        isOdd = false; // Switch to even numbers
        pthread_cond_signal(&cond); // Notify the even number thread

        pthread_mutex_unlock(&mtx);

        // Sleep for 1 second
        sleep(1);
    }
    pthread_exit(0);
}

void* printEven(void* arg) {
    while (count < 100) {
        pthread_mutex_lock(&mtx);

        // Wait until it's the turn to print even numbers
        while (isOdd) {
            pthread_cond_wait(&cond, &mtx);
        }

        printf("%d\n", count);
        ++count;

        isOdd = true; // Switch to odd numbers
        pthread_cond_signal(&cond); // Notify the odd number thread

        pthread_mutex_unlock(&mtx);

        // Sleep for 1 second
        sleep(1);
    }
    pthread_exit(0);
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mtx, NULL); // Initialize the mutex
    pthread_cond_init(&cond, NULL); // Initialize the condition variable

    // Create threads
    pthread_create(&t1, NULL, printOdd, NULL);
    pthread_create(&t2, NULL, printEven, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy mutex and condition variable
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);

    return 0;
}
