#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

struct process {
	string name;
	int process_id;
	int activity_status;
	int cpuBurst;
	int base_register;
	int limit_register;
	int process_type;
	int num_files;
	int priority;
	int checksum;
	int remainingBurst;
};

struct Mock_CPU {
	int algo;
	vector<process> pLoad;
};

vector<Mock_CPU> cpuV;
vector<process> processV;

void FCFS(int index) {

	Mock_CPU& current = cpuV[index];
	
	int avgWait = 0;

	for (int i = 0; i < current.pLoad.size(); i++) {

		cout << "attempting to locate next process" << endl;

		process& curProc = current.pLoad[i];

		int bursts = curProc.cpuBurst;

		cout << "attempting to snooze" << endl;

		this_thread::sleep_for(chrono::milliseconds(bursts));

		cout << "attempting to print results" << endl;

		cout << "FCFS: " << curProc.name << " process took " << to_string(bursts) << " milliseconds to execute." << endl;

		cout << "attemtping to add to avg wait time." << endl;

		if ((i + 1) != current.pLoad.size()) {

			avgWait += bursts;

		}

	}

	avgWait = avgWait / current.pLoad.size();

	cout << "CPU" << index << " running First-Come-First-Served Average Wait Time: " << to_string(avgWait) << " milliseconds " << endl;

}

void RR(int index) {

	Mock_CPU& current = cpuV[index];

	int avgWait = 0;

	int timeQuantam = 69;
	int totalProcesses = current.pLoad.size();
	int currentIndex = 0;

	while (totalProcesses > 0) {

		process& curProc = current.pLoad[currentIndex];

		int execTime = min(timeQuantam, curProc.remainingBurst);

		this_thread::sleep_for(chrono::milliseconds(execTime));

		curProc.remainingBurst -= execTime;

		if (curProc.remainingBurst <= 0) {

			cout << "Round Robin: " << curProc.name << " process took " << to_string(curProc.cpuBurst) << " milliseconds to execute." << endl;
			totalProcesses--;

		}

		currentIndex = (currentIndex + 1) % current.pLoad.size();

		if (totalProcesses != 0) {

			avgWait += execTime;

		}

	}

	avgWait = avgWait / current.pLoad.size();

	cout << "CPU" << index << " running Round-Robin Average Wait Time: " << to_string(avgWait) << " milliseconds " << endl;

}

void SJF(int index) {

	Mock_CPU& current = cpuV[index];

	int avgWait = 0;

	sort(current.pLoad.begin(), current.pLoad.end(), [](const process& a, const process& b) {
		return a.cpuBurst < b.cpuBurst;
	});

	for (int i = 0; i < current.pLoad.size(); i++) {

		process& curProc = current.pLoad[i];

		this_thread::sleep_for(chrono::milliseconds(curProc.cpuBurst));

		cout << "Shortest Job First: " << curProc.name << " process took " << to_string(curProc.cpuBurst) << " milliseconds to execute." << endl;

		if ((i + 1) != current.pLoad.size()) {

			avgWait += curProc.cpuBurst;

		}

	}

	avgWait = avgWait / current.pLoad.size();

	cout << "CPU" << index << " running Shortest-Job-First Average Wait Time: " << to_string(avgWait) << " milliseconds " << endl;

}

void PRIO(int index) {

	Mock_CPU& current = cpuV[index];

	int avgWait = 0;

	sort(current.pLoad.begin(), current.pLoad.end(), [](const process& a, const process& b) {
		return a.priority < b.priority;
		});

	for (int i = 0; i < current.pLoad.size(); i++) {

		process& curProc = current.pLoad[i];

		this_thread::sleep_for(chrono::milliseconds(curProc.cpuBurst));

		cout << "Priority Scheduling: " << curProc.name << " process took " << to_string(curProc.cpuBurst) << " milliseconds to execute." << endl;
		cout << curProc.name << " had a priority of " << to_string(curProc.priority) << "." << endl;

		if ((i + 1) != current.pLoad.size()) {

			avgWait += curProc.cpuBurst;

		}

	}

	avgWait = avgWait / current.pLoad.size();

	cout << "CPU" << index << " running Priority-Scheduling Average Wait Time: " << to_string(avgWait) << " milliseconds " << endl;

}

void* CPUs(void* ID) {

	int index = (int)(long)ID;

	if (index >= 0 && index < cpuV.size()) {
		
		Mock_CPU& curCPU = cpuV[index];

		if (curCPU.algo == 0) {

			FCFS(index);

		} else if (curCPU.algo == 1) {

			RR(index);

		} else if (curCPU.algo == 2) {

			SJF(index);

		} else if (curCPU.algo == 3) {

			PRIO(index);

		} else {

			cout << "Not a valid CPU type." << endl;
			cout << "Please use a CPU type from 0-3." << endl;
			cout << "Stopping this CPU..." << endl;
			return (void*)1;
		}

	}

	fflush(stdout);

	return (void*)0;
}

