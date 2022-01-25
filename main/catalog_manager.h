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
// class Index;
class SQLCreateTable;
class SQLDropTable;
class SQLDropIndex;

class CatalogManager{
    private:
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive &ar,const unsigned int version){
            ar &dbs_;
        }
        std::string path_;
        std::vector<Database> dbs_;
    public:
        CatalogManager(std::string p);
        ~CatalogManager();
        std::vector<Database> &dbs() {return dbs_;}
        std::string path() {return path_;}
        Database *GetDB(std::string db_name);
        void WriteArchiveFile();
        void CreateDatabase(std::string dbname);
};

class Database{
private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar,const unsigned int version){
        ar &db_name_;
        ar &tbs_;
    }
    std::string db_name_;
    std::vector<Table> tbs_;

    public:
        Database();
        Database(std::string dbname);
        ~Database(){}
        std::string db_name(){return db_name_;}
        
};
class Table{
private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar,const unsigned int version){
        ar &tb_name_;
        ar &record_length_;
        ar &first_block_num_;
        ar &first_rubbish_num_;
        ar &block_count_;
        ar &ats_;
        // ar &ids_;
    }
    std::string tb_name_;
    int record_length_;

    int first_block_num_;
    int first_rubbish_num_;
    int block_count_;
    std::vector<Attribute> ats_;
    // std::vector<Index> ids_;
};

class Attribute{
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version){
        ar &attr_name_;
        ar &data_type_;
        ar &length_;
        ar &attr_type_;
    }
    std::string attr_name_;
    int data_type_;
    int length_;
    int attr_type_;
};

#endif /*dd*/