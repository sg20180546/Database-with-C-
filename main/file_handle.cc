#include "file_handle.h"
#include <fstream>

#include "commons.h"


void FileHandle::IncreaseAge(){
    FileInfo* fp=first_file_;
    while(fp!=NULL){
        BlockInfo* bp=fp->first_block();
        while(bp!=NULL){
            bp->IncreaseAge();
            bp=bp->next();
        }
        fp=fp->next();
    }
}