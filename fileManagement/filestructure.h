#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H
#include <cstdlib>
#include <string>
#include <map>

class FileStructure
{
    public:
        FileStructure();
		FileStructure(std::string name, int size);
        unsigned int produceFileID(std::string file_name);
        std::string addFile(std::string file_name, std::string file_data);
        unsigned int findSize(std::string file_data);
        std::string getData();
        std::string updateFile();
        std::string appendFile(std::string file_name, std::string update_data);
        std::string readFile(std::string file_name);
        bool deleteFile(std::string file_name);
        unsigned int setLocation(unsigned int start);
        unsigned int getLength(std::string file_name);
        unsigned int getLocation();
		unsigned int getSize();
		std::string getName();
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
