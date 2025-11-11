#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t mutex, wrt;
int sharedvar = 99;
int readercount = 0;

pthread_t writers[5], readers[5];

void reader() {
    sem_wait(&mutex);
    readercount++;
    if (readercount == 1) {
        sem_wait(&wrt);   // first reader locks writer
    }
    sem_post(&mutex);

    printf("\nReader is reading sharedvar = %d", sharedvar);
    sleep(1);
    printf("\nReader is done");

    sem_wait(&mutex);
    readercount--;
    if (readercount == 0) {
        sem_post(&wrt);   // last reader unlocks writer
    }
    sem_post(&mutex);
}

void writer() {
    printf("\nWriter is trying to enter");
    sem_wait(&wrt);
    printf("\nWriter has entered CS");
    sharedvar++;
    printf("\nWriter CHANGED THE VALUE OF SHARED VAR TO %d", sharedvar);
    sleep(1);
    sem_post(&wrt);
    printf("\nWriter is out of CS");
}

int main() {
    int n2, i;
    printf("Enter the number of readers & writers: ");
    scanf("%d", &n2);

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < n2; i++) {
        pthread_create(&writers[i], NULL, (void *)writer, NULL);
        pthread_create(&readers[i], NULL, (void *)reader, NULL);
    }

    for (i = 0; i < n2; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    return 0;
}
