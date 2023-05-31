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

using namespace std;

struct process {
	char* name;
	int process_id;
	int activity_status;
	int cpuBurst;
	int base_register;
	int limit_register;
	int process_type;
	int num_files;
	int priority;
	int checksum;
};

struct CPU {
	int algo;
	vector<process> pLoad;
};

vector<CPU> cpuV;
vector<process> processV;

void FCFS(int index) {



}

void RR(int index) {



}

void SJF(int index) {



}

void PRIO(int index) {



}

void* CPU(void* ID) {

	int cpu_num = (int)(long)ID;
	fflush(stdout);



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
	}

	int size = sizeof(argv) / sizeof(argv[0]);

	int(i = 3; i < size; i++) {

		

		i++;



	}

}