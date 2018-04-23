#include "processmanagement.hpp"
#include "../memorymanagement/memorymanagement.hpp"

using namespace std;


FAT_Table ft;
FileStructure fs;

std::string round_robin(string* args, int no_of_args) {
	/**
	/TODO: analyze arguments to create processes, assign them to memory and then execute round robin;
	**/
	string response;
	string p_name;
	int p_size, p_burst;
	std::vector<memmgmt::Process> processes;
	if (no_of_args % 3 == 0) {      //check if the number of arguments is as expected;
		for (int i = 0; i < no_of_args; i += 3) {
			try {
				p_name = args[i];
				p_size = stoi(args[i + 1]);
				p_burst = stoi(args[i + 2]);
			}
			catch (exception &err) {
				return "Invalid arguments!";
			}
			memmgmt::Process p(p_name, p_size, p_burst);
			if (std::find(processes.begin(), processes.end(), p) == processes.end()) {
				processes.push_back(p);
			}
			else {
				return "Duplicate process names are not allowed.";
			}
		}
	}
	else return "Incorrect argument count.";

	// now all processes have been mapped to memory; commence round-robin;
	//array initialization;
	int* wt = new int[processes.size()];
	int* rem_bt = new int[processes.size()];

	for (int i = 0; i < processes.size(); i++) {
		wt[i] = 0;
		rem_bt[i] = processes[i].p_burst;
	}

	int quantum = 2;
	int time_elapsed = 0;
	while (1) {
		bool done = true;
		for (int i = 0; i < processes.size(); i++) {
			if (rem_bt[i] > 0) {
				done = false;
				if (rem_bt[i] > quantum) {
					time_elapsed += quantum;
					rem_bt[i] -= quantum;
				}
				else {
					time_elapsed += rem_bt[i];
					wt[i] = time_elapsed - processes[i].p_burst;
					rem_bt[i] = 0;
					processes[i].isComplete = true;
					response.append("Quantum = 5;\nProcess P" + processes[i].name + " completed at t = " + to_string(time_elapsed) + ".\nIt waited for " + to_string(wt[i]) + " seconds.\n");
				}
			}
		}
		if (done == true) break;
	}
	return response;
}

void initFATTable() {
	ft.initFAT();
}

std::string createProcess(int commd_code, string* args, int no_of_args) {
    string response = "-1";

    if (commd_code == -1) {             //-1 round-robin
        response = round_robin(args, no_of_args);
    } else if (commd_code == 1) {
        response = ft.ls_command();
    } else if (commd_code == 2) {
        response = ft.display_fat_table();
    } 
    else if (commd_code == 3) {       //3 read file
        response = fs.readFile(args[0]);
    } else if (commd_code == 4) {       //4 write file
		std::string arg2 = "";
		for (int i = 1; i < no_of_args; i++) {
			arg2 += args[i] + " ";
		}
	   response = fs.addFile(args[0], arg2);
	   ft.make_table(fs);
    } else if (commd_code == 5) { // append file
		std::string arg2 = "";
		for (int i = 1; i < no_of_args; i++) {
			arg2 += args[i] + " ";
		}
		response = ft.appendFile(args[0], arg2);
		ft.shiftFiles();
	}
	else if (commd_code == 6) { // remove file
		if (no_of_args > 1) {
			return "\'rm\': Too many arguments";
		} else if (no_of_args  == 0) {
			return "\'rm\': Must pass file name as argument";
		}
		else {
			response = ft.deleteFile(args[0]);
		}
	}
	else if (commd_code == 7) {       // Add process
		if (no_of_args > 2) {
			return "'addprc': too many arguments";
		}
		else if (no_of_args < 2) {
			return "'addprc': too few arguments";
		}
		try {
			memmgmt::Process p(args[0], stoi(args[1]), 0);
			if (updatePAT(p)) {
				response = "Process " + p.name + " created; occupies " + to_string(p.size) + " blocks of memory.";
			}
			else {
				response = "Not enough space";
			}
		}
		catch (...) {
			return args[1] + ": invalid input";
		}
    } else if (commd_code == 8) {       // Delete process and run compaction
        string p_name = args[0];
		if (memmgmt::deleteProcessfromPAT(p_name)) {
			memmgmt::compactionPAT();
			response = "Removed process " + p_name + " from memory. Post compaction memory size is " + to_string(memmgmt::spaceOccupiedProcess()) + " blocks";
		}
		else {
			response = "Could not find process\n" + memmgmt::displayPAT();
		}
	}
	else if (commd_code == 9) {
		// show pat
		return memmgmt::displayPAT();
	}
    return response;
}
