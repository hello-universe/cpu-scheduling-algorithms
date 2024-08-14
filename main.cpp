#include <bits/stdc++.h>
using namespace std;
#define MAX 30
struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime = 0;
    int priority = 0;
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
    int choice;
    do
    {
        cout << "\n1. FCFS" << endl;
        cout << "2. SJF" << endl;
        cout << "3. SRTF" << endl;
        cout << "4. Priority (Non Preemptive)" << endl;
        cout << "5. Priority (Preemptive)" << endl;
        cout << "6. Round Robin" << endl;
        cout << "7. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        if(choice==7){
            break;
        }
        else if(choice!=1 && choice!=2 && choice!=3 && choice!=4 && choice!=5 && choice!=6){
            cout<<"Invalid choice\n";
            continue;
        }
        int n;
        Process processes[MAX];
        float awt = 0, atat = 0;
        int currentTime = 0, completed = 0;

        cout << "Enter number of processes(<=30): ";
        cin >> n;
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
        vector<bool> isCompleted(n, false);
        int quantum;
        queue<int> readyQueue;
        bool inQueue[n] = {false};
        switch (choice)
        {
        case 1:
            // Sort processes by arrival time
            sort(processes, processes + n, compareArrival);

            // Calculate completion time, turn around time, and waiting time
            processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
            processes[0].turnAroundTime = processes[0].burstTime;
            processes[0].waitingTime = 0;

            for (int i = 1; i < n; i++)
            {
                processes[i].completionTime = max(processes[i - 1].completionTime, processes[i].arrivalTime) + processes[i].burstTime;
                processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
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
            printf("%-10s%-15s%-15s%-20s%-15s\n", "Process", "Arrival Time", "Burst Time", "Turn Around Time", "Waiting Time");
            for (int i = 0; i < n; i++)
            {
                printf("%-10d%-15d%-15d%-20d%-15d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].turnAroundTime, processes[i].waitingTime);
            }

            // Output average waiting time and turn around time
            printf("\nAverage Waiting Time: %.2f\n", awt);
            printf("Average Turn Around Time: %.2f\n", atat);
            break;
        case 2:
            // Sort processes by arrival time
            sort(processes, processes + n, compareArrival);

            while (completed < n)
            {
                // Find the process with the shortest burst time that has arrived
                int shortestIndex = -1;
                for (int i = 0; i < n; i++)
                {
                    if (processes[i].arrivalTime <= currentTime && !isCompleted[i])
                    {
                        if (shortestIndex == -1 || processes[i].burstTime < processes[shortestIndex].burstTime)
                        {
                            shortestIndex = i;
                        }
                    }
                }

                // If no process has arrived, move the current time forward
                if (shortestIndex == -1)
                {
                    currentTime++;
                    continue;
                }

                // Process the shortest job
                currentTime += processes[shortestIndex].burstTime;
                processes[shortestIndex].completionTime = currentTime;
                processes[shortestIndex].turnAroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
                processes[shortestIndex].waitingTime = processes[shortestIndex].turnAroundTime - processes[shortestIndex].burstTime;
                isCompleted[shortestIndex] = true;
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
            printf("\n%-10s%-15s%-15s%-20s%-15s\n\n", "Process", "Arrival Time", "Burst Time", "Turn Around Time", "Waiting Time");
            for (int i = 0; i < n; i++)
            {
                printf("%-10d%-15d%-15d%-20d%-15d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].turnAroundTime, processes[i].waitingTime);
            }

            // Output average waiting time and turn around time
            printf("\nAverage Waiting Time: %.2f\n", awt);
            printf("Average Turn Around Time: %.2f\n", atat);
            break;
        case 3:
            // Sort processes by arrival time
            sort(processes, processes + n, compareArrival);

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
            break;
        case 4:
            cout << "Enter the priority of processes(Lower the number higher the priority): ";
            for (int i = 0; i < n; i++)
            {
                cin >> processes[i].priority;
            }
            // Sort processes by arrival time
            sort(processes, processes + n, compareArrival);

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
            break;

        case 5:
            cout << "Enter the priority of processes(Lower the number higher the priority): ";
            for (int i = 0; i < n; i++)
            {
                cin >> processes[i].priority;
            }
            // Sort processes by arrival time
            sort(processes, processes + n, compareArrival);

            while (completed < n)
            {
                // Find the process with the highest priority that has arrived
                int highestPriority = -1;
                for (int i = 0; i < n; i++)
                {
                    if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
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
                    ++currentTime;
                    continue;
                }

                // Execute the process with highest priority
                ++currentTime;
                --processes[highestPriority].remainingTime;
                if (processes[highestPriority].remainingTime == 0)
                {

                    processes[highestPriority].completionTime = currentTime;
                    processes[highestPriority].turnAroundTime = processes[highestPriority].completionTime - processes[highestPriority].arrivalTime;
                    processes[highestPriority].waitingTime = processes[highestPriority].turnAroundTime - processes[highestPriority].burstTime;
                    ++completed;
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
            printf("\n\n%-10s%-15s%-15s%-15s%-20s%-15s\n\n", "Process", "Arrival Time", "Burst Time", "Priority", "Turn Around Time", "Waiting Time");
            for (int i = 0; i < n; i++)
            {
                printf("%-10d%-15d%-15d%-15d%-20d%-15d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].turnAroundTime, processes[i].waitingTime);
            }

            // Output average waiting time and turn around time
            printf("\nAverage Waiting Time: %.2f\n", awt);
            printf("Average Turn Around Time: %.2f\n", atat);
            break;
        case 6:

            cout << "Enter time quantum: ";
            cin >> quantum;

            // Enqueue processes that arrive at time 0
            for (int i = 0; i < n; i++)
            {
                if (processes[i].arrivalTime <= currentTime && !inQueue[i])
                {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            while (completed < n)
            {
                if (!readyQueue.empty())
                {
                    int i = readyQueue.front();
                    readyQueue.pop();

                    // Execute process for a time quantum or its remaining time, whichever is smaller
                    int timeSlice = min(quantum, processes[i].remainingTime);
                    processes[i].remainingTime -= timeSlice;
                    currentTime += timeSlice;

                    // Check if the process is completed
                    if (processes[i].remainingTime == 0)
                    {
                        processes[i].completionTime = currentTime;
                        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                        completed++;
                    }

                    // Enqueue new processes that have arrived during the current time slice
                    for (int j = 0; j < n; j++)
                    {
                        if (processes[j].arrivalTime <= currentTime && !inQueue[j] && processes[j].remainingTime > 0)
                        {
                            readyQueue.push(j);
                            inQueue[j] = true;
                        }
                    }

                    // Re-enqueue the current process if it's not finished
                    if (processes[i].remainingTime > 0)
                    {
                        readyQueue.push(i);
                    }
                }
                else
                {
                    // If no process is ready, move time forward
                    currentTime++;
                    for (int i = 0; i < n; i++)
                    {
                        if (processes[i].arrivalTime <= currentTime && !inQueue[i])
                        {
                            readyQueue.push(i);
                            inQueue[i] = true;
                        }
                    }
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
            printf("\nFor Time Quantum: %d\n", quantum);
            printf("Average Waiting Time: %.2f\n", awt);
            printf("Average Turn Around Time: %.2f\n", atat);
            break;
        case 7:
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 7);
    return 0;
}