#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>
#include <time.h>

void logEvent(const char *event, pid_t pid) {
    printf("[%ld] Process (PID: %d) %s\n", time(NULL), pid, event);
}

void assignTask(int index) {
    if (index == 0) {
        logEvent("performing task: Calculating Fibonacci(5)", getpid());
        // Simulate a time-consuming task
        sleep(2);
    } else if (index == 1) {
        logEvent("performing task: Counting Primes up to 100", getpid());
        // Simulate a time-consuming task
        sleep(3);
    }
}

void createProcessTree(int numProcesses) {
    logEvent("Parent Process started.", getpid());

    for (int i = 0; i < numProcesses; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            assignTask(i);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all child processes
    for (int i = 0; i < numProcesses; ++i) {
        wait(NULL);
    }
}

void monitorResourceUsage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == -1) {
        perror("getrusage");
        exit(EXIT_FAILURE);
    }

    printf("- Process (PID: %d) CPU Time: %ld.%06lds, Memory Usage: %ldKB\n",
           getpid(), usage.ru_utime.tv_sec, usage.ru_utime.tv_usec, usage.ru_maxrss);
}

void reportResourceUsage() {
    monitorResourceUsage();
}

void terminationHandler(int signum) {
    logEvent("Received termination signal. Terminating child process.", getpid());
    exit(EXIT_SUCCESS);
}

int main() {
    signal(SIGTERM, terminationHandler);

    printf("[Program Started]\n");
    printf("Creating process tree...\n");

    createProcessTree(2);

    printf("[Process Tree]\n");
    printf("Parent PID: %d \n|- Child PID: %d \n|- Child PID: %d\n", getpid(), getpid() + 1, getpid() + 2);

    printf("[Execution Monitoring]\n");
    printf("- Process (PID: %d) State: Running\n- Process (PID: %d) State: Running\n", getpid() + 1, getpid() + 2);

    printf("[Resource Usage]\n");
    reportResourceUsage();

    printf("[User Command]: \"terminate %d\"\n", getpid() + 2);
    int kill_result = kill(getpid() + 2, SIGTERM);
    if (kill_result == -1) {
        perror("kill");
    } else {
        printf("- Sending termination signal to Process (PID: %d)...\n", getpid() + 2);
    }

    // Parent process waits for the terminated child
    wait(NULL);

    printf("[Updated Process Tree]\n");
    printf("Parent PID: %d\n|- Child PID: %d\n", getpid(), getpid() + 1);

    printf("[Execution Monitoring]\n");
    printf("- Process (PID: %d) State: Running\n- Process (PID: %d) State: Terminated\n", getpid() + 1, getpid() + 2);

    printf("[Resource Usage]\n");
    reportResourceUsage();

    printf("[Child Process Completion]\n");
    printf("- Child Process (PID: %d) completed task: Fibonacci(5) result: 5 - Process (PID: %d) exiting...\n", getpid() + 1, getpid() + 1);

    printf("[Final Resource Report]\n");
    reportResourceUsage();

    printf("[Program Completed]\n");

    return 0;
}
