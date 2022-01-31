#ifndef MINIDB_FILE_HANDLE_H_
#define MINIDB_FILE_HANDLE_H_

#include <string>

#include "block_info.h"
#include "file_info.h"

class FileHandle{
private:
    FileInfo* first_file_;
    std::string path_;
public:
    FileHandle(std::string p) : first_file_(new FileInfo() ) ,path_(p){}
    ~FileHandle();
    void IncreaseAge();
};

#endif