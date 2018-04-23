#include "fat_table.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

FAT_Table::FAT_Table()
{
}

void FAT_Table::make_table(FileStructure file)
{
	int start = 0;

	for (std::vector<File>::iterator iter = fat.begin(); iter < fat.end(); iter++) {
		if (file.getName() == iter->structure.getName()) {
			fat.erase(iter);
			break;
		}
	}

	std::sort(fat.begin(), fat.end());

	shiftFiles();

	if (fat.size() > 0) {
		File lastFile = *(fat.end() - 1);
		start = lastFile.start + lastFile.structure.getSize();
	}
	File newFile;
	newFile.start = start;
	newFile.structure = file;

	fat.push_back(newFile);

    std::ofstream fat_table_file("FAT_TABLE.txt");           //FAT_TABLE.csv must exist
    if(fat_table_file.is_open()) {
        fat_table_file << "\nFile" << "\t\tStart" << "\t\tSize" << std::endl;
		for (File file : fat) {
			fat_table_file << "\n" << file.structure.getName() << "\t\t" << file.start << "\t\t" << file.structure.getSize() << std::endl;
		}
    }
    fat_table_file.close();
}

void FAT_Table::shiftFiles() {
	if (fat.size() > 0) {
		if (fat[0].start != 0) {
			fat[0].start = 0;
		}
	}

	for (int i = 0; i < ((int) fat.size()) - 1; i++) {
		std::cout << "CRAP " << i <<" " << fat.size() << " " << ((fat.size() - 1)) <<"\n";
		if (fat[i].start + fat[i].structure.getSize() != fat[i + 1].start) {
			fat[i + 1].start = fat[i].start + fat[i].structure.getSize();
		}
	}
}

std::string FAT_Table::display_fat_table()
{
    std::ifstream fat_table_file("FAT_TABLE.txt");

    std::string fat_row;
    std::string fat_table = "";

    if(fat_table_file.is_open())
    {
        while(!fat_table_file.eof())
        {
			getline(fat_table_file, fat_row);
			fat_table += fat_row + "\n";
        }
    }
    fat_table_file.close();
    return fat_table;
}

std::string FAT_Table::appendFile(std::string filename, std::string updatedData) {
	for (int i = 0; i < fat.size(); i++) {
		if (fat[i].structure.getName() == filename) {
			fat[i].structure.appendFile(filename, updatedData);
			shiftFiles();
			std::ofstream fat_table_file("FAT_TABLE.txt");           //FAT_TABLE.csv must exist
			if (fat_table_file.is_open()) {
				fat_table_file << "\nFile" << "\t\tStart" << "\t\tSize" << std::endl;
				for (File file : fat) {
					fat_table_file << "\n" << file.structure.getName() << "\t\t" << file.start << "\t\t" << file.structure.getSize() << std::endl;
				}
			}
			fat_table_file.close();
			return "Successfully appended";
		}
	}

	return "No file of the name found";
}

std::string FAT_Table::deleteFile(std::string filename) {
	for (std::vector<File>::iterator iter = fat.begin(); iter < fat.end(); iter++) {
		if (iter->structure.getName() == filename) {
			if (iter->structure.deleteFile(filename)) {
				fat.erase(iter);
				std::sort(fat.begin(), fat.end());
				shiftFiles();
				std::ofstream fat_table_file("FAT_TABLE.txt");           //FAT_TABLE.csv must exist
				if (fat_table_file.is_open()) {
					fat_table_file << "\nFile" << "\t\tStart" << "\t\tSize" << std::endl;
					for (File file : fat) {
						fat_table_file << "\n" << file.structure.getName() << "\t\t" << file.start << "\t\t" << file.structure.getSize() << std::endl;
					}
				}
				fat_table_file.close();
				return "Deleted";
			}
			else {
				return "No such file";
			}
		}
	}

	return "No such file";
}

void FAT_Table::initFAT() {
	std::ifstream fat_table_file("FAT_TABLE.txt");

	if (fat_table_file.is_open())
	{
		std::string dummystring;
		do {
			std::getline(fat_table_file, dummystring);
		} while (dummystring == "");
		while (!fat_table_file.eof())
		{
			std::string filename;
			int start, filesize;
			fat_table_file >> filename >> start >> filesize;
			File file;
			file.start = start;
			file.structure = FileStructure(filename, filesize);
			file.structure.readFile(filename);
			fat.push_back(file);			
		}
	}
	fat_table_file.close();
	if(fat.size() > 0)
		fat.erase(fat.end() - 1);
}

std::string FAT_Table::ls_command()
{
	std::string listFiles;

	for (File file : fat) {
		listFiles += file.structure.getName() + "\n";
	}

    return listFiles;
}
