

#include <fstream>
#include <iostream>

#include <vector>

#include <boost/filesystem.hpp>

#include "exceptions.h"
#include "minidb_api.h"
#include "index_manager.h"
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
        // throw DataBaseNotExistException();
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

void MiniDBAPI::CreateTable(SQLCreateTable &st){
    std::cout<<"Creating Table: "<<st.tb_name()<<std::endl;
    if(curr_db_.length()==0){
        throw NoDatabaseSelectedException();
    }
    Database *db=cm_->GetDB(curr_db_);
    if(db==NULL){
        throw DataBaseNotExistException();
    }
    if(db->GetTable(st.tb_name())!=NULL ){
        throw TableAlreadyExistsException();
    }
    std::string file_name(path_+curr_db_+"/"+st.tb_name()+".records");
    boost::filesystem::path folder_path(file_name);
    if(boost::filesystem::exists(file_name)){
        boost::filesystem::remove(file_name);
        std:cout<<"Table file already exists and deleted! "<<std::endl;
    }
    ofstream ofs(file_name);
    ofs.close();
    db->CreateTable(st);
    std::cout<<"Table file created"<<std::endl;
    cm_->WriteArchiveFile();
}

void MiniDBAPI::CreateIndex(SQLCreateIndex &st){
    if(curr_db_.length()==0){
        throw NoDatabaseSelectedException();
    }
    Database *db=cm_->GetDB(curr_db_);
    if(db->GetTable(st.tb_name())==NULL){
        throw TableNotExistException();
    }
    if(db->CheckIfIndexExists(st.index_name())){
        throw IndexAlreadyExistsException();
    }
    IndexManager *im=new IndexManager(cm_,curr_db_);
    im->CreateIndex(st);
    delete im;
}

void MiniDBAPI::Use(SQLUse &st){
    Database *db=cm_->GetDB(st.db_name());
    if(db==NULL){
        throw DataBaseNotExistException();
    }
    if(curr_db_.length()!=0){
        std::cout<<"Closing the previous Database: "<<curr_db_<<std::endl;
        cm_->WriteArchiveFile();
        delete hdl_;
    }
    curr_db_=st.db_name();
    hdl_=new BufferManager(path_);
    // hdl=new buffermanger;
}