# Bank Queue Simulation

This project simulates a queue system at a bank using C++. It generates a random number of customers (between 5 and 15), each with random arrival and service times, and computes key statistics such as waiting time, service time, idle time, and time in the system.

## 📌 Project Description

The simulation models how clients arrive at a bank and how they are served one after another. It calculates and displays the following:

- Arrival Time
- Service Begin Time
- Service End Time
- Idle Time (when the bank is not serving anyone)
- Waiting Time in Queue
- Time Spent in the System

In addition, it provides summary statistics such as:

- Average Waiting Time
- Average Time in System
- Maximum Service Time
- Number of Clients Who Waited

## ⚙️ Technologies Used

- C++
- STL: `vector`, `queue`, `random`, `iomanip`

## 🏗️ Structure

- **`Client` class**: Stores individual client data.
- **`Bank` class**: Simulates the system and processes all clients.
- **Random Generators**: Functions to simulate random arrival and service times using `Mersenne Twister`.

## 🔄 How it Works

1. A random number of clients is generated (between 5 and 15).
2. Each client is assigned:
   - A random arrival time (initial client starts between 0–3 mins, others arrive 1–5 mins later).
   - A random service time (1–5 mins).
3. The system calculates:
   - When each client starts and ends service.
   - If the server (bank teller) was idle.
   - How long each client waited.
   - How long each stayed in the system.

## ▶️ How to Run

Make sure you have a C++ compiler installed (e.g. `g++`, `clang++`), then run:

```bash
g++ -o bank_simulation main.cpp
./bank_simulation
```

## 📊 Sample Output
```bash
==========================================================================
| ID | Arrival | Service Begin | Service End | Idle Time | Wait | System |
==========================================================================
|  1 |   1.26  |       1.26     |     4.77     |   1.26     | 0.00 |  3.51 |
|  2 |   5.22  |       5.22     |     7.42     |   0.45     | 0.00 |  2.20 |
|  3 |   8.57  |       8.57     |    12.47     |   1.15     | 0.00 |  3.90 |
|  4 |  10.33  |      12.47     |    13.60     |   0.00     | 2.14 |  3.27 |
|  5 |  11.86  |      13.60     |    15.90     |   0.00     | 1.74 |  4.04 |
==========================================================================
Average Waiting Time: 0.78 minutes
Average Time In System: 3.38 minutes
Maximum Service Time: 3.90 minutes
Number of Clients Who Waited: 2 out of 5

