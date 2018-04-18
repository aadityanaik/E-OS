#include <iostream>
#include "ProcessManagementModule.hpp"
using namespace std;

void roundRobin();		//implementation of scheduling algorithm;
bool memoryAvl();		//check if main memory available  creating process;

int process::createProcess() {
	int ret_flag = -1;
	/*if (memoryAvl()) {
		process newProcess;
		newProcess.pid = process_count;
		newProcess.size = 2;		//temporary default;
		newProcess.pstate = 0;		//defaults to '0' -> ready;
		newProcess.isComplete = false;
		ret_flag = newProcess.pid;
		process_count++;
		return ret_flag;
		
		//TODO: Look for contiguous memory blocks and assign memoryBlockStartFrom;
	} else {
		//process not created;
		return ret_flag;
	}*/
	
}

int main() {
	cout << "Hello, miniOS!" << endl;
}

