#include <stdio.h>
#define MAX_TASKS 10
#define MAX_INSTANCES 100
typedef struct {
    int pid;
    int arrival;
    int deadline;
    int burst;
    int remaining;
    int abs_deadline;
} Task;
int main() {
    int n;
    int sim_time;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int period[n]; int deadline[n]; int capacity[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Capacity (Burst), Deadline, and Period for Task T%d: ", i + 1);
        scanf("%d %d %d", &capacity[i], &deadline[i], &period[i]);
    }
    printf("Enter total simulation time: ");
    scanf("%d", &sim_time);
    Task instances[MAX_INSTANCES];
    int inst_count = 0;
    for (int i = 0; i < n; i++) {
        for (int t = 0; t < sim_time; t += period[i]) {
            Task ti;
            ti.pid = i + 1;
            ti.arrival = t;
            ti.burst = capacity[i];
            ti.remaining = capacity[i];
            ti.deadline = deadline[i];
            ti.abs_deadline = t + deadline[i];
            instances[inst_count++] = ti;
        }
    }
    printf("\nEarliest Deadline First Scheduling:\n");
    printf("Time\tTask\n");
    for (int time = 0; time < sim_time; time++) {
        int selected = -1, min_deadline = 1e9;
        for (int i = 0; i < inst_count; i++) {
            if (instances[i].arrival <= time && instances[i].remaining > 0 && instances[i].abs_deadline < min_deadline) {
                min_deadline = instances[i].abs_deadline;
                selected = i;
            }
        }
        if (selected != -1) {
            instances[selected].remaining--;
            printf("%d\tT%d\n", time, instances[selected].pid);
        }else printf("%d\tIdle\n", time);
    }
    return 0;
}
