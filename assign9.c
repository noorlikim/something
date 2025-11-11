#include <stdio.h>

int inqueue(int queue[], int size, int page) {
    for (int i = 0; i < size; i++) {
        if (queue[i] == page)
            return 1;
    }
    return 0;
}

int main() {
    int frame, fcount;

    printf("Enter the number of frames: ");
    scanf("%d", &frame);

    printf("Enter the number of pages: ");
    scanf("%d", &fcount);

    int page[fcount];
    printf("Enter the page reference string: ");
    for (int i = 0; i < fcount; i++) 
    {
        scanf("%d", &page[i]);
    }

    int queue[frame];
  int recent[frame];
    int count = 0, time = 0, pagefault = 0;

    
    for (int i = 0; i < frame; i++) {
        queue[i] = -1;
        recent[i] = 0;
    }

    printf("\nLRU Page Replacement Process \n");

    for (int i = 0; i < fcount; i++) {
        int current = page[i];
        printf("Current Page: %d => ", current);
        time++;  

        
        int hit = 0;
        for (int j = 0; j < count; j++) {
            if (queue[j] == current) {
                hit = 1;
                recent[j] = time; 
                break;
            }
        }

        if (hit) {
            
            for (int k = 0; k < frame; k++) {
                if (queue[k] != -1)
                    printf("%d ", queue[k]);
                else
                    printf("- ");
            }
            printf("HIT\n");
        } 
        else {
            
            if (count < frame) {
                queue[count] = current;
                recent[count] = time;
                count++;
            }
             else {
               
                int lru_index = 0;
                int min_time = recent[0];
                for (int j = 1; j < frame; j++) 
                {
                    if (recent[j] < min_time) {
                        min_time = recent[j];
                        lru_index = j;
                    }
                }
                queue[lru_index] = current;
                recent[lru_index] = time;
            }

            pagefault++;

            
            for (int k = 0; k < frame; k++) {
                if (queue[k] != -1)
                    printf("%d ", queue[k]);
                else
                    printf("- ");
            }
            printf("MISS\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", pagefault);
    return 0;
}
