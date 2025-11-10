#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#define MAX 25

int main() {
    int filedes[2];
    char string[MAX];
    char line[MAX];
    pid_t pid;

    printf("Enter the string to be given to the parent: ");
    fgets(string,MAX, stdin);

    if (pipe(filedes) < 0) {
        printf("Pipe creation error\n");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        printf("\nFork error");
        exit(1);
    }
    if (pid > 0) {
        close(filedes[0]);
        write(filedes[1], string, MAX);
    }
    if (pid == 0) {
        close(filedes[1]);
        read(filedes[0], line, MAX);
        line[MAX-1] = '\0';
        printf("Data read by child is: %s", line);
        exit(0);
    }
    return 0;
}

