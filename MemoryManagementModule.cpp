// @Author : Aditya Pansare
// MEMORY MANAGEMENT MODULE
// PAGING METHOD USED : DYNAMIC
// DATA STRUCTURE USED : STRUCTURES FOR ELEMENTS, ARRAYS FOR MEMORY
// MAIN MEMORY & SECONDARY MEMORY IS AN ARRAY OF INTEGERS [true (OCCUPIED), false (UNOCCUPIED)]
// MEMORY MAIN : MEMORY SECONDARY = 1 : 5
// MEMORY ALLOCATION TECHNIQUE : DYNAMIC
// COMPACTION TO BE IMPLEMENTED
// CREATE MAT ACCORDING TO PROCESS AND FILES

#include<iostream>
// BELOW IS THE MEMORY SIZE AS PER RATIO, IT CAN BE CHANGED AS PER NEED AND FEASIBILTY
#define MAX 25 
using namespace std;

// GLOBAL RESOURCES
// MOCK STRUCTURE FOR PROCESS
struct process{
    int pid;
    int size;
    int memoryBlockStartFrom;
};

// MOCK STRUCTURE FOR FILES

struct file{
    int fid;
    int size;
    int memoryBlockStartFrom;
};

bool MAINMemory[MAX];
bool SECONDARYMemory[5 * MAX];


//FUNCTIONS FOR THE MODULE

bool checkMainMemoryFull(){
    int i =0;
    bool fullchecker=true;
    while(i <= MAX){
        fullchecker *= MAINMemory[i];
        if(fullchecker == false){
            break;
        }

    }

    if(fullchecker == false){
        return false;
    }else{
        return true;
    }
}
bool checkSecondaryMemoryFull(){
    int i =0;
    bool fullchecker=true;
    while(i <= 5 * MAX){
        fullchecker *= SECONDARYMemory[i];
        if(fullchecker == false){
            break;
        }

    }

    if(fullchecker == false){
        return false;
    }else{
        return true;
    }
}

int updateMainMemoryOccupied(){
    int occCount = 0;
    int i=0;
    while(i <= MAX){
        if (MAINMemory[i]==true){
            occCount+=1;
        };

    }

    return occCount;

}
int updateSecondaryMemoryOccupied(){
    int occCount = 0;
    int i=0;
    while(i <= 5*MAX){
        if (SECONDARYMemory[i]==true){
            occCount+=1;
        };

    }

    return occCount;

}



int findMainMemoryLocation(process p){
    int i =0;
    // RUN COMPACTION
    if(checkMainMemoryFull() == true){
        return -1;
    }else{
        while(i<=MAX){
            if(MAINMemory[i]==false){
                return i;
                p.memoryBlockStartFrom =i;
                break;
            }
        }
    }
}

int findSecondaryMemoryLocation(file f){
    int i =0;
    // RUN COMPACTION
    if(checkSecondaryMemoryFull() == true){
        return -1;
    }else{
        while(i<=MAX){
            if(SECONDARYMemory[i]==false){
                return i;
                f.memoryBlockStartFrom =i;
                break;
            }
        }
    }
    
}

void createMATMain(){

}

void createMATSecondary(){

}

bool mainMemoryCompaction(){

}

bool secondaryMemoryCompaction(){

}

bool allocateMemoryMain(process p){
    //CALL findMainMemoryLocation()
}

bool allocateMemorySecondary(file f){
    //CALL findSecondaryMemoryLocation()
}



int main(){

}

