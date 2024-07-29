#include <stdio.h>

#define MAX 100

typedef struct {
    int size;
    int allocated;
    int process_id;
} Block;

void firstFit(int memory[], int memSize, int processes[], int procSize) {
    int allocation[MAX] = {-1};

    for (int i = 0; i < procSize; i++) {
        for (int j = 0; j < memSize; j++) {
            if (memory[j] >= processes[i]) {
                allocation[i] = j;
                memory[j] -= processes[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < procSize; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int memSize, procSize;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &memSize);

    int memory[memSize];
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < memSize; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &memory[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &procSize);

    int processes[procSize];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < procSize; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }

    firstFit(memory, memSize, processes, procSize);

    return 0;
}


OUTPUT

Enter the number of memory blocks: 3
Enter the sizes of the memory blocks:
Block 1: 5
Block 2: 3
Block 3: 1
Enter the number of processes: 3
Enter the sizes of the processes:
Process 1: 5
Process 2: 8
Process 3: 3

Process No.     Process Size    Block No.
1               5               1
2               8               1
3               3               2
