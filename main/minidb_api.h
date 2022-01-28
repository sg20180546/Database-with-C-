#ifndef MINIDB_MINIDB_API_H_
#define MINIDB_MINIDB_API_H_

#include <string>

#include "sql_statement.h"
#include "catalog_manager.h"
#include "buffer_manager.h"
// using namespace std;
class MiniDBAPI {
private:
  std::string path_;
    std::string curr_db_;
    CatalogManager *cm_;
    BufferManager *hdl_;


public:
  MiniDBAPI(std::string p);
  ~MiniDBAPI();
  void Quit();
  void Help();
  void CreateDatabase(SQLCreateDatabase &st);
  void CreateTable(SQLCreateTable &st);
  void CreateIndex(SQLCreateIndex &st);
  void Use(SQLUse &st);
  void Insert(SQLInsert &st);
};

#endif