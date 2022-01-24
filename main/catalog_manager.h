

#ifndef MINIDB_CATALOG_MANAGER_H_
#define MINIDB_CATALOG_MANAGER_H_


#include <string>
#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include "sql_statement.h"

class Database;
class Table;
class Attribute;
class Index;
class SQLCreateTable;
class SQLDropTable;
class SQLDropIndex;

class CatalogManger{
    private:
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive &ar,const unsigned int version){
            ar &dbs_;
        }
        std::string path_;
        std::vector<Database> dbs_;
    public:
        CatalogManger(std::string p);
        ~CatalogManger();
        std::vector<Database> &dbs() {return dbs_;}
        std::string path() {return path_;}
        Database *GetDB(std::string db_name);
};

class Database{
    private:
        friend class boost::serialization::access;
    // std::string db_name_;
    public:
        std::string db_name(){return db_name_;}
};


#endif /*dd*/