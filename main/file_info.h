#ifndef MINIDB_FILE_INFO_H_
#define MINIDB_FILE_INFO_H_

#include <string>
#include "commons.h"

class BlockInfo;

class FileInfo{

private:
    std::string db_name_;
    int type_;
    std::string file_name_;
    int record_amount_;
    int record_length_;
    BlockInfo * first_block_;
    FileInfo* next_;
public:
    FileInfo()
        : db_name_(""),type_(FORMAT_RECORD),file_name_(""),record_amount_(0),
        record_length_(0),first_block_(0),next_(0){}
    FileInfo(std::string db, int tp, std::string file, int reca,int recl,
    FileInfo*nex, BlockInfo* firb)
        :db_name_(db),type_(tp),file_name_(file),record_amount_(reca),
        record_length_(recl),first_block_(firb),next_(nex) {}
    ~FileInfo(){}

    FileInfo* next(){return next_;}
    BlockInfo* first_block(){return first_block_;}
    std::string db_name(){return db_name_;}
    int type(){return type_;}
    std::string file_name(){return file_name_;}

};
#endif