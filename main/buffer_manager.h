#ifndef MINIDB_BUFFER_MANAGER_H_
#define MINIDB_BUFFER_MANAGER_H_

#include <string>
#include "buffer_handle.h"
#include "block_handle.h"

class BufferManager{
private:
    std::string path_;

public:
    BufferManager(std::string p) 
        : path_(p) {}
    ~BufferManager(){

    }
};
#endif