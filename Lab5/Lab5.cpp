//FCFS, SJF, SRTF
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INT_MAX 2147483647

struct Process {
    int id, arrivalTime, burstTime, priority;
    int completionTime, turnAroundTime, waitingTime, remainingTime;
};

void calculateTimes(vector<Process>& processes) {
    int total_wt = 0, total_tat = 0;
    for (auto& p : processes) {
        total_wt += p.waitingTime;
        total_tat += p.turnAroundTime;
    }
    cout << "Avg Waiting Time: " << (float)total_wt / processes.size() << endl;
    cout << "Avg Turn Around Time: " << (float)total_tat / processes.size() << endl;
}

void fcfs(vector<Process> processes) {
    int currentTime = 0;
    sort(processes.begin(), processes.end(), [](Process a, Process b) { return a.arrivalTime < b.arrivalTime; });

    for (auto& p : processes) {
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }
        currentTime += p.burstTime;
        p.completionTime = currentTime;
        p.turnAroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnAroundTime - p.burstTime;
    }

    cout << "FCFS Scheduling\n";
    cout << "P.No\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for (auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.completionTime
             << "\t\t" << p.turnAroundTime << "\t\t\t" << p.waitingTime << endl;
    }
    calculateTimes(processes);
}

void sjf(vector<Process> processes) {
    int n = processes.size(), currentTime = 0, completed = 0;
    vector<bool> isCompleted(n, false);

    while (completed != n) {
        int idx = -1, minBurst = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurst) {
                minBurst = processes[i].burstTime;
                idx = i;
            }
        }
        if (idx != -1) {
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
            isCompleted[idx] = true;
            completed++;
        } else {
            currentTime++;
        }
    }

    cout << "SJF Scheduling\n";
    cout << "P.No\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for (auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.completionTime
             << "\t\t" << p.turnAroundTime << "\t\t\t" << p.waitingTime << endl;
    }
    calculateTimes(processes);
}

void srtf(vector<Process> processes) {
    int n = processes.size(), currentTime = 0, completed = 0;
    for (auto& p : processes) p.remainingTime = p.burstTime;
    vector<bool> isCompleted(n, false);

    while (completed != n) {
        int idx = -1, minRemaining = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime < minRemaining) {
                minRemaining = processes[i].remainingTime;
                idx = i;
            }
        }
        if (idx != -1) {
            processes[idx].remainingTime--;
            currentTime++;
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
                isCompleted[idx] = true;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    cout << "SRTF Scheduling\n";
    cout << "P.No\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for (auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.completionTime
             << "\t\t" << p.turnAroundTime << "\t\t\t" << p.waitingTime << endl;
    }
    calculateTimes(processes);
}

int main() {
    int n, choice;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    cout << "Select scheduling algorithm:\n1. FCFS\n2. SJF\n3. SRTF\n";
    cin >> choice;

    switch (choice) {
        case 1:
            fcfs(processes);
            break;
        case 2:
            sjf(processes);
            break;
        case 3:
            srtf(processes);
            break;
        default:
            cout << "Invalid choice\n";
    }

    return 0;
}
