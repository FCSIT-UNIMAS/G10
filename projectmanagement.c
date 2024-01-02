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

void displayProcessInfo() {
    printf("Process ID: %d, Parent Process ID: %d\n", getpid(), getppid());
}

void performTask() {
    // Simulated task, replace this with actual tasks for child processes
    printf("Task performed by PID %d\n", getpid());
    // Simulated task duration
    sleep(2);
}

void trackResourceUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Resource Usage - PID %d:\n", getpid());
    printf("User CPU Time: %ld.%06ld seconds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System CPU Time: %ld.%06ld seconds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
}

void reportResourceUsage() {
    trackResourceUsage();
    // Additional reporting mechanisms or data formatting can be added here
}

void signalHandler(int signal) {
    if (signal == SIGUSR1) {
        logEvent("Received SIGUSR1 signal, terminating child process.");
        exit(EXIT_SUCCESS);
    }
}

void createProcessTree(int levels) {
    if (levels == 0) {
        performTask();
        exit(EXIT_SUCCESS);
    }

    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        createProcessTree(levels - 1);
    } else {
        int status;
        wait(&status);
        // Perform synchronization or additional tasks after child completion if needed
    }
}

int main() {
    int treeLevels = 5; // Change this to modify the depth of the process tree

    logEvent("Starting the program");

    signal(SIGUSR1, signalHandler);

    createProcessTree(treeLevels);

    reportResourceUsage();

    logEvent("Program finished");

    return 0;
}
