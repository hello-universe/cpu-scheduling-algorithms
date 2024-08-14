# CPU Scheduling Algorithms
A CPU scheduling algorithm simulator in C++ that allows users to select from multiple scheduling algorithms. The algorithms included are FCFS, SJF, SRTF, Priority Scheduling(Both preemptive and non-preemptive) and Round robin Scheduling.

## Table of Contents

- [CPU Scheduling Algorithms](#cpu-scheduling-algorithms)
  - [Purpose](#purpose)
  - [CPU and I/O Burst Cycles](#cpu-and-io-burst-cycles)
  - [Preemptive vs Non-Preemptive Scheduling](#preemptive-vs-non-preemptive-scheduling)
  - [Key Components](#key-components)
  - [Scheduling Circumstances](#scheduling-circumstances)
  - [Scheduling Criteria](#scheduling-criteria)
  - [Terminologies used in CPU scheduling](#terminologies-used-in-cpu-scheduling)
  - [Algorithms](#algorithms)
    - [First Come First Served (FCFS)](#first-come-first-served-fcfs)
    - [Shortest Job First (SJF)](#shortest-job-first-sjf)
    - [Shortest Remaining Time First(SRTF)](#shortest-remaining-time-first-srtf)
    - [Priority Scheduling](#priority-scheduling)
    - [Round Robin Scheduling](#round-robin-scheduling)
  - [Installation](#installation)
  - [Input Format](#input-format)

## Purpose
- CPU scheduling maximizes CPU utilization in multiprogrammed systems by switching between processes because in a single-processor systems, only one process can run at a time; others must wait.
- Multiprogramming keeps the CPU busy by switching to another process when one waits, improving productivity.

## CPU and I/O Burst Cycles

Process execution consists of a cycle of CPU execution and I/O wait.
Processes alternate between these two states.


- **CPU Burst:** Time a process spends using the CPU.
- **I/O Burst:** Time a process waits for I/O completion.

## Preemptive vs Non-Preemptive Scheduling 

- **Non-Preemptive:** CPU is only taken away when a process terminates or waits.
- **Preemptive:** CPU can be given to another process even while one is running, risking data inconsistency.

## Key Components

- **CPU Scheduler:** Selects a process from the ready queue when the CPU is idle.  The selection process is carried out by the short-term
scheduler (or CPU scheduler).
- **Dispatcher:** Gives control of the CPU to the selected process. The time it takes for the dispatcher to stop one process and start another running is
known as the dispatch latency.

## Scheduling Circumstances

1. Process switches from running to waiting.
2. Process switches from running to ready (e.g., interrupt).
3. Process switches from waiting to ready (e.g., I/O completion).
4. Process terminates.

## Scheduling Criteria

- **CPU Utilization:** % of time CPU is busy.
- **Throughput:** Number of processes completed per unit time.
- **Turnaround Time:** Total time process takes from submission to completion.
- **Waiting Time:** Time spent waiting in the ready queue.
- **Response Time:** Time from request submission to first response.

## Terminologies used in CPU scheduling

- **Arrival Time:** The arrival time of a process is the time at which a process enters the ready queue and is ready to be executed.
- **Burst Time (CPU Burst):** Burst time is the total time required by a process for its execution on the CPU.
- **Completion Time:** Completion time is the time at which a process finishes its execution and exits the CPU.
- **Turnaround Time:** Turnaround time is the total time taken by a process from the time it arrives in the ready queue until it completes execution. It includes the sum of the waiting time, the burst time, and any time spent doing I/O operations.  
**Turnaround Time = Completion Time - Arrival Time**
- **Waiting Time:** Waiting time is the total time a process spends in the ready queue waiting for CPU access. It is the time spent waiting for CPU scheduling.  
**Waiting Time = Turnaround Time - Burst Time**
- **Response Time:** Response time is the time from the submission of a request (arrival time) until the first response is produced. It's important in interactive systems.  
**Response Time = First CPU Allocation Time - Arrival Time**
- **Priority:** Priority is a value associated with each process that determines the order in which processes are scheduled. Higher priority processes are given preference over lower priority processes.
- **Time Quantum (Time Slice):** In round-robin scheduling, the time quantum is the fixed amount of time allocated to each process in the ready queue. If a process does not complete within its time quantum, it is preempted and put back into the queue.
- **Starvation:** Starvation occurs when a process is never executed or experiences an indefinite delay in execution due to lower priority or because it is constantly preempted by other processes.
- **Aging:** Aging is a technique used to prevent starvation by gradually increasing the priority of a process the longer it waits in the ready queue. This ensures that all processes eventually get executed.
- **Ready Queue:** The ready queue is the list of processes that are ready to execute and are waiting for CPU time.

## Algorithms

### First Come First Served (FCFS)

- Simple, non-preemptive scheduling algorithm 
- Processes are allocated CPU based on the order of their arrival
- **Issues**
  - **Convoy effect:**  If processes with higher burst time arrived before the processes with smaller burst time, then, smaller processes have to wait for a long time for longer processes to
release the CPU.

  - Inefficient for time-sharing systems.

### Shortest Job First (SJF)

- Selects the waiting process with the smallest execution time to execute next.
- Non-preemptive in nature.
- If the next CPU bursts of two processes are the same, FCFS scheduling is used to break the tie.
- Beneficial in situations where the objective is to minimize the average waiting time for processes
- **Issues** 
  - [Starvation](https://www.geeksforgeeks.org/starvation-and-aging-in-operating-systems/) of long processes
  - Difficult to predict next burst length.

### Shortest Remaining Time First (SRTF)

- Preemptive version of the Shortest job first
-  The process with the smallest amount of time remaining until completion is selected to execute.
- Like the shortest job first, it also has the potential for process starvation. 
Long processes may be held off indefinitely if short processes are continually added. 

### Priority Scheduling

- CPU is allocated based on process priority.
- It can be premptive or non-premptive.

- **Issues** 
  - Starvation of low-priority processes, mitigated by aging (gradually increasing priority over time).

### Round Robin Scheduling

- Processes served in FCFS order with fixed time slices (quantum).
- It is always preemptive.
- It is best suited for time sharing system, client server architecture and interactive system.
- **Issues** 
  - Starvation for long processes as they have to repeat the cycle many times.
  - Performance depends on time quantum size.
Priorities cannot be set for processes.

- **Key Insights**
  - **Smaller quantum:** Better response time, higher context switches.
  - **Larger quantum:** Fewer context switches, resembles FCFS with larger quantum.

## Installation

1. Clone the repository.
2. Install g++ compiler.
3. Compile the code using the below command.
```bash
    g++ main.cpp -o main
```
4. Run the executable file.
```bash
    .\main
```

## Input Format
- **Line 1:** The number of processes(n)
- **Line 2:** The burst time of n processes.
- **Line 3:** The arrival time of n processes.
- **Line 4 (Only for priority and round robin scheduling):**
  - In case of priority scheduling algorithms(both premptive and non-premptive) the fourth line of input contains the priority of n processes such that lower is the number higher is the priority.
  - In case of round robin scheduling the fourth line of input contains the time quantum.