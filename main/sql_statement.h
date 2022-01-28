#ifndef MINIDB_SQL_STATEMENT_H_
#define MINIDB_SQL_STATEMENT_H_

#include <string>
#include <vector>

#include "catalog_manager.h"

class CatalogManger;
class Database;
class Attribute;
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

class SQLCreateTable: public SQL{
    private:
        std::string tb_name_;
        std::vector<Attribute> attrs_;
    public:
        SQLCreateTable(std::vector<std::string> sql_vector){Parse(sql_vector);}
        std::string tb_name() {return tb_name_;}
        void set_tb_name(std::string tbname){tb_name_=tbname;}
        std::vector<Attribute> attrs() {return attrs_;}
        void set_attrs(std::vector<Attribute> att){attrs_=att;}
        void Parse(std::vector<std::string> sql_vector);
};
class SQLCreateIndex: public SQL{
private:
    std::string index_name_;
    std::string tb_name_;
    std::string col_name_;
public:
    SQLCreateIndex(std::vector<std::string> sql_vector){Parse(sql_vector);}
    void Parse(std::vector<std::string> sql_vector);
    std::string index_name(){return index_name_;}
    std::string tb_name(){return tb_name_;}
    std::string col_name(){return col_name_;}
};

class SQLUse: public SQL{
private:
    std::string db_name_;
public:
    SQLUse(std::vector<std::string> sql_vector){Parse(sql_vector);}
    std::string db_name(){return db_name_;}
    void set_db_name(std::string dbname){db_name_=dbname;}
    void Parse(std::vector<std::string> sql_vector);
};
typedef struct{
    int data_type;
    std::string  value;
}SQLValue;

class SQLInsert:public SQL{
private:
    std::string tb_name_;
    std::vector<SQLValue> values_;
public:
    SQLInsert(std::vector<std::string> sql_vector){Parse(sql_vector);}
    void Parse(std::vector<std::string> sql_vector);
    std::string tb_name(){return tb_name_;}
    std::vector<SQLValue> &values(){return values_;}
};

#endif