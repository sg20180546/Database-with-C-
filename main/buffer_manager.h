#ifndef MINIDB_BUFFER_MANAGER_H_
#define MINIDB_BUFFER_MANAGER_H_

#include <string>
#include "block_handle.h"

class BufferManager{
private:
    std::string path_;
    BlockHandle* bhandle_;
public:
    BufferManager(std::string p) 
        : path_(p) {}
    ~BufferManager(){

    }
    BlockInfo * GetFileBlock(std::string db_name,std::string tb_name,
    int file_type,int block_num);
    void WriteBlock(BlockInfo* block);
    void WriteToDisk();
};
#endif