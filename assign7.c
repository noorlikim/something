#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m;
int alloc[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int avail[MAX_RESOURCES];

bool safetyAlgorithm(int safeSeq[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = { false };

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            return false;
    }

    return true;
}

bool resourceRequestAlgorithm(int processID, int request[]) {
    for (int j = 0; j < m; j++) {
        if (request[j] > need[processID][j]) {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    for (int j = 0; j < m; j++) {
        if (request[j] > avail[j]) {
            printf("\nResources not available. Process must wait.\n");
            return false;
        }
    }

    // Try allocation
    for (int j = 0; j < m; j++) {
        avail[j] -= request[j];
        alloc[processID][j] += request[j];
        need[processID][j] -= request[j];
    }

    int safeSeq[MAX_PROCESSES];
    if (safetyAlgorithm(safeSeq)) {
        printf("\nRequest can be granted. System remains in a SAFE state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
        return true;
    } else {
        // Rollback
        for (int j = 0; j < m; j++) {
            avail[j] += request[j];
            alloc[processID][j] -= request[j];
            need[processID][j] += request[j];
        }
        printf("\nRequest cannot be granted. System would be in an UNSAFE state.\n");
        return false;
    }
}

int main() {
    printf("Enter the number of processes (<= %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter the number of resources (<= %d): ", MAX_RESOURCES);
    scanf("%d", &m);

    if (m <= 0 || m > MAX_RESOURCES) {
        printf("Invalid number of resources.\n");
        return 1;
    }

    printf("Enter the Allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the Maximum matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Print initial state
    printf("\nInitial System State:\n");
    printf("Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("\n");
    }

    printf("Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("Available Resources: ");
    for (int i = 0; i < m; i++)
        printf("%d ", avail[i]);
    printf("\n");

    int safeSeq[MAX_PROCESSES];
    if (safetyAlgorithm(safeSeq)) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state.\n");
        return 1;
    }

    // Resource Request Loop
    char choice;
    do {
        int processID;
        int request[MAX_RESOURCES];

        printf("\nEnter the process number making a request (0 to %d): ", n - 1);
        scanf("%d", &processID);

        if (processID < 0 || processID >= n) {
            printf("Invalid process ID.\n");
            continue;
        }

        printf("Enter request vector (size %d): ", m);
        for (int i = 0; i < m; i++)
            scanf("%d", &request[i]);

        resourceRequestAlgorithm(processID, request);

        printf("\nDo you want to make another request? (Y/N): ");
        scanf(" %c", &choice);
        choice = toupper(choice);

    } while (choice == 'Y');

    printf("Exiting program.\n");
    return 0;
}
