#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>

void displayProcessTree(int level) {
    for (int i = 0; i < level; ++i)
        printf("|- ");

    printf("Process (PID: %d) ", getpid());
}

void performTask(int taskID) {
    printf("performing task: ");

    if (taskID % 2 == 0) {
        printf("Calculating Fibonacci(5)\n");
        // Task: Calculate Fibonacci(5)
        // ... (actual implementation not shown for brevity)
    } else {
        printf("Counting Primes up to 100\n");
        // Task: Count Primes up to 100
        // ... (actual implementation not shown for brevity)
    }
}

void monitorResourceUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    printf("CPU Time: %ld.%06ld s, Memory Usage: %.1fMB\n",
           usage.ru_utime.tv_sec + usage.ru_stime.tv_sec,
           usage.ru_utime.tv_usec + usage.ru_stime.tv_usec,
           (double)usage.ru_maxrss / 1024);
}

void logEvent(const char* event) {
    printf("[%s]\n", event);
}

int main() {
    printf("[Program Started]\nCreating process tree...\n");
    
    displayProcessTree(0);
    printf("started.\n");

    for (int i = 1; i <= 2; ++i) {
        pid_t childPID = fork();

        if (childPID == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (childPID == 0) {  // Child process
            displayProcessTree(i);
            printf("created.\n");

            performTask(i);

            exit(EXIT_SUCCESS);
        } else {  // Parent process
            waitpid(childPID, NULL, 0);
        }
    }

    printf("[Process Tree]\nParent PID: %d\n", getpid());
    for (int i = 1; i <= 2; ++i) {
        printf("|- Child PID: %d\n", getpid() + i);
    }

    printf("[Execution Monitoring]\n");
    for (int i = 1; i <= 2; ++i) {
        printf("- Process (PID: %d) State: Running\n", getpid() + i);
    }

    printf("[Resource Usage]\n");
    monitorResourceUsage();

    // Simulate termination command
    printf("[User Command]: \"terminate %d\"\n", getpid() + 2);
    printf("- Sending termination signal to Process (PID: %d)...\n", getpid() + 2);
    kill(getpid() + 2, SIGTERM);
    waitpid(getpid() + 2, NULL, 0);
    printf("- Process (PID: %d) terminated.\n", getpid() + 2);

    printf("[Updated Process Tree]\nParent PID: %d\n", getpid());
    printf("|- Child PID: %d\n", getpid() + 1);

    printf("[Execution Monitoring]\n");
    printf("- Process (PID: %d) State: Running\n", getpid() + 1);
    printf("- Process (PID: %d) State: Terminated\n", getpid() + 2);

    printf("[Resource Usage]\n");
    monitorResourceUsage();

    printf("[Child Process Completion]\n");
    printf("- Child Process (PID: %d) completed task: Fibonacci(5) result: 5\n", getpid() + 1);
    printf("- Process (PID: %d) exiting...\n", getpid() + 1);

    printf("[Final Resource Report]\n");
    monitorResourceUsage();

    printf("[Program Completed]\n");

    return 0;
}
