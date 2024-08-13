#include <bits/stdc++.h>
using namespace std;
#define MAX 30

struct Process
{
    int id; // Process ID
    int arrivalTime;
    int burstTime;
    int remainingTime;
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
    Sample Input:
    5
    1 4 2 6 3
    3 1 4 0 2
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
        processes[i].remainingTime = processes[i].burstTime;
    }

    cout << "Enter the arrival time of processes: ";
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].arrivalTime;
    }

    // Sort processes by arrival time
    sort(processes, processes + n, compareArrival);

    // Initialize variables for current time and processes completed
    int currentTime = 0;
    int completed = 0;
    // vector<bool> isCompleted(n, false);

    while (completed < n)
    {
        // Find the process with the shortest burst time that has arrived
        int shortestIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                if (shortestIndex == -1 || processes[i].remainingTime < processes[shortestIndex].remainingTime)
                {
                    shortestIndex = i;
                }
            }
        }

        // If no process has arrived, move the current time forward
        if (shortestIndex == -1)
        {
            ++currentTime;
            continue;
        }

        // Process the shortest job
        ++currentTime;
        --processes[shortestIndex].remainingTime;
        if (processes[shortestIndex].remainingTime == 0)
        {
            processes[shortestIndex].completionTime = currentTime;
            processes[shortestIndex].turnAroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
            processes[shortestIndex].waitingTime = processes[shortestIndex].turnAroundTime - processes[shortestIndex].burstTime;
            // isCompleted[shortestIndex] = true;
            completed++;
        }
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
    printf("\n%-10s%-15s%-15s%-20s%-15s\n\n", "Process", "Arrival Time", "Burst Time", "Turn Around Time", "Waiting Time");
    for (int i = 0; i < n; i++)
    {
        printf("%-10d%-15d%-15d%-20d%-15d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].turnAroundTime, processes[i].waitingTime);
    }

    // Output average waiting time and turn around time
    printf("\nAverage Waiting Time: %.2f\n", awt);
    printf("Average Turn Around Time: %.2f\n", atat);

    return 0;
}
