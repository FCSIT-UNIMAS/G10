Project Overview
--
The goal of this project is to get students interested in low-level system programming in a Unix/Linux environment by using the C language. The main goal is to give students practical experience with the fundamentals of Unix/Linux system programming, with a focus on process control and management via the use of system calls directly. The project includes work on creating process trees, tracking resource utilization, keeping an eye on system-level executions, and setting up a logging system. Peer review and collaborative elements are also combined to improve learning through interaction and feedback.
*******
*******

Installation Instructions:
--
To set up the environment for this project, follow these steps:

*Linux Environment:*
Ensure you are using a Linux environment that supports C programming compilation and execution from the command line.

*Compiler:*
Make sure you have a C compiler installed. If not, install it using the package manager specific to your Linux distribution (e.g., sudo apt-get install gcc on Ubuntu).


Compilation Instructions:
--
1. To compile the C program, use the following instructions:
  
   gcc -o filename.c


Execution Instructions:
--
1. Run the program with a specified number of processes (1, 3, or 5):

   ./filename 

2. Follow the on-screen prompt to enter the desired number of processes.


Output Explanation:
--
Upon running the program with the specified number of processes, the following key information will be displayed in the terminal:

1. *Process Tree:*
   
   - A hierarchical structure representing the parent and child processes.
   - Each process is identified by its Process ID (PID), and their relationships are visually represented.

2. *Execution Monitoring:*
   - States of each process, indicating whether it is running or terminated.
   - Displayed with the corresponding PID and its execution state.

3. *Resource Usage:*
   - Real-time tracking of CPU time and memory consumption for both the parent and child processes.
   - Presented in a structured format including CPU time in seconds and memory usage in megabytes.

4. *User Commands Simulation:*
   - A simulated user command to terminate a specific child process identified by its PID.
   - Displayed with a message indicating the termination signal sent and the termination status.

5. *Updated Process Tree:*
   - The modified process tree after the simulated termination, indicating which child process has been terminated.

6. *Child Process Completion:*
   - Specific details about the completion of child processes' tasks.
   - For example, displaying the task performed, its result, and an exit message.

7. *Final Resource Report:*
   * A summary of resource usage after the completion of the entire program.
   * Includes CPU time and memory usage for the entire process tree.

8. *Program Completion:*
   * A concluding message indicating the successful completion of the program.


Tool Usage (GDB):
---
1. *For debugging using GDB, compile the program with debugging symbols:*
   - gcc -o filename -g filename.c

2. *Run the program in GDB:*
   - gdb ./filename_debug 

3. *Set breakpoints, inspect variables, and step through the code using GDB commands:*
   - (gdb) break main
   - (gdb) run

4. *Use GDB commands such as print, step, next, and continue for debugging.*
   
5. *Exit GDB:*
   - (gdb) quit


Contributors:
--
1.	Mohamad Shaziq Bin Mohamad Aziz (73558)

  	| *Contribution:* Coding |

2.  Muhammad Hafiz Bin Awang Arsat (75870)

    | *Contribution:* Coding |
   
3.  Luqman Hafiz Bin Mohamad (75513)

    | *Contribution:* Cooding |
  
4.  Aaron Arthur Anak Stanley John (73895)

    | *Contribution:* Coding & Instruction/Description for README file |



