#pragma once

#include <vector>
#include <string>

struct Process {
	string name;
	int size;
	int start_block;
	int p_burst;
	bool isComplete;

	Process(std::string p_name, int p_size, int p_burst);
};

struct File {
	string name;
	int size;
	int start_block;
};


std::vector<File> FAT;

std::vector <Process> PAT;

int spaceOccupiedProcess();

bool updatePAT(Process p);

bool deleteProcessfromPAT(std::string p_name);

std::string displayPAT();

File takeFileParamters(std::string f_name, int f_size);

int spaceOccupiedFile();

bool updateFAT(File f);

bool deleteFilefromFAT(std::string f_name);

std::string displayFAT();

float percentageSpace();

void compactionPAT();

void compactionFAT();