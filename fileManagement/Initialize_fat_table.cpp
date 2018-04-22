#include <fstream>
int main() {

std::ofstream fat_table_file("FAT_TABLE.csv");           //FAT_TABLE.csv must exist
    if(fat_table_file.is_open()) {
        fat_table_file << "File Name" << "," << "Start" << "," << "File Size" << std::endl;
    }
    fat_table_file.close();
    return 0;
}
