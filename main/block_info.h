#ifndef MINIDB_BLOCK_INFO_H_
#define MINIDB_BLOCK_INFO_H_

#include <sys/types.h>

#include "commons.h"

class FileInfo;

class BlockInfo{
private:
    FileInfo* file_;
    int block_num_;
    char* data_;
    bool dirty_;
    long age_;
    BlockInfo* next_;
public:
    BlockInfo(int num): dirty_(false),next_(NULL),file_(NULL),age_(0),block_num_(num){
        data_=new char[4*1024];
    }
    virtual ~BlockInfo(){ delete[] data_;}
    FileInfo* file(){return file_;}
    void set_file(FileInfo* f){file_=f;}
    void IncreaseAge(){++age_;}
    BlockInfo* next(){return next_;}
    char* data(){ return data_;}
//  ??? string to int?
    int GetRecordCount(){return *(int *)(data_ + 8);}
    int GetNextBlockNUm(){return *(int*)(data_+4);}
};


#endif