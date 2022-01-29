#include "index_manager.h"
#include <fstream>
#include <iostream>

#include "sql_statement.h"
#include "exceptions.h"
#include "commons.h"

using namespace std;


void IndexManager::CreateIndex(SQLCreateIndex &st){
    string tb_name=st.tb_name();
    Table* tbl=cm_->GetDB(db_name_)->GetTable(tb_name);
    if(tbl==NULL){
        throw TableNotExistException();
    }
    if(tbl->GetIndexNum()!=0){
        throw OneIndexEachTableException();
    }
    Attribute *attr=tbl->GetAttribute(st.col_name());
    if(attr->attr_type()!=1){
        throw IndexMustBeCreatedOnPKException();
    }
    string file_name=cm_->path()+db_name_+"/"+st.index_name()+".index";
    std::ofstream ofs(file_name.c_str(),std::ios::binary);
    ofs.close();

    Index idx(st.index_name(),st.col_name(),attr->data_type(),attr->length(),(4*1024-12)/(4+attr->length())/2 -1);

    tbl->AddIndex(idx);

    BPlusTree tree(tbl->GetIndex(0),hdl_,cm_,db_name_);
}

int BPlusTree::GetVal(Tkey key){
    int ret=-1;
    FindNodeParam fnp;
}