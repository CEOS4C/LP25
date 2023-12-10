#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void compute_i_primary(int i) {
    int index = 0;
    uint64_t values[i];
    values[index++] = 2;
    values[index++] = 3;
    int n = 5;

    while (index < i) {
        int v;
        for (v = 0; v < index && sqrt(n) >= values[v]; ++v) {
            if (n % values[v] == 0) {
                break;
            }
        }
        if (n % values[v] != 0)
            values[index++] = n;
        n += 2;
    }

    if (i == 1000){
        printf("Child %d [%d] 1000e nombre premier : %lu\n", i, getpid(), values[999]);
    }

    if (i == 98){
        printf("Child %d [%d] 98e nombre premier : %lu\n", i, getpid(), values[97]);
    }
}

int main() {
    pid_t child_pid1, child_pid2;

    if ((child_pid1 = fork()) == 0) {
        printf("Child 1 (PID=%d)\n", getpid());
        compute_i_primary(1000);
        printf("Child 1 [%d] End\n", getpid());
        exit(0);
    }

    if ((child_pid2 = fork()) == 0) {
        printf("Child 2 (PID=%d)\n", getpid());
        compute_i_primary(98);
        printf("Child 2 [%d] End\n", getpid());
        exit(0);
    }

    printf("Parent (PID=%d)\n", getpid());

    waitpid(child_pid1, NULL, 0);
    waitpid(child_pid2, NULL, 0);

    printf("Parent [%d] End\n", getpid());
    return 0;
}
