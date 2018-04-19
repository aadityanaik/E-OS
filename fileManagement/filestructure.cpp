#include "filestructure.h"
#include <random>
#include <ctime>
#include <iostream>

FileStructure::FileStructure()
{
    file_id = 0;
    file_name = "";
    file_data = "";
    file_location = 0;
}

FileStructure::FileStructure(unsigned int file_id, std::string file_name, std::string file_data, unsigned int file_location, unsigned int file_size)
{
    this->file_id = file_id;
    this->file_name = file_name;
    this->file_data = file_data;
    this->file_location = file_location;
    this->file_size = file_size;
}

unsigned int FileStructure::produceFileID(std::string file_name)
{
    unsigned int random_num;
    unsigned int final_random_num;
    unsigned int file_length;
    srand (time(NULL));
    file_length = file_name.length();
    random_num = rand()%1000;
    final_random_num = random_num*(rand()%10000);
    file_id = (final_random_num*file_length)%100;
    return file_id;
}

unsigned int FileStructure::findSize(std::string file_data)
{
    unsigned int file_size;
    file_size = file_data.length()%10;
    if(file_size < 0 || file_size == 0) {
        file_size = 1;
    }

    return size;
}

void FileStructure::addFile(std::string file_name, std::string file_data)
{
    unsigned int generated_id;
    unsigned int generated_size;
    generated_id = produceFileID(file_name);
    generated_size = findSize(file_data);

    file_id = generated_id;
    this->file_name = file_name;
    file_location = 5;
    std::cout << "\nFile Id: " << file_id << "\nFile Name: " << file_name << "\nFile Location: " << file_location <<
    "\nFile Size: " << file_size << std::endl;
}

std::string FileStructure::getData()
{
    return file_data;
}
