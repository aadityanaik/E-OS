#pragma once

#include "..\fileManagement\fat_table.h"
#include "..\fileManagement\filestructure.h"
#include "..\memorymanagement\memorymanagement.hpp"

std::string round_robin(std::string* args, int no_of_args);

void initFATTable();

std::string createProcess(int commd_code, std::string* args, int no_of_args);