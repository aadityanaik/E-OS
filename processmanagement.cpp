#include "filestructure.h"
#include "fat_table.h"
#include "filestructure.cpp"
#include "fat_table.cpp"
#include "memorymanagement.cpp"
#include "processmanagement.hpp"

using namespace std;

FAT_Table ft;
FileStructure fs;

std::string createProcess(int commd_code, string args[], int no_of_args) {
    string response = "-1";

    if (commd_code == -1) {
        response = round_robin(args, no_of_args);
    } else if (commd_code == 1) {
        response = "Return output of ls";
    } else if (commd_code == 2) {
        response = ft.display_fat_table();
    } else if (commd_code == 3) {
        response = fs.readFile(args[0]);
    } else if (commd_code == 4) {
       response = fs.appendFile(args[0], "appended_data");
    } else if (commd_code = 5) {
        response = displayPAT();
    }
    return response;
}

int main() {
    string args[] = {"P1", "2", "3", "P2", "4", "5", "P3", "6", "7"};
    cout<<createProcess(-1, args, 9);
}

std::string round_robin(string args[], int no_of_args) {
    /**
    /TODO: analyze arguments to create processes, assign them to memory and then execute round robin;
    **/
    string response;
    string p_name;
    int p_size, p_burst;
    if (no_of_args % 3 == 0) {      //check if the number of arguments is as expected;
        for (int i = 0; i < no_of_args; i += 3) {
            try {
                p_name = args[i];
                p_size = stoi(args[i+1]);
                p_burst = stoi(args[i+2]);
            }
            catch (exception &err) {
                response = "Invalid arguments!";
            }
            Process p(p_name, p_size, p_burst);
            updatePAT(p);
        }
    } else response = "Incorrect argument count.";

    // now all processes have been mapped to memory; commence round-robin;
    //array initialization;
    int wt[PAT.size()], rem_bt[PAT.size()];

    for (int i = 0; i < PAT.size(); i++) {
        wt[i] = 0;
        rem_bt[i] = PAT[i].p_burst;
    }

    int quantum = 2;
    int time_elapsed = 0;
    while (1) {
        bool done = true;
        for (int i = 0; i < PAT.size(); i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > quantum) {
                    time_elapsed += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    time_elapsed += rem_bt[i];
                    wt[i] = time_elapsed - PAT[i].p_burst;
                    rem_bt[i] = 0;
                    PAT[i].isComplete = true;
                    response.append("Process P" + PAT[i].name + " was completed at t = " + to_string(time_elapsed) + ".\nIt waited for " + to_string(wt[i]) + " seconds.\n");
                }
            }
        }
        if (done == true) break;
    }
    return response;
}
