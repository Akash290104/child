#include <stdio.h>
#include <unistd.h>    // For fork(), getpid(), getppid(), exec()
#include <sys/types.h> // For pid_t
#include <sys/wait.h>  // For wait()
#include <stdlib.h>    // For exit()
#include <string.h>    // For strlen()

int main() {
    int a, b;
    pid_t pid;

    // Display Parent and Process IDs
    printf("Before fork:\n");
    printf("Parent PID: %d\n", getppid());
    printf("Current PID: %d\n", getpid());

    // Prompt user for numbers and read input
    printf("Enter the numbers: ");
    scanf("%d %d", &a, &b);

    // Create a process using fork
    pid = fork();

    if (pid < 0) {
        // fork failed
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // In the child process
        printf("In Child Process:\n");
        printf("Parent PID: %d\n", getppid());
        printf("Child PID: %d\n", getpid());

        // Make the child process an orphan
        sleep(5); // Allow time for the parent to exit

        // Replace child process with a new program using exec()
        char sum_command[256];
        snprintf(sum_command, sizeof(sum_command), "./child_program %d %d", a, b);

        execlp("sh", "sh", "-c", sum_command, (char *)NULL);
        perror("execlp failed"); // If execlp fails
        exit(1);
    } else {
        // In the parent process
        printf("In Parent Process:\n");
        printf("Parent PID: %d\n", getpid());

        // Wait for the child process to complete
        wait(NULL); // Wait for any child process

        printf("Parent exiting...\n");
        exit(0); // Exit the parent process
    }

    return 0;
}

































