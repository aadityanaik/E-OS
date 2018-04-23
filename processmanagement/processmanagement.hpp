#pragma once

#include "..\fileManagement\fat_table.h"
#include "..\fileManagement\filestructure.h"

FAT_Table ft;
FileStructure fs;

std::string round_robin(std::string args[], int no_of_args);

std::string createProcess(int commd_code, std::string args[], int no_of_args);