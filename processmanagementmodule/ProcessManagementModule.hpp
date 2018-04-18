#pragma once

//global data members;
static int process_count = 0;

//global functions;
void roundRobin();

struct process {
	//data members;
	int pid;
	int size;
	int memoryBlockStartFrom;
	int pstate;
	bool isComplete;
	
	//functions;
	int createProcess();
};

