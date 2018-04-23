#include "filestructure.h"
#include "fat_table.h"
#include <iostream>

int fat_table_index = 0;

int main()
{
    while(true) {
        char addFileOption;
        std::string fileName;
        std::string fileData;
        unsigned int fileLength;
        unsigned int fileStart;

        FileStructure file_structure;
        FAT_Table fat_table;

        std::cout << "\t\t\t\tFile Management Menu\n" << std::endl;

        std::cout << "Press 1 to create new file" << std::endl;
        std::cout << "Press 2 to read file data" << std::endl;
        std::cout << "Press 3 to append file data" << std::endl;
        std::cout << "Press 4 to display FAT table" << std::endl;
        std::cout << "Press 5 to delete File" << std::endl;
        std::cout << "Press 6 to exit!" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> addFileOption;

        //if condition to check for available memory

        if(addFileOption == '1' || addFileOption == 'f' || addFileOption == 'F') {
            std::cout << "\nEnter the file name: ";
            std::cin >> fileName;
            std::cout << "Enter Data: ";
            std::cin >> fileData;
            file_structure.addFile(fileName, fileData);
            std::cout << "File " << fileName << " added!" << std::endl;
            fileLength = file_structure.findSize(fileData);
            fileStart = file_structure.getLocation();
            fat_table.make_table(fileName, fileStart, fileLength);
        }
        else if(addFileOption == '2' || addFileOption == 'd' || addFileOption == 'D') {
            std::string file_name_to_read;
            std::cout << "Enter file name to read: ";
            std::cin >> file_name_to_read;
            file_structure.readFile(file_name_to_read);
        }
        else if(addFileOption == '3' || addFileOption == 'a' || addFileOption == 'A') {
            std::string file_name_to_append, data_to_append;
            std::cout << "Enter file name to append: ";
            std::cin >> file_name_to_append;
            std::cout << "Enter data: ";
            std::cin >> data_to_append;
            file_structure.appendFile(file_name_to_append, data_to_append);
        }
        else if(addFileOption == '4' || addFileOption == 'f' || addFileOption == 'F') {
            std::cout << "FAT Table: " << std::endl;
        }
        else if(addFileOption == '5' || addFileOption == 'f' || addFileOption == 'F') {
            std::string file_name_to_delete;
            std::cout << "Enter file name to delete: ";
            std::cin >> file_name_to_delete;
            file_structure.deleteFile(file_name_to_delete);
        }
        else if(addFileOption == '6' || addFileOption == 'e' || addFileOption == 'E') {
            std::cout << "Exiting File Window!" << std::endl;
            break;
        }
        else {
            std::cout << "Please enter a valid number!" << std::endl;
        }
    }
    return 0;
}
