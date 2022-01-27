#ifndef MINIDB_INDEX_MANAGER_H_
#define MINIDB_INDEX_MANAGER_H_

#include <string>

#include "catalog_manager.h"
#include "sql_statement.h"

class BPlusTree;
class BPlusTreeNode;

class IndexManager{
private:
    CatalogManager *cm_;
    std::string db_name_;
    public:
        IndexManager(CatalogManager *cm, std::string db){
            cm_=cm;
            db_name_=db;
        }
        ~IndexManager(){}
        void CreateIndex(SQLCreateIndex &st)l
};

class BPlusTree{
private:
    Index *idx_;
    int degree_;
    CatalogManager *cm_;
    std::string db_name_;

public:
    BPlusTree(Index* idx,CatalogManager *cm,std::string db_name){
        cm_=cm;
        idx_=idx;
        db_name_=db_name;
        degree_=2*idx_->rank()+1;
    }
    ~BPlusTree(){}
}

#endif