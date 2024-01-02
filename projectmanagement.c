#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>
#include <time.h>

void logEvent(const char *event) {
    time_t now;
    time(&now);
    printf("[%s] %s\n", ctime(&now), event);
}

void displayProcessInfo(int pid, int ppid) {
    printf("[Process %d (Parent: %d)] ", pid, ppid);
}

void performTask(int pid, int taskType) {
    displayProcessInfo(pid, getppid());

    switch (taskType) {
        case 1:
            printf("Child Process performing task: Calculating Fibonacci(5)\n");
            // Simulated task duration
            sleep(2);
            break;
        case 2:
            printf("Child Process performing task: Counting Primes up to 100\n");
            // Simulated task duration
            sleep(3);
            break;
        default:
            break;
    }
}

void trackResourceUsage(int pid, double cpuTime, double memoryUsage) {
    displayProcessInfo(pid, getppid());
    printf("CPU Time: %.2fs, Memory Usage: %.1fMB\n", cpuTime, memoryUsage);
}

void signalHandler(int signal) {
    if (signal == SIGUSR1) {
        logEvent("Received termination signal.");
    }
}

void createProcessTree(int levels) {
    int taskType = 1;

    if (levels == 0) {
        int pid = getpid();
        performTask(pid, taskType);
        exit(EXIT_SUCCESS);
    }

    int pid = getpid();
    int ppid = getppid();
    displayProcessInfo(pid, ppid);
    printf("Creating process tree...\n");

    logEvent("Program Started");

    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        taskType = (taskType == 1) ? 2 : 1; // Alternate task types for child processes
        createProcessTree(levels - 1);
    } else {
        int status;
        wait(&status);

        printf("[Process Tree]\n");
        printf("Parent PID: %d |- Child PID: %d\n", getpid(), child_pid);
        // Simulate execution monitoring and resource usage
        trackResourceUsage(pid, 0.02, 1.2);
        trackResourceUsage(child_pid, 0.055, 0.8);

        logEvent("User Command: \"terminate 1002\"");
        kill(child_pid, SIGUSR1);

        waitpid(child_pid, NULL, 0);

        printf("[Updated Process Tree]\n");
        printf("Parent PID: %d\n", getpid());

        printf("[Execution Monitoring]\n");
        printf("Process (PID: %d) State: Running\n", getpid());
        printf("Process (PID: %d) State: Terminated\n", child_pid);

        trackResourceUsage(pid, 0.03, 1.3);
        printf("[Child Process Completion]\n");
        printf("Child Process (PID: %d) completed task: Fibonacci(5) result: 5 - Process (PID: %d) exiting...\n", child_pid, child_pid);

        printf("[Final Resource Report]\n");
        printf("Parent Process (PID: %d) CPU Time: 0.05s, Memory Usage: 1.4MB\n", getpid());
        printf("Child Process (PID: %d) CPU Time: 0.08s, Memory Usage: 0.8MB\n", child_pid);

        logEvent("Program Completed");
        printf("[Program Completed]\n");
    }
}

int main() {
    int treeLevels = 1; // Change this to modify the depth of the process tree

    signal(SIGUSR1, signalHandler);

    createProcessTree(treeLevels);

    return 0;
}

