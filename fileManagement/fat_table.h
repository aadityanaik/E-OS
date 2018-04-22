#ifndef FAT_TABLE_H
#define FAT_TABLE_H
#include <string>

class FAT_Table
{
    public:
        FAT_Table();
        void make_table(std::string file_name, unsigned int start, unsigned int file_size);
        void display_fat_table();

    protected:

    private:
        std::string fileName;
        unsigned int start;
        unsigned int fileSize;
};

#endif // FAT_TABLE_H
