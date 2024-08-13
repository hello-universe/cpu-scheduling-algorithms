#include <bits/stdc++.h>
using namespace std;
#define MAX 30

struct Process
{
    int id; // Process ID
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};

bool compareArrival(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
}

int main()
{
    int n;
    Process processes[MAX];
    float awt = 0, atat = 0;

    /*
    Sample Input
    5
    4 3 1 5 2
    0 1 2 3 4
    5 4 3 2 2
    */

    // Input number of processes
    cout << "Enter number of processes (<=30): ";
    cin >> n;

    // Input burst time and arrival time of processes
    cout << "Enter the burst time of processes: ";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cin >> processes[i].burstTime;
    }

    cout << "Enter the arrival time of processes: ";
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].arrivalTime;
    }

    cout << "Enter the priority of processes(Lower the number higher the priority): ";
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].priority;
    }

    // Sort processes by arrival time
    sort(processes, processes + n, compareArrival);

    // Initialize variables for current time and processes completed
    int currentTime = 0;
    int completed = 0;
    vector<bool> isCompleted(n, false);

    while (completed < n)
    {
        // Find the process with the highest priority that has arrived
        int highestPriority = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i])
            {
                if (highestPriority == -1 || processes[i].priority < processes[highestPriority].priority)
                {
                    highestPriority = i;
                }
            }
        }

        // If no process has arrived, move the current time forward
        if (highestPriority == -1)
        {
            currentTime++;
            continue;
        }

        // Execute the process with highest priority
        currentTime += processes[highestPriority].burstTime;
        processes[highestPriority].completionTime = currentTime;
        processes[highestPriority].turnAroundTime = processes[highestPriority].completionTime - processes[highestPriority].arrivalTime;
        processes[highestPriority].waitingTime = processes[highestPriority].turnAroundTime - processes[highestPriority].burstTime;
        isCompleted[highestPriority] = true;
        completed++;
    }

    // Calculate total waiting time and turn around time for average calculation
    for (int i = 0; i < n; i++)
    {
        awt += processes[i].waitingTime;
        atat += processes[i].turnAroundTime;
    }

    awt /= n;
    atat /= n;

    // Output the results in a formatted table
    printf("\n\n%-10s%-15s%-15s%-15s%-20s%-15s\n\n", "Process", "Arrival Time", "Burst Time", "Priority", "Turn Around Time", "Waiting Time");
    for (int i = 0; i < n; i++)
    {
        printf("%-10d%-15d%-15d%-15d%-20d%-15d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].turnAroundTime, processes[i].waitingTime);
    }

    // Output average waiting time and turn around time
    printf("\nAverage Waiting Time: %.2f\n", awt);
    printf("Average Turn Around Time: %.2f\n", atat);

    return 0;
}
