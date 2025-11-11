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
		    for (int i = 0; i < fcount; i++) {
			scanf("%d", &page[i]);
		    }

		    int queue[frame];
		    int front = 0, rear = 0, count = 0;
		    int pagefault = 0;

		    for (int i = 0; i < frame; i++) 
		    {
			queue[i] = -1;
		    }

		    printf("\n-FIFO Page Replacement Process\n");

		    for (int i = 0; i < fcount; i++) {
			int current = page[i];
			printf("Current Page %d->", current);

			if (inqueue(queue, count, current)) {
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
				queue[rear] = current;
				rear = (rear + 1) % frame;
				count++;
			    } 
			    else 
			    {
				queue[front] = current;
				front = (front + 1) % frame;
			    }

			    pagefault++;

			    for (int k = 0; k < frame; k++) 
			    {
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
