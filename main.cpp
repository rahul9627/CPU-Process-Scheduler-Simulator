#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <limits>
#include <iomanip>

// Configuration constants
const int QUANTUM = 4;                    // Time quantum for Round Robin algorithm
const int DEFAULT_PROCESS_COUNT = 10;     // Default number of processes to generate
const int MAX_BURST_TIME = 20;            // Maximum burst time for random generation
const int MIN_BURST_TIME = 1;             // Minimum burst time for random generation
const int MAX_PRIORITY = 3;               // Maximum priority level
const int MIN_PRIORITY = 1;               // Minimum priority level
const int NUM_QUEUES = 3;                 // Number of queues for multilevel scheduling

/**
 * Process class representing a process in the scheduling system
 * Contains process ID, burst time, and priority
 */
class Process {
public:
    int pid;           // Process ID
    int burst_time;    // CPU burst time required
    int priority;      // Process priority (lower number = higher priority)

    Process(int pid, int burst_time, int priority)
        : pid(pid), burst_time(burst_time), priority(priority) {}
};

/**
 * Generates a vector of random processes for testing
 * @param num_processes Number of processes to generate
 * @return Vector of randomly generated processes
 */
std::vector<Process> generateProcesses(int num_processes) {
    srand(time(nullptr));
    std::vector<Process> processes;

    for (int i = 0; i < num_processes; i++) {
        int burst_time = rand() % (MAX_BURST_TIME - MIN_BURST_TIME + 1) + MIN_BURST_TIME;
        int priority = rand() % (MAX_PRIORITY - MIN_PRIORITY + 1) + MIN_PRIORITY;
        processes.emplace_back(i, burst_time, priority);
    }

    return processes;
}

/**
 * Displays all processes in a formatted table
 * @param processes Vector of processes to display
 */
void displayProcesses(const std::vector<Process>& processes) {
    int N = processes.size();
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "PROCESS LIST (" << N << " processes)" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(8) << "ID" << std::setw(12) << "Burst Time" << std::setw(12) << "Priority" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int i = 0; i < N; i++) {
        std::cout << std::setw(8) << processes[i].pid 
                  << std::setw(12) << processes[i].burst_time 
                  << std::setw(12) << processes[i].priority << std::endl;
    }
    std::cout << std::string(50, '=') << std::endl;
}

/**
 * Calculates the total burst time of all processes
 * @param processes Vector of processes
 * @return Total burst time
 */
double total_burst_time(const std::vector<Process>& processes) {
    double total_burst_time = 0;
    for (const auto& process : processes) {
        total_burst_time += process.burst_time;
    }
    return total_burst_time;
}

/**
 * First Come First Served (FCFS) Scheduling Algorithm
 * Processes are executed in the order they arrive
 * @param processes Vector of processes to schedule
 * @return Average waiting time
 */
double first_come_first_served(const std::vector<Process>& processes) {
    int N = processes.size();
    std::vector<int> waiting_time(N, 0);
    std::vector<int> turnaround_time(N, 0);

    // Calculate waiting time for each process
    for (int i = 1; i < N; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < N; i++) {
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }

    // Calculate average waiting time
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
    for (int i = 0; i < N; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= N;
    avg_turnaround_time /= N;

    // Display scheduling results
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "FIRST COME FIRST SERVED (FCFS) SCHEDULING" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << std::setw(8) << "Process" << std::setw(12) << "Burst Time" 
              << std::setw(12) << "Priority" << std::setw(15) << "Waiting Time" 
              << std::setw(18) << "Turnaround Time" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(8) << processes[i].pid 
                  << std::setw(12) << processes[i].burst_time
                  << std::setw(12) << processes[i].priority
                  << std::setw(15) << waiting_time[i]
                  << std::setw(18) << turnaround_time[i] << std::endl;
    }
    
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Average Waiting Time: " << std::fixed << std::setprecision(2) << avg_waiting_time << std::endl;
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << avg_turnaround_time << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return avg_waiting_time;
}

/**
 * Comparison function for sorting processes by burst time
 */
bool compareByBurstTime(const Process& a, const Process& b) {
    return a.burst_time < b.burst_time;
}

