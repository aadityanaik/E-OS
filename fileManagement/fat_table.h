#ifndef FAT_TABLE_H
#define FAT_TABLE_H
#include <string>

class FAT_Table
{
    public:
        FAT_Table();
        void make_table(std::string file_name, unsigned int start, unsigned int file_size);
        std::string display_fat_table();
        void make_ls(std::string file_name);
        std::string ls_command();

    protected:

    private:
        std::string fileNameFAT;
        unsigned int startFAT;
        unsigned int fileSizeFAT;
};

#endif // FAT_TABLE_H
