#include "filestructure.h"
#include <iostream>

int main()
{
    char addFileOption;
    std::string fileName;
    std::string fileData;
    FileStructure file_structure();

    std::cout << "\t\t\t\tFile Management Menu\n" << std::endl;

    std::cout << "Press 1 to create new file" << std::endl;
    std::cout << "Press 2 to see file data" << std::endl;
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
    }
    else if(addFileOption == '2' || addFileOption == 'd' || addFileOption == 'D') {
        std::string data;
        data = file_structure.getData();
        std::cout << "Okay" <<std::endl;
    }

    return 0;
}