/**
 * Shortest Job First (SJF) Scheduling Algorithm
 * Processes with shortest burst time are executed first
 * @param processes Vector of processes to schedule
 * @return Average waiting time
 */
double shortest_job_first(const std::vector<Process>& processes) {
    int N = processes.size();
    // Create a copy of the processes vector for sorting
    std::vector<Process> processes_copy = processes;

    // Sort processes by shortest burst time
    std::sort(processes_copy.begin(), processes_copy.end(), compareByBurstTime);

    std::vector<int> waiting_time(N, 0);
    std::vector<int> turnaround_time(N, 0);

    // Calculate waiting time for each process
    for (int i = 1; i < N; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes_copy[i - 1].burst_time;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < N; i++) {
        turnaround_time[i] = waiting_time[i] + processes_copy[i].burst_time;
    }

    // Calculate average waiting time
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
    for (int i = 0; i < N; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= N;
    avg_turnaround_time /= N;

    // Display scheduling results
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "SHORTEST JOB FIRST (SJF) SCHEDULING" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << std::setw(8) << "Process" << std::setw(12) << "Burst Time" 
              << std::setw(12) << "Priority" << std::setw(15) << "Waiting Time" 
              << std::setw(18) << "Turnaround Time" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(8) << processes_copy[i].pid 
                  << std::setw(12) << processes_copy[i].burst_time
                  << std::setw(12) << processes_copy[i].priority
                  << std::setw(15) << waiting_time[i]
                  << std::setw(18) << turnaround_time[i] << std::endl;
    }
    
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Average Waiting Time: " << std::fixed << std::setprecision(2) << avg_waiting_time << std::endl;
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << avg_turnaround_time << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return avg_waiting_time;
}

/**
 * Priority Scheduling Algorithm
 * Processes are executed based on priority (lower number = higher priority)
 * @param processes Vector of processes to schedule
 * @return Average waiting time
 */
double priority_scheduling(const std::vector<Process>& processes) {
    int N = processes.size();
    // Create a copy of the processes vector for sorting
    std::vector<Process> processes_copy = processes;

    // Sort processes by priority (lower number = higher priority)
    std::sort(processes_copy.begin(), processes_copy.end(), [](const Process& a, const Process& b) {
        return a.priority < b.priority;
    });

    std::vector<int> waiting_time(N, 0);
    std::vector<int> turnaround_time(N, 0);

    // Calculate waiting time for each process
    for (int i = 1; i < N; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes_copy[i - 1].burst_time;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < N; i++) {
        turnaround_time[i] = waiting_time[i] + processes_copy[i].burst_time;
    }

    // Calculate average waiting time
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
    for (int i = 0; i < N; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= N;
    avg_turnaround_time /= N;

    // Display scheduling results
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "PRIORITY SCHEDULING" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << std::setw(8) << "Process" << std::setw(12) << "Burst Time" 
              << std::setw(12) << "Priority" << std::setw(15) << "Waiting Time" 
              << std::setw(18) << "Turnaround Time" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(8) << processes_copy[i].pid 
                  << std::setw(12) << processes_copy[i].burst_time
                  << std::setw(12) << processes_copy[i].priority
                  << std::setw(15) << waiting_time[i]
                  << std::setw(18) << turnaround_time[i] << std::endl;
    }
    
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Average Waiting Time: " << std::fixed << std::setprecision(2) << avg_waiting_time << std::endl;
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << avg_turnaround_time << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return avg_waiting_time;
}

/**
 * Round Robin Scheduling Algorithm
 * Processes are executed in time slices (quantum) in circular order
 * @param processes Vector of processes to schedule
 * @return Average waiting time
 */
