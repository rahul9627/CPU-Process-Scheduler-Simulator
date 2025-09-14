# CPU Process Scheduler Simulator

A comprehensive C++ program that simulates various CPU scheduling algorithms used in operating systems. This educational tool demonstrates how different scheduling strategies affect process execution and system performance.

## 🚀 Features

- **Multiple Scheduling Algorithms**: Implements 5 different CPU scheduling algorithms
- **Interactive Menu System**: User-friendly command-line interface
- **Random Process Generation**: Automatically generates test processes with random burst times and priorities
- **Performance Metrics**: Calculates and displays waiting time and turnaround time for each algorithm
- **Educational Focus**: Designed for learning and understanding operating system concepts

## 📋 Implemented Algorithms

### 1. First Come First Served (FCFS)
- Processes are executed in the order they arrive
- Non-preemptive scheduling
- Simple but may lead to convoy effect

### 2. Shortest Job First (SJF)
- Processes with shortest burst time are executed first
- Non-preemptive scheduling
- Optimal for minimizing average waiting time

### 3. Priority Scheduling
- Processes are executed based on priority (lower number = higher priority)
- Non-preemptive scheduling
- Useful for real-time systems

### 4. Round Robin (RR)
- Processes are executed in time slices (quantum) in circular order
- Preemptive scheduling
- Prevents starvation and provides fair CPU allocation

### 5. Multilevel Queue Scheduling
- Processes are distributed into different queues
- Each queue uses a different scheduling algorithm:
  - Queue 0: Round Robin
  - Queue 1: First Come First Served (FCFS)
  - Queue 2: Shortest Job First (SJF)

## 🛠️ Configuration

The program includes several configurable constants:

```cpp
const int QUANTUM = 4;                    // Time quantum for Round Robin
const int DEFAULT_PROCESS_COUNT = 10;     // Default number of processes
const int MAX_BURST_TIME = 20;            // Maximum burst time
const int MIN_BURST_TIME = 1;             // Minimum burst time
const int MAX_PRIORITY = 3;               // Maximum priority level
const int MIN_PRIORITY = 1;               // Minimum priority level
const int NUM_QUEUES = 3;                 // Number of queues for multilevel
```

## 🏃‍♂️ How to Run

### Prerequisites
- C++ compiler (g++, Visual Studio, etc.)
- Windows/Linux/macOS operating system

### Compilation and Execution

1. **Compile the program:**
   ```bash
   g++ main.cpp -o ProcessScheduler.exe
   ```

2. **Run the executable:**
   ```bash
   ./ProcessScheduler.exe
   ```

### Alternative (Windows)
```cmd
g++ main.cpp -o ProcessScheduler.exe
ProcessScheduler.exe
```

## 📖 Usage

1. **Start the program** - The simulator will generate 10 random processes automatically
2. **Choose an algorithm** from the interactive menu:
   - Press `1` for FCFS
   - Press `2` for SJF
   - Press `3` for Priority Scheduling
   - Press `4` for Round Robin
   - Press `5` for Multilevel Queue
3. **View results** - Each algorithm displays:
   - Process execution order
   - Individual waiting and turnaround times
   - Average waiting and turnaround times
4. **Additional options**:
   - Press `8` to display current processes
   - Press `9` to generate new random processes
   - Press `0` to exit

## 📊 Sample Output

```
============================================================
                    CPU SCHEDULING ALGORITHM SIMULATOR
============================================================
This program demonstrates various CPU scheduling algorithms used in operating systems.
Processes are generated with random burst times and priorities for testing.
============================================================

Generated 10 random processes for testing.

============================================================
                    SCHEDULING ALGORITHMS MENU
============================================================
1. First Come First Served (FCFS)
2. Shortest Job First (SJF)
3. Priority Scheduling
4. Round Robin (RR)
5. Multilevel Queue Scheduling
------------------------------------------------------------
8. Display Current Processes
9. Generate New Processes
0. Exit Program
============================================================
Enter your choice (0-9):
```

## 🎯 Educational Value

This simulator is perfect for:
- **Students** learning operating system concepts
- **Developers** understanding CPU scheduling
- **Interview preparation** for system design roles
- **Academic projects** and assignments

## 🔧 Technical Details

- **Language**: C++ (C++11 or later)
- **Dependencies**: Standard C++ library only
- **Platform**: Cross-platform (Windows, Linux, macOS)
- **Memory**: Efficient vector-based implementation
- **Randomization**: Uses `srand()` with time-based seed

## 📈 Performance Metrics

The simulator calculates and displays:
- **Waiting Time**: Time a process waits in the ready queue
- **Turnaround Time**: Total time from process arrival to completion
- **Average Metrics**: Overall system performance indicators

## 🤝 Contributing

Feel free to contribute to this project by:
- Adding new scheduling algorithms
- Improving the user interface
- Adding more detailed performance metrics
- Fixing bugs or improving code quality

## 📝 License

This project is open source and available for educational purposes.

## 🎓 Learning Resources

To better understand CPU scheduling algorithms, consider studying:
- Operating System textbooks (e.g., Silberschatz, Tanenbaum)
- Online courses on operating systems
- System design interview preparation materials

