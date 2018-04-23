#include "fat_table.h"
#include <fstream>
#include <iostream>
#include <string>

FAT_Table::FAT_Table()
{
    fileNameFAT = "null";
    startFAT = 0;
    fileSizeFAT = 0;
}

void FAT_Table::make_table(std::string file_name, unsigned int start, unsigned int file_size)
{
    std::ofstream fat_table_file("FAT_TABLE.txt", std::ios::app);           //FAT_TABLE.csv must exist
    if(fat_table_file.is_open()) {
        fat_table_file << "\n" << file_name << "\t\t" << start << "\t\t" << file_size << std::endl;
    }
    fat_table_file.close();
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
            fat_table = fat_table + fat_row;
        }
    }
    fat_table_file.close();
    return fat_table;
}

void FAT_Table::make_ls(std::string file_name)
{
    std::ofstream fat_table_ls("ls.txt", std::ios::app);           //FAT_TABLE.csv must exist
    if(fat_table_ls.is_open()) {
        fat_table_ls << "\n" << file_name << std::endl;
    }
    fat_table_ls.close();
}

std::string FAT_Table::ls_command()
{
    std::ifstream fat_table_ls("ls.txt");

    std::string fat_row;
    std::string fat_table = "";

    if(fat_table_file.is_open())
    {
        while(!fat_table_file.eof())
        {
            getline(fat_table_file, fat_row);
            fat_table = fat_table + fat_row;
        }
    }
    fat_table_file.close();
    return fat_table;
}
