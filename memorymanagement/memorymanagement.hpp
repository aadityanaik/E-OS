#pragma once

#include <vector>
#include <string>

namespace memmgmt {

	struct Process {
		std::string name;
		int size;
		int start_block;
		int p_burst;
		bool isComplete;

		Process(std::string p_name, int p_size, int p_burst);

		bool operator == (Process p) {
			return name == p.name;
		}
	};

	struct File {
		std::string name;
		int size;
		int start_block;
	};

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
}