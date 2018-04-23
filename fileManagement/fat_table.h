#ifndef FAT_TABLE_H
#define FAT_TABLE_H
#include <string>
#include <vector>
#include "filestructure.h"

struct File {
	FileStructure structure;
	int start;

	bool operator < (File f2) {
		return start < f2.start;
	}
};

class FAT_Table
{
    public:
        FAT_Table();
        void make_table(FileStructure);
        std::string display_fat_table();
        std::string ls_command();
		void shiftFiles();
		void initFAT();
		std::string appendFile(std::string, std::string);
		std::string deleteFile(std::string);

    protected:

    private:
		std::vector<File> fat;
};

#endif // FAT_TABLE_H
