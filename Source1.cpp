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

using namespace std;

int cpu_order 

void* CPU0(void* ID) {



}

void* CPU1(void* ID) {



}

void* CPU2(void* ID) {



}

void* CPU3(void* ID) {



}

int main(int argc, char* argv[]) {

	if (argc < 4 && (argc % 2) != 0) {

		cout << "Your command's format was incorrect. The correct format is:" << endl;
		cout << "./[executable_name] [filename.bin] [CPU] [Load_percentage]" << endl;
		cout << "The '[CPU] [Load_percentage]' portion is repeatable up to four times, one for each CPU (0-3)." << endl;
		cout << "The '[CPU]' portion must be a single-digit int, from 0 to 3. 'The [Load_percentage]' portion must be a double of less than one. All [Load_percentages] must add up to 1.0 or less." << endl;
		cout << "The file you use must be in the same directory as the program executable." << endl;
		cout << "For more information, please refer to the README.txt" << endl;

	}



}