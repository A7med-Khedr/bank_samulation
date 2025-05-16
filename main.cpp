#include <iostream>  // For input and output
#include <vector>    // For using dynamic array (to store multiple clients)
#include <queue>     // Included but not used in current version
#include <random>    // For generating random numbers
#include <iomanip>   // For formatted output (setw, setprecision, etc.)
using namespace std;

// Function to generate a random double number between [min, max]
double random_double(double min, double max) {
    static random_device rd;           // Random seed generator
    static mt19937 mt(rd());           // Mersenne Twister random number generator
    uniform_real_distribution<double> dist(min, max);
    return dist(mt);                   // Generate and return a random number
}

// Function to generate a random integer number between [min, max]
int random_integer(int min, int max) {
    static random_device rd;           // Random seed generator
    static mt19937 mt(rd());           // Mersenne Twister random number generator
    uniform_int_distribution<int> dist(min, max);
    return dist(mt);                   // Generate and return a random number
}

// Class to store details of a single client
class Client {
	private:
		double arrivalTime{};      // Time of arrival
		double serviceBegin{};     // Time service begins
		double serviceEnd{};       // Time service ends
		double idleTime{};         // Time server was idle before this client
		double waitInQueue{};      // Time client waited in queue
		double timeInSystem{};     // Total time client spent in the system

	public:
		// Setters and Getters for all attributes
		void setArrivalTime(double time) { arrivalTime = time; }
		double getArrivalTime() const { return arrivalTime; }

		void setServiceBegin(double time) { serviceBegin = time; }
		double getServiceBegin() const { return serviceBegin; }

		void setServiceEnd(double time) { serviceEnd = time; }
		double getServiceEnd() const { return serviceEnd; }

		void setIdleTime(double time) { idleTime = time; }
		double getIdleTime() const { return idleTime; }

		void setWaitInQueue(double time) { waitInQueue = time; }
		double getWaitInQueue() const { return waitInQueue; }

		void setTimeInSystem(double time) { timeInSystem = time; }
		double getTimeInSystem() const { return timeInSystem; }
};

// Class to simulate the bank system and handle multiple clients
class Bank {
	private:
		vector<Client> clients;    // Vector to store all clients
		int num_customers;         // Number of clients generated

	public:
		Bank() {
			// Random number of clients between 5 and 15
			num_customers = random_integer(5, 15);
			clients.resize(num_customers); // Resize the vector accordingly

			setClients();        // Set the arrival time for each client
			setServiceTimes();   // Calculate service begin/end and waiting times
			setIdleTimes();      // Calculate idle time for each client
		}

		// Generate arrival times for all clients
		void setClients() {
			double current_time = random_double(0, 3); // First client arrival
			clients[0].setArrivalTime(current_time);

			for (int i = 1; i < num_customers; ++i) {
				double delay = random_double(1, 5); // Time between arrivals
				current_time += delay;
				clients[i].setArrivalTime(current_time); // Set arrival for each client
			}
		}

		// Calculate service begin/end, waiting time, and time in system
		void setServiceTimes() {
			for (int i = 0; i < num_customers; ++i) {
				double service_time = random_double(1, 5); // Service duration

				double service_begin;
				if (i == 0) {
					// First client starts service at their arrival
					service_begin = clients[i].getArrivalTime();
				} else {
					// Client starts either when they arrive or when previous finishes
					service_begin = max(clients[i].getArrivalTime(), clients[i - 1].getServiceEnd());
				}

				double service_end = service_begin + service_time;
				double wait_in_queue = service_begin - clients[i].getArrivalTime();
				double time_in_system = service_end - clients[i].getArrivalTime();

				clients[i].setServiceBegin(service_begin);
				clients[i].setServiceEnd(service_end);
				clients[i].setWaitInQueue(wait_in_queue);
				clients[i].setTimeInSystem(time_in_system);
			}
		}

		// Calculate idle time between clients
		void setIdleTimes() {
			clients[0].setIdleTime(0); // First client has no idle time

			for (int i = 1; i < num_customers; ++i) {
				double idle_time = clients[i].getServiceBegin() - clients[i - 1].getServiceEnd();
				clients[i].setIdleTime(max(0.0, idle_time)); // If negative, set to 0
			}
		}

		// Calculate average waiting time of all clients
		double getAverageWaitingTime() const {
			double total_wait = 0;
			for (const auto& client : clients) {
				total_wait += client.getWaitInQueue();
			}
			return total_wait / num_customers;
		}

		// Calculate average time clients spend in the system
		double getAverageTimeInSystem() const {
			double total_time = 0;
			for (const auto& client : clients) {
				total_time += client.getTimeInSystem();
			}
			return total_time / num_customers;
		}

		// Get the maximum time taken to serve any client
		double getMaxServiceTime() const {
			double max_time = 0;
			for (const auto& client : clients) {
				double service_time = client.getServiceEnd() - client.getServiceBegin();
				if (service_time > max_time) {
					max_time = service_time;
				}
			}
			return max_time;
		}

		// Count how many clients had to wait in queue
		int getWaitedClientsCount() const {
			int count = 0;
			for (const auto& client : clients) {
				if (client.getWaitInQueue() > 0) {
					count++;
				}
			}
			return count;
		}

		// Print summary statistics
		void printStatistics() const {
			cout << "Average Waiting Time    : " << getAverageWaitingTime() << " minutes\n";
			cout << "Average Time In System  : " << getAverageTimeInSystem() << " minutes\n";
			cout << "Maximum Service Time    : " << getMaxServiceTime() << " minutes\n";
			cout << "Clients Who Waited      : " << getWaitedClientsCount() << " out of " << num_customers << "\n";
		}

		// Print detailed client table
		void printClients() const {
			cout << fixed << setprecision(2); // Set decimal precision to 2

			// Print table header
			cout << "==========================================================================\n";
			cout << "| ID | Arrival | Service Begin | Service End | Idle Time | Wait | System |\n";
			cout << "==========================================================================\n";

			// Print each client's data
			for (int i = 0; i < num_customers; ++i) {
				cout << "| "
					<< setw(2) << i + 1 << " | "
					<< setw(7) << clients[i].getArrivalTime() << " | "
					<< setw(13) << clients[i].getServiceBegin() << " | "
					<< setw(11) << clients[i].getServiceEnd() << " | "
					<< setw(9) << clients[i].getIdleTime() << " | "
					<< setw(5) << clients[i].getWaitInQueue() << " | "
					<< setw(6) << clients[i].getTimeInSystem() << " |\n";
			}

			// Print footer and statistics
			cout << "==========================================================================\n";
			printStatistics();
		}
};

// Entry point of the program
int main() {
    Bank bank;             // Create a bank object (clients are generated)
    bank.printClients();   // Print clients' data and statistics
    return 0;              // Program ends
}
