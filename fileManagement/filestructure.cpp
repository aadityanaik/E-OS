#include "filestructure.h"
#include <random>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

FileStructure::FileStructure()
{
    file_id = 0;
    file_name = "";
    file_data = "null";
    file_location = 0;
    file_size = 0;
    generated_id = 0;
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
    file_size = file_data.length()/10;
    if(file_size < 0 || file_size == 0) {
        file_size = 1;
    }

    return file_size;
}

void FileStructure::addFile(std::string file_name, std::string file_data)
{
    unsigned int generated_size;
    generated_id++;
    generated_id = generated_id*produceFileID(file_name);
    generated_size = findSize(file_data);

    file_size = generated_size;
    file_id = generated_id * generated_size;
    this->file_name = file_name;
    file_location = 5;

    std::ofstream createdFile(file_name+ ".txt");
    if(createdFile.is_open()) {
        createdFile << file_data;
    }
    createdFile.close();

    std::cout << "\nFile Id: " << file_id << "\nFile Name: " << file_name << "\nFile Location: " << file_location <<
    "\nFile Size: " << file_size << std::endl;
}

std::string FileStructure::getData()
{
    return file_data;
}

std::string FileStructure::updateFile()
{
    std::string writeFile;
    std::cout << "Enter data: ";
    std::cin >> writeFile;

    return writeFile;
}

void FileStructure::appendFile(std::string file_name)
{
    std::string update;
    update = updateFile();

    std::ofstream append(update + ".txt", std::ios::app);
    if(append.is_open()) {
        append << update;
    }
    append.close();
    std::cout << "File updated!" << std::endl;
}

void FileStructure::readFile(std::string file_name)
{
    std::string read_data;
    std::ifstream readFile(file_name + ".txt");
        if(readFile.is_open()) {
            std::cout << "The data is: " << std::endl;
            readFile >> read_data;
        }
        else {
            std::cout << "File not found!" << std::endl;
        }
        readFile.close();

        std::cout << read_data << std::endl;
}

void FileStructure::deleteFile(std::string file_name)
{
    int delete_status;
    std::string file_name_with_extension = file_name + ".txt";
    char file_name_array[30];

    std::strcpy(file_name_array, file_name_with_extension.c_str());

    delete_status = remove(file_name_array);
    if(delete_status == 0) {
        std::cout << "File " << file_name << " successfully deleted!" << std::endl;
    }
    else {
        std::cout << "Unable to delete " << file_name << std::endl;
    }
}
