#include "fat_table.h"
#include <fstream>
#include <iostream>

FAT_Table::FAT_Table()
{
    fileName = "";
    start = 0;
    fileSize = 0;
}

void FAT_Table::make_table(std::string file_name, unsigned int start, unsigned int file_size)
{
    std::ofstream fat_table_file("FAT_TABLE.csv", std::ios::app);           //FAT_TABLE.csv must exist
    if(fat_table_file.is_open()) {
        fat_table_file << fileName << "," << start << "," << fileSize << std::endl;
    }
    fat_table_file.close();
}

void FAT_Table::display_fat_table()
{
    std::cout << fileName << "\t" <<start << "\t" << fileSize << std::endl;
}
