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
			processes.push_back(p);
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
					response.append("Process P" + processes[i].name + " was completed at t = " + to_string(time_elapsed) + ".\nIt waited for " + to_string(wt[i]) + " seconds.\n");
				}
			}
		}
		if (done == true) break;
	}
	return response;
}

std::string createProcess(int commd_code, string* args, int no_of_args) {
    string response = "-1";

    if (commd_code == -1) {             //-1 round-robin
        response = round_robin(args, no_of_args);
    } else if (commd_code == 1) {       //1 ls
        response = "Return output of ls";
    } else if (commd_code == 2) {       //2 display FAT
        //response = ft.display_fat_table();
    } else if (commd_code == 3) {       //3 read file
        response = fs.readFile(args[0]);
    } else if (commd_code == 4) {       //4 append file
		std::string arg2 = "";
		for (int i = 1; i < no_of_args; i++) {
			arg2 += args[i] + " ";
		}
	   response = fs.appendFile(args[0], arg2);
    } else if (commd_code = 5) {        //5 write file
        response = memmgmt::displayPAT();
    } else if (commd_code == 6) {       //6 Add process
        Process p;
        p.p_name = args[0];
        p.p_size = stoi(args[1]);
        updatePAT(p);
        response = "Process " + p.p_name + " created; occupies " + to_string(p.p_size) + " blocks of memory.";
    } else if (commd_code == 7) {       //7 Delete process and run compaction
        string p_name = arg[0];
        memmgmt::deleteProcessfromPAT(p_name);
        memmgmt::compactionPAT();
        response = "Removed process " + p_name "from memory. Post compaction memory size is " + to_string(memmgmt::spaceOccupiedProcess()) + " blocks";
    }
    return response;
}
