
#include "catalog_manager.h"
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;

CatalogManager::CatalogManager(std::string p): path_(p){}

CatalogManager::~CatalogManager(){}

void CatalogManager::WriteArchiveFile(){
    std::string file_name=path_+"catalog";
    std::ofstream ofs;
    ofs.open(file_name.c_str(),std::ios::binary);
    boost::archive::binary_oarchive oar(ofs);
    oar << (*this);
    ofs.close();
}




void CatalogManager::CreateDatabase(std::string dbname){
    dbs_.push_back(Database(dbname));
}

Database* CatalogManager::GetDB(std::string db_name){
    for(unsigned int i=0;i<dbs_.size();++i){
        if(dbs_[i].db_name()==db_name){
            return &dbs_[i];
        }
    }
    return NULL;
}

Database::Database(std::string dbname) : db_name_(dbname){}

void Database::CreateTable(SQLCreateTable &st){
    int record_length=0;
    Table tb;
    for(int i=0;i<st.attrs().size();++i){
        tb.AddAttribute(st.attrs()[i]);
        record_length+=st.attrs()[i].length();
    }
    tb.set_tb_name(st.tb_name());
    tb.set_record_length(record_length);
    tbs_.push_back(tb);
}

bool Database::CheckIfIndexExists(std::string index_name){
    bool exists=false;
    for(unsigned int i=0;i<tbs_.size();++i){
        for(unsigned int j=0;j<tbs_[i].ids().size();++j){
            if (tbs_[i].ids()[j].name() == index_name) {
                exists = true;
            }
        }
    }
    return exists;
}

Table* Database::GetTable(std::string tb_name){
    for(unsigned int i=0;i<tbs_.size();++i){
        if(tbs_[i].tb_name()==tb_name){
            return &tbs_[i];
        }
    }
    return NULL;
}
