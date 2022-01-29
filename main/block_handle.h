#ifndef MINIDB_BLOCK_HANDLE_H_
#define MINIDB_BLOCK_HANDLE_H_

#include "block_info.h"

class BlockHandle{
private:
    BlockInfo* first_block_;
    int bsize_;
    int bcount_;
    std::string path_;
    BlockInfo *Add(BlockInfo *block);
public:
    BlockHandle(std::string p) :
    first_block_(new BlockInfo(0)), bsize_(300), bcount_(0), path_(p){
        Add(first_block_);
    }
    ~BlockHandle();

    int bcount(){return bcount_;}

    BlockInfo* GetUsableBlock();
    void FreeBlock();
};

#endif