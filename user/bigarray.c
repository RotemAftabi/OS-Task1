#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void) {
    int no_children = 4;  // Number of child processes to create
    const int N = 1 << 16;  // 2^16
    int *array = (int *)malloc(N * sizeof(int));
    if (!array) {
        fprintf(2, "Failed to allocate memory.\n");
        return 1;
    }

    // Initialize array with consecutive integers: 0..(N-1)
    for (int i = 0; i < N; i++) {
        array[i] = i;
    }

    // We'll create 4 child processes; set up a pids array for storing child PIDs
    int pids[no_children];
    int procId = forkn(no_children, pids);
    if (procId < 0) {
        fprintf(2, "forkn() failed.\n");
        free(array);
        return 1;
    }

    if (procId == 0) {
        // Parent process
        int childSums[no_children];
        if (waitall(&no_children, childSums) < 0) {
            fprintf(2, "waitall() failed.\n");
            free(array);
            return 1;
        }

        // Sum up partial sums from children
        long long total = 0;
        for (int i = 0; i < no_children; i++) {
            total += childSums[i];
        }

        // Print the final total sum
        printf("Final sum: %lld\n", total);

        free(array);
        return 0;

    } else {
        // Child processes (1 through 4)
        int subSize = N / no_children;
        int start = (procId - 1) * subSize;
        int end   = (procId == no_children) ? N : procId * subSize;

        long long partialSum = 0;
        for (int i = start; i < end; i++) {
            partialSum += array[i];
        }

        // Print the partial sum
        printf("Child %d partial sum: %lld\n", procId, partialSum);

        // Return partial sum as exit status (truncated to int)
        exit((int)partialSum, "");
    }
}
