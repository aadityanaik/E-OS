#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H
#include <cstdlib>
#include <string>
//#include <iostream>

class FileStructure
{
    public:
        FileStructure();
        FileStructure(unsigned int file_id, std::string file_name, unsigned int file_location, unsigned int file_size);
        //~FileStructure();

        unsigned int produceFileID(std::string file_name);
        void addFile(std::string file_name, string file_data);
        void findSize(std::string file_data);
        std::string getData();
    protected:

    private:
        unsigned long int file_id;
        std::string file_name;
        std::string file_data;
        unsigned int file_location;
        unsigned int file_size;
};

#endif // FILESTRUCTURE_H