double round_robin(const std::vector<Process>& processes) {
    int N = processes.size();
    // Initialize waiting time and completion time for all processes
    std::vector<int> waiting_time(N, 0);
    std::vector<int> completion_time(N, 0);

    // Create a copy of burst times
    std::vector<int> remaining_burst_time(N);
    for (int i = 0; i < N; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    int time = 0; // Current system time

    // Continue executing processes in queue until all are completed
    while (true) {
        bool done = true;

        // Execute all processes one by one
        for (int i = 0; i < N; i++) {
            // If process burst time is greater than 0, process is not yet completed
            if (remaining_burst_time[i] > 0) {
                done = false; // There is still a process waiting

                if (remaining_burst_time[i] > QUANTUM) {
                    // Increase system time by quantum
                    time += QUANTUM;

                    // Decrease process burst time by quantum
                    remaining_burst_time[i] -= QUANTUM;
                } else {
                    // Increase system time by remaining burst time of process
                    time += remaining_burst_time[i];

                    // Waiting time is system time minus process burst time
                    waiting_time[i] = time - processes[i].burst_time;
                    completion_time[i] = time;

                    // Remaining burst time of process becomes 0
                    remaining_burst_time[i] = 0;
                }
            }
        }

        // If all processes are completed
        if (done == true)
            break;
    }

    // Calculate turnaround time for each process
    std::vector<int> turnaround_time(N);
    for (int i = 0; i < N; i++) {
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }

    // Calculate average waiting time
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
    for (int i = 0; i < N; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= N;
    avg_turnaround_time /= N;

    // Display scheduling results
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "ROUND ROBIN SCHEDULING (Quantum = " << QUANTUM << ")" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << std::setw(8) << "Process" << std::setw(12) << "Burst Time" 
              << std::setw(12) << "Priority" << std::setw(15) << "Waiting Time" 
              << std::setw(18) << "Turnaround Time" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(8) << processes[i].pid 
                  << std::setw(12) << processes[i].burst_time
                  << std::setw(12) << processes[i].priority
                  << std::setw(15) << waiting_time[i]
                  << std::setw(18) << turnaround_time[i] << std::endl;
    }
    
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Average Waiting Time: " << std::fixed << std::setprecision(2) << avg_waiting_time << std::endl;
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << avg_turnaround_time << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return avg_waiting_time;
}

/**
 * Multilevel Queue Scheduling Algorithm
 * Processes are distributed into different queues and each queue uses a different scheduling algorithm
 * @param processes Vector of processes to schedule
 * @return Average waiting time
 */
double multilevel_queue_scheduling(const std::vector<Process>& processes) {
    int N = processes.size();
    std::vector<std::vector<Process>> queues(NUM_QUEUES); // Create 3 queues

    // Randomly distribute processes into queues
    srand(time(nullptr)); // Set seed based on system time
    for (const auto& process : processes) {
        int queue_number = rand() % NUM_QUEUES; // Generate random number between 0 and 2
        queues[queue_number].push_back(process); // Add process to queue
    }

    // Execute processes in each queue using different scheduling algorithms
    // Queue 0: Round Robin
    // Queue 1: First Come First Served (FCFS)
    // Queue 2: Shortest Job First (SJF)
    
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "MULTILEVEL QUEUE SCHEDULING" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    std::cout << "\nQueue 0: Round Robin (Quantum = " << QUANTUM << ")" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    double avg_waiting_time_0 = 0;
    if (!queues[0].empty()) {
        avg_waiting_time_0 = round_robin(queues[0]);
    } else {
        std::cout << "No processes in Queue 0" << std::endl;
    }
    double total_burst_time_0 = total_burst_time(queues[0]);
    
    std::cout << "\nQueue 1: First Come First Served (FCFS)" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    double avg_waiting_time_1 = 0;
    if (!queues[1].empty()) {
        avg_waiting_time_1 = first_come_first_served(queues[1]);
        // Add waiting time from previous queue
        avg_waiting_time_1 += total_burst_time_0;
        std::cout << "Average Waiting Time (including Queue 0): " << std::fixed << std::setprecision(2) << avg_waiting_time_1 << std::endl;
    } else {
        std::cout << "No processes in Queue 1" << std::endl;
    }
    double total_burst_time_1 = total_burst_time(queues[1]);
    
    std::cout << "\nQueue 2: Shortest Job First (SJF)" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    double avg_waiting_time_2 = 0;
    if (!queues[2].empty()) {
        avg_waiting_time_2 = shortest_job_first(queues[2]);
        // Add waiting time from previous queues
        avg_waiting_time_2 += total_burst_time_0 + total_burst_time_1;
        std::cout << "Average Waiting Time (including Queues 0 & 1): " << std::fixed << std::setprecision(2) << avg_waiting_time_2 << std::endl;
    } else {
        std::cout << "No processes in Queue 2" << std::endl;
    }
    
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "MULTILEVEL QUEUE SUMMARY" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "Queue 0 (Round Robin): " << queues[0].size() << " processes" << std::endl;
    std::cout << "Queue 1 (FCFS): " << queues[1].size() << " processes" << std::endl;
    std::cout << "Queue 2 (SJF): " << queues[2].size() << " processes" << std::endl;
    
    double total_waiting_time = avg_waiting_time_0 + avg_waiting_time_1 + avg_waiting_time_2;
    double avg_waiting_time = total_waiting_time / NUM_QUEUES;
    std::cout << "Overall Average Waiting Time: " << std::fixed << std::setprecision(2) << avg_waiting_time << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    return avg_waiting_time;
}

/**
 * Main function - Interactive CPU Scheduling Simulator
 * Provides a menu-driven interface to test different scheduling algorithms
 */
int main() {
    srand(time(nullptr));

    std::cout << std::string(80, '=') << std::endl;
    std::cout << "                    CPU SCHEDULING ALGORITHM SIMULATOR" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "This program demonstrates various CPU scheduling algorithms used in operating systems." << std::endl;
    std::cout << "Processes are generated with random burst times and priorities for testing." << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    std::vector<Process> processes = generateProcesses(DEFAULT_PROCESS_COUNT);
    std::cout << "\nGenerated " << DEFAULT_PROCESS_COUNT << " random processes for testing." << std::endl;

    while(true) {
        int choice;
        do {
            std::cout << "\n" << std::string(60, '=') << std::endl;
            std::cout << "                    SCHEDULING ALGORITHMS MENU" << std::endl;
            std::cout << std::string(60, '=') << std::endl;
            std::cout << "1. First Come First Served (FCFS)" << std::endl;
            std::cout << "2. Shortest Job First (SJF)" << std::endl;
            std::cout << "3. Priority Scheduling" << std::endl;
            std::cout << "4. Round Robin (RR)" << std::endl;
            std::cout << "5. Multilevel Queue Scheduling" << std::endl;
            std::cout << std::string(60, '-') << std::endl;
            std::cout << "8. Display Current Processes" << std::endl;
            std::cout << "9. Generate New Processes" << std::endl;
            std::cout << "0. Exit Program" << std::endl;
            std::cout << std::string(60, '=') << std::endl;
            std::cout << "Enter your choice (0-9): ";
            std::cin >> choice;

            // Input validation
            if (std::cin.fail() || choice == 6 || choice == 7 || choice < 0 || choice > 9) {
                std::cout << "\nInvalid option! Please enter a valid choice (0-9)." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        } while (std::cin.fail() || choice == 6 || choice == 7 || choice < 0 || choice > 9);

        switch (choice) {
            case 1:
                first_come_first_served(processes);
                break;
            case 2:
                shortest_job_first(processes);
                break;
            case 3:
                priority_scheduling(processes);
                break;
            case 4:
                round_robin(processes);
                break;
            case 5:
                multilevel_queue_scheduling(processes);
                break;
            case 8:
                displayProcesses(processes);
                break;
            case 9:
                processes.clear();
                std::cout << "\nGenerating new processes... ";
                processes = generateProcesses(DEFAULT_PROCESS_COUNT);
                std::cout << "Done! Generated " << DEFAULT_PROCESS_COUNT << " new processes." << std::endl;
                break;
            case 0:
                std::cout << "\n" << std::string(60, '=') << std::endl;
                std::cout << "                    THANK YOU FOR USING THE SIMULATOR!" << std::endl;
                std::cout << "                    Goodbye!" << std::endl;
                std::cout << std::string(60, '=') << std::endl;
                return 0;
            default:
                std::cout << "\nInvalid option. Please try again." << std::endl;
        }
        
        // Pause before showing menu again
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
