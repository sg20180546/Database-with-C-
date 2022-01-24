#include "minidb_api.h"

#include <fstream>
#include <iostream>

#include <vector>

#include <boost/filesystem.hpp>

#include "exception.h"
#include "catalog_manager.h"
void MiniDBAPI::Help(){

}

void MiniDBAPI::CreateDatabase(SQLCreateDatabase &st){
    std::cout<<"Creating Database: "<<st.db_name()<<std::endl;
    std::string folder_name(path,+st.db_name());
    boost::filesystem::path folder_path(folder_name);

    folder_path.imbue(std::locale("en_us.UTF-8"));
    if(cm_->GetDB(st.db_name()!=NULL){
        throw DatabaseAlreadyExistsException();
    }
}