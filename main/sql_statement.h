#ifndef MINIDB_SQL_STATEMENT_H_
#define MINIDB_SQL_STATEMENT_H_

#include <string>
#include <vector>

#include "catalog_manager.h"

class CatalogManger;
class Database;

class SQL{
    protected:
        int sql_type_;
    public:
        SQL(): sql_type_(-1) {}
        SQL(int sqltype){sql_type_=sqltype;}
        virtual ~SQL(){}
        int sql_type(){ return sql_type_;}
        void set_sql_type(int sqltype){sql_type_= sqltype;}
        virtual void Parse(std::vector<std::string> sql_vector)=0;
        int ParseDataType(std::vector<std::string> sql_vector, Attribute &attr,
        unsigned int pos);

};

class SQLCreateDatabase: public SQL{
private:
    std::string db_name_;
public:
    SQLCreateDatabase(std::vector<std::string> sql_vector){Parse(sql_vector);}
    std::string db_name(){return db_name_;}
    void set_db_name(std::string dbname){db_name_ = dbname;}
    void Parse(std::vector<std::string> sql_vector);
};


#endif