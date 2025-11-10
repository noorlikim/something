#include <stdio.h>

int main() {
    int n, i;
    int pid[10], arrival[10], burst[10], completion[10], turnaround[10], waiting[10];
    int start_time, time;
    float ttat = 0, twt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
     {
        pid[i] = i + 1; 
    }

    printf("Enter Arrival Times:\n");
    for (i = 0; i < n; i++)
     {
        printf("P[%d] : ", pid[i]);
        scanf("%d", &arrival[i]);
    }

    printf("Enter Burst Times:\n");
    for (i = 0; i < n; i++)
     {
        printf("P[%d] : ", pid[i]);
        scanf("%d", &burst[i]);
    }

    
    start_time = arrival[0];
    for (i = 0; i < n; i++)
     {
        if (start_time < arrival[i])
            start_time = arrival[i];

        completion[i] = start_time + burst[i];
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
        start_time = completion[i];

        ttat += turnaround[i];
        twt += waiting[i];
    }


    printf("\nGantt Chart:\n");
    time = arrival[0];
    printf("%d", time);
    for (i = 0; i < n; i++)
     {
        if (time < arrival[i])
            time = arrival[i]; 
        printf(" --P%d-- %d", pid[i], time + burst[i]);
        time += burst[i];
    }

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) 
    {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\n", pid[i], arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", ttat / n);
    printf("\nAverage Waiting Time    = %.2f\n", twt / n);

    return 0;
}
