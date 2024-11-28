#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    int execution_time;
    int priority;
} Process;

void generate_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].execution_time = rand() % 20 + 1; // Random execution time between 1 and 20
        processes[i].priority = rand() % 10 + 1;      // Random priority between 1 and 10
    }
}

void sort_by_id(Process processes[], int n) {
    // No sorting needed as processes are already in order of their ID
}

void sort_by_execution_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].execution_time > processes[j].execution_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void sort_by_priority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void fcfs_scheduling(Process processes[], int n) {
    int waiting_time = 0, turnaround_time = 0;
    int total_wt = 0, total_tat = 0;
    int completion_time = 0;

    printf("\nFCFS Scheduling:\n");
    printf("Process ID\tExecution Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        waiting_time = completion_time;
        turnaround_time = waiting_time + processes[i].execution_time;

        total_wt += waiting_time;
        total_tat += turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].execution_time, waiting_time, turnaround_time);

        completion_time += processes[i].execution_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

void sjf_scheduling(Process processes[], int n) {
    int waiting_time = 0, turnaround_time = 0;
    int total_wt = 0, total_tat = 0;
    int completion_time = 0;

    printf("\nSJF Scheduling:\n");
    printf("Process ID\tExecution Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        waiting_time = completion_time;
        turnaround_time = waiting_time + processes[i].execution_time;

        total_wt += waiting_time;
        total_tat += turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].execution_time, waiting_time, turnaround_time);

        completion_time += processes[i].execution_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

void priority_scheduling(Process processes[], int n) {
    int waiting_time = 0, turnaround_time = 0;
    int total_wt = 0, total_tat = 0;
    int completion_time = 0;

    printf("\nPriority Scheduling:\n");
    printf("Process ID\tExecution Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        waiting_time = completion_time;
        turnaround_time = waiting_time + processes[i].execution_time;

        total_wt += waiting_time;
        total_tat += turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].execution_time, processes[i].priority, waiting_time, turnaround_time);

        completion_time += processes[i].execution_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int num_processes = 7;
    Process processes[num_processes];

    generate_processes(processes, num_processes);

    printf("Generated Processes (ID, Execution Time, Priority):\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: Execution Time = %d, Priority = %d\n", processes[i].id, processes[i].execution_time, processes[i].priority);
    }

    sort_by_id(processes, num_processes);
    fcfs_scheduling(processes, num_processes);

    // SJF Scheduling
    sort_by_execution_time(processes, num_processes);
    sjf_scheduling(processes, num_processes);

    // Priority Scheduling
    sort_by_priority(processes, num_processes);
    priority_scheduling(processes, num_processes);

    return 0;
}

