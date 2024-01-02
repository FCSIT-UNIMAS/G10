Project Overview

The goal of this project is to get students interested in low-level system programming in a Unix/Linux environment by using the C language. The main goal is to give students practical experience with the fundamentals of Unix/Linux system programming, with a focus on process control and management via the use of system calls directly. The project includes work on creating process trees, tracking resource utilization, keeping an eye on system-level executions, and setting up a logging system. Peer review and collaborative elements are also combined to improve learning through interaction and feedback.



Installation Instructions:
To set up the environment for this project, follow these steps:



Linux Environment:
Ensure you are using a Linux environment that supports C programming compilation and execution from the command line.

Compiler:
Make sure you have a C compiler installed. If not, install it using the package manager specific to your Linux distribution (e.g., sudo apt-get install gcc on Ubuntu).




Compilation Instructions:
To compile the C program, use the following instructions:
'gcc -o projectManagement.c'.




Execution Instructions:
To run the program, follow these steps:
'./projectManagement [num_processes]'
Replace [num_processes] with the desired number of child processes (e.g., 1, 3, 5). This parameter controls the complexity of the process tree.




Direct Process Tree Construction (Task A1)

The program initializes process tree creation using fork().
A hierarchical tree structure is formed using loops or recursion to create multiple levels of child processes.
Each child process is assigned a specific task, such as mathematical or file operations.
Parent processes use wait() or waitpid() for proper synchronization, ensuring they proceed only after all child processes complete their tasks.




System-Level Execution Monitoring (Task A2)

Processes identify themselves using getpid() and retrieve their parent's ID using getppid().
Information is displayed in the terminal, showcasing the structure of the process tree.
Signal handling using signal() or sigaction() enables parent processes to send signals to children.
The parent can terminate child processes using kill() based on specific conditions.




Resource Usage Monitoring (Task A3)

getrusage() is implemented in both parent and child processes to track resource usage.
Metrics such as CPU time (user and system) and memory consumption are collected.
A function is designed to format and output real-time or interval-based resource usage data.




Code Execution and Debugging (Task A4)
A logging mechanism is implemented to record key events (process creation, termination, system call invocation).
Logs include timestamps, process IDs, and descriptions of actions.
