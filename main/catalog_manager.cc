
#include "catalog_manager.h"
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;

// CatalogManger::CatalogManger(std::string p): path_(p){ReadArchiveFile();}


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