int main(int argc, char* argv[]) {

	if (argc < 4 && (argc % 2) != 0) {

		cout << "Your command's format was incorrect. The correct format is:" << endl;
		cout << "./[executable_name] [filename.bin] [CPU] [Load_percentage]" << endl;
		cout << "The '[CPU] [Load_percentage]' portion is repeatable up to four times, one for each CPU (0-3)." << endl;
		cout << "The '[CPU]' portion must be a single-digit int, from 0 to 3. 'The [Load_percentage]' portion must be a double of less than one. All [Load_percentages] must add up to 1.0 or less." << endl;
		cout << "The file you use must be in the same directory as the program executable." << endl;
		cout << "For more information, please refer to the README.txt" << endl;
		return 1;

	}

	ifstream file(argv[1], ios::binary);
	if (!file) {
		cout << "Failed to open file. Please ensure that the file is in the same folder as the program." << endl;
		cout << "Make sure to also include '.bin' at the end of the file name when typing in the command." << endl;
		cout << "For more information, please refer to the README.txt" << endl;
		return 1;
	}

	file.seekg(0, ios::end);
	streampos fileSize = file.tellg();
	file.seekg(0, ios::beg);

	double totalLoad = 0.0;

	for (int i = 3; i < argc; i++) {

		try {

			totalLoad += stod(argv[i]);

			i++;

		} catch (const exception& e) {

			cout << "Failed to parse double." << endl; 
			cout << "Remember to type a percentage allocation as something like '0._'.More than one digit is allowed after the '0.'." << endl;
			cout << "For more information, please refer to the README.txt" << endl;
			file.close();
			return 1;

		}
	}

	if (abs(totalLoad - 1.0) < 0.0000001) {

		cout << "Total percentage is equal to 1.0. Proceeding with CPU distribution" << endl;

	} else {

		cout << "Total percentage is not equal to 1.0. You must allocate all processes to a CPU." << endl;
		cout << "Remember to type a percentage allocation as something like '0._'. More than one digit is allowed after the '0.'." << endl;
		cout << "For more information, please refer to the README.txt" << endl;
		file.close();
		return 1;

	}

	int bitNav = 0;
	int totalProcesses = 0;

	while (bitNav < fileSize) {

		try {

			char nameBuffer[32];
			file.read(nameBuffer, 32);
			string procName(nameBuffer, 32);

			char idBuffer[4];
			file.read(idBuffer, 4);
			int id = *reinterpret_cast<int*>(idBuffer);

			char activityBuffer[1];
			file.read(activityBuffer, 1);
			int activity = *reinterpret_cast<int*>(activityBuffer);

			char burstBuffer[4];
			file.read(burstBuffer, 4);
			int burst = *reinterpret_cast<int*>(burstBuffer);

			char baseBuffer[4];
			file.read(baseBuffer, 4);
			int base = *reinterpret_cast<int*>(baseBuffer);

			char limitBuffer[8];
			file.read(limitBuffer, 8);
			int limit = *reinterpret_cast<int*>(limitBuffer);

			char typeBuffer[1];
			file.read(typeBuffer, 1);
			int type = *reinterpret_cast<int*>(typeBuffer);

			char numBuffer[4];
			file.read(numBuffer, 4);
			int num = *reinterpret_cast<int*>(numBuffer);

			char priorityBuffer[1];
			file.read(priorityBuffer, 1);
			int priority = *reinterpret_cast<int*>(priorityBuffer);

			char checksumBuffer[4];
			file.read(checksumBuffer, 4);
			int check = *reinterpret_cast<int*>(checksumBuffer);

			bitNav += 63;
			totalProcesses += 1;

			processV.push_back({ procName, id, activity, burst, base, limit, type, num, priority, check, burst });

		} catch (const exception& e) {

			cout << "Failed to read file correctly." << endl;
			cout << "Make sure the file you've chosen is a file of type .bin and that it is formatted correctly according to the rubric for Lab5." << endl;
			cout << "For more information, please refer to the README.txt (which includes the binary file layout)." << endl;
			file.close();
			return 1;

		}

	}

	file.close();

	cout << "The total amount of processes is " << to_string(totalProcesses) << "." << endl;

	int index = 0;
	int totalCPUs = 0;

	for (int i = 2; i < argc; i++) {

		try {

			int amount = static_cast<int>(floor(stod(argv[i+1]) * totalProcesses));

			vector<process> allocatedProcesses(processV.begin() + index, processV.begin() + index + amount);

			Mock_CPU nCpu;
			nCpu.algo = stoi(argv[i]);
			nCpu.pLoad = allocatedProcesses;
			cpuV.push_back(nCpu);

			totalCPUs += 1;

			i++;

			index = index + amount;

			if (nCpu.algo < 0 || nCpu.algo > 3) {

				cout << "CPUs were not between 0-3." << endl;
				cout << "Make sure that the CPU is an integer 0-3. Unlike the Load_Percentage, the CPU cannot have a decimal." << endl;
				cout << "For more information, please refer to the README.txt." << endl;
				return 1;

			}

		} catch (const exception& e) {

			cout << "CPUs were typed wrong." << endl;
			cout << "Make sure that the CPU is an integer 0-3. Unlike the Load_Percentage, the CPU cannot have a decimal." << endl;
			cout << "For more information, please refer to the README.txt." << endl;
			return 1;

		}
	}

	if (index != totalProcesses) {

		while (index < totalProcesses) {

			Mock_CPU& cpu0 = cpuV.front();

			cpu0.pLoad.push_back(processV[index]);

			index++;

		}

	}

	pthread_t cpuThreads[totalCPUs];

	for (int i = 0; i < totalProcesses; i++) {

		pthread_create(&cpuThreads[i], 0, CPUs, (void*)(long)i);

	}

	cout << "Tieing Threads" << endl;

	for (long i = 0; i == totalProcesses; i++) {

		pthread_join(cpuThreads[i], NULL);

	}

	return 0;

}