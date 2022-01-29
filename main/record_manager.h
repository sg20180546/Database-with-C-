#ifndef MINIDB_RECORD_MANAGER_H_
#define MINIDB_RECORD_MANAGER_H_

#include "block_info.h"
#include "buffer_manager.h"
#include "catalog_manager.h"
#include "sql_statement.h"
#include "exceptions.h"
class RecordManager{
private:
    BufferManager *hdl_;
    CatalogManager *cm_;
    std::string db_name_;
public:
    RecordManager(CatalogManager* cm, BufferManager* hdl, std::string db)
    : cm_(cm),hdl_(hdl),db_name_(db) {}
    ~RecordManager(){}
    void Insert(SQLInsert &st);
};

#endif