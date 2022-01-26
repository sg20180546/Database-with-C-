

#include <fstream>
#include <iostream>

#include <vector>

#include <boost/filesystem.hpp>

#include "exceptions.h"
#include "minidb_api.h"

using namespace std;
// #include "catalog_manager.h"
MiniDBAPI::MiniDBAPI(std::string p) : path_(p){cm_= new CatalogManager(p); }

MiniDBAPI::~MiniDBAPI(){
    delete cm_;
}

void MiniDBAPI::Help(){
    std::cout<<"HELP"<<std::endl;
}
void MiniDBAPI::Quit(){
    std::cout<<"Quiting ..."<<std::endl;
}

void MiniDBAPI::CreateDatabase(SQLCreateDatabase &st){
    std::cout<<"Creating Database: "<<st.db_name()<<std::endl;
    std::string folder_name(path_+st.db_name());
    boost::filesystem::path folder_path(folder_name);

    folder_path.imbue(std::locale("en_US.UTF-8"));
    std::cout<<folder_path<<"1"<<std::endl;
    if(cm_->GetDB(st.db_name()) !=NULL){
        throw DatabaseAlreadyExistsException();
    }
    // std::cout<<folder_path<<"2"<<std::endl;
    if(boost::filesystem::exists(folder_path)){
        boost::filesystem::remove_all(folder_path);
        std::cout<<"Database folder exists and deleted!"<<std::endl;
    }
    // std::cout<<folder_path<<std::endl;
    boost::filesystem::create_directories(folder_path);
    std::cout<<"Database folder created"<<std::endl;
    cm_->CreateDatabase(st.db_name());
    std::cout<<"Catalog written!"<<std::endl;
    cm_->WriteArchiveFile();

}