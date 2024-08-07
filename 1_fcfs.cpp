#include <bits/stdc++.h>
using namespace std;
#define MAX 30

struct Process {
    int id;  // Process ID
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};

bool compareArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    Process processes[MAX];
    float awt = 0, atat = 0;

    // Input number of processes
    cout << "Enter number of processes (<=30): ";
    cin >> n;

    // Input burst time and arrival time of processes
    cout << "Enter the burst time of processes: ";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cin >> processes[i].burstTime;
    }

    cout << "Enter the arrival time of processes: ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].arrivalTime;
    }

    // Sort processes by arrival time
    sort(processes, processes + n, compareArrival);

    // Calculate completion time, turn around time, and waiting time
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].turnAroundTime = processes[0].burstTime;
    processes[0].waitingTime = 0;

    for (int i = 1; i < n; i++) {
        processes[i].completionTime = max(processes[i-1].completionTime, processes[i].arrivalTime) + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
    }

    // Calculate total waiting time and turn around time for average calculation
    for (int i = 0; i < n; i++) {
        awt += processes[i].waitingTime;
        atat += processes[i].turnAroundTime;
    }

    awt /= n;
    atat /= n;

    // Output the results in a formatted table
    printf("%-10s%-15s%-15s%-20s%-15s\n", "Process", "Arrival Time", "Burst Time", "Turn Around Time", "Waiting Time");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-20d%-15d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].turnAroundTime, processes[i].waitingTime);
    }

    // Output average waiting time and turn around time
    printf("\nAverage Waiting Time: %.2f\n", awt);
    printf("Average Turn Around Time: %.2f\n", atat);

    return 0;
}
