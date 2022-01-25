#include "minidb_api.h"

#include <fstream>
#include <iostream>

#include <vector>

#include <boost/filesystem.hpp>

#include "exceptions.h"
#include "catalog_manager.h"
void MiniDBAPI::Help(){

}

void MiniDBAPI::CreateDatabase(SQLCreateDatabase &st){
    std::cout<<"Creating Database: "<<st.db_name()<<std::endl;
    std::string folder_name(path_+st.db_name());
    boost::filesystem::path folder_path(folder_name);

    folder_path.imbue(std::locale("en_us.UTF-8"));

    if(cm_->GetDB(st.db_name()) !=NULL){
        throw DatabaseAlreadyExistsException();
    }
    if(boost::filesystem::exists(folder_path)){
        boost::filesystem::remove_all(folder_path);
        std::cout<<"Database folder exists and deleted!"<<std::endl;
    }
    boost::filesystem::create_directories(folder_path);
    std::cout<<"Database folder created"<<std::endl;
    cm_->CreateDatabase(st.db_name());
    std::cout<<"Catalog written!"<<std::endl;
    cm_->WriteArchiveFile();

}