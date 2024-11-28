#include <stdio.h>

void worst_fit(int memory_blocks[], int block_size, int processes[], int process_size) {
    int allocation[process_size];
    int fragmentation = 0;

    for (int i = 0; i < process_size; i++) {
        allocation[i] = -1; 
        int worst_idx = -1;
        int worst_size = -1;

        for (int j = 0; j < block_size; j++) {
            if (memory_blocks[j] >= processes[i] && memory_blocks[j] > worst_size) {
                worst_size = memory_blocks[j];
                worst_idx = j;
            }
        }
        if (worst_idx != -1) {
            allocation[i] = worst_idx; 
            fragmentation += (memory_blocks[worst_idx] - processes[i]); 
            memory_blocks[worst_idx] -= processes[i]; 
        }
    }

    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < process_size; i++) {
        printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
    }
    printf("Total Fragmentation: %d\n", fragmentation);
}

int main() {
    int memory_blocks[] = {100, 500, 200, 300, 600};
    int processes[] = {212, 417, 112, 426};
    int block_size = sizeof(memory_blocks) / sizeof(memory_blocks[0]);
    int process_size = sizeof(processes) / sizeof(processes[0]);

    worst_fit(memory_blocks, block_size, processes, process_size);
    return 0;
}
