#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0, min_index;
    int pid[20], arrival[20], burst[20], remaining[20], completion[20], turnaround[20], waiting[20];
    float ttat = 0, twt = 0;

    
    int gantt_pid[200], gantt_time[200], g_index = 0;
    int prev = -1;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        completion[i] = 0;
    }

    printf("Enter Arrival Times:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d] : ", pid[i]);
        scanf("%d", &arrival[i]);
    }

    printf("Enter Burst Times:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d] : ", pid[i]);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
    }

   
    while (completed < n) {
        min_index = -1;
        int min_remaining = 99999;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && remaining[i] < min_remaining) {
                min_remaining = remaining[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            
            if (prev != -2) {
                gantt_pid[g_index] = 0; 
                gantt_time[g_index] = time;
                g_index++;
                prev = -2;
            }
            time++;
            continue;
        }

       
        if (prev != min_index) {
            gantt_pid[g_index] = pid[min_index];
            gantt_time[g_index] = time;
            g_index++;
            prev = min_index;
        }

        remaining[min_index]--;
        time++;

        if (remaining[min_index] == 0) {
            completed++;
            completion[min_index] = time;
        }
    }

    
    gantt_time[g_index] = time;

    
    for (i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
        ttat += turnaround[i];
        twt += waiting[i];
    }

    
    printf("\nGantt Chart:\n");
    for (i = 0; i < g_index; i++) {
        if (gantt_pid[i] == 0)
            printf("%d --IDLE-- ", gantt_time[i]);
        else
            printf("%d --P%d-- ", gantt_time[i], gantt_pid[i]);
    }
    printf("%d\n", gantt_time[g_index]);


    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\n", pid[i], arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", ttat / n);
    printf("\nAverage Waiting Time    = %.2f\n", twt / n);

    return 0;
}
