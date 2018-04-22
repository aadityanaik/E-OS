#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H
#include <cstdlib>
#include <string>

class FileStructure
{
    public:
        FileStructure();
        unsigned int produceFileID(std::string file_name);
        void addFile(std::string file_name, std::string file_data);
        unsigned int findSize(std::string file_data);
        std::string getData();
        std::string updateFile();
        void appendFile(std::string file_name);
        void readFile(std::string file_name);
        void deleteFile(std::string file_name);
    protected:

    private:
        unsigned long int file_id;
        std::string file_name;
        std::string file_data;
        unsigned int file_location;
        unsigned int file_size;
        unsigned int generated_id;
};

#endif // FILESTRUCTURE_H
