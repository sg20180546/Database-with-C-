
#include "catalog_manager.h"
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;


Database* CatalogManger::GetDB(std::string db_name){
    for(unsigned int i=0;i<dbs_.size();++i){
        if(dbs_[i].db_name()==db_name){
            return &dbs_[i];
        }
    }
    return NULL;
}