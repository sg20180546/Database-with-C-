
#include "record_manager.h"
#include <iomanip>
#include <iostream>

#include "index_manager.h"
using namespace std;
void RecordManager::Insert(SQLInsert &st){
    string tb_name=st.tb_name();
    unsigned long values_size=st.values().size();
    Table* tbl=cm_->GetDB(db_name_)->GetTable(tb_name);
    if(tbl==NULL){
        throw TableNotExistException();
    }
    int max_count=(4096-12)/(tbl->record_length());
    vector<Tkey> tkey_values;
    int pk_index=-1;

    for(int i=0;i<values_size;++i){
        int value_type=st.values()[i].data_type;
        string value=st.values()[i].value;
        int length=tbl->ats()[i].length();

        Tkey tmp(value_type,length);
        tmp.ReadValue(value.c_str());
        tkey_values.push_back(tmp);
        if(tbl->ats()[i].attr_type()==1){
            pk_index=i;
        }
    }
    if(pk_index!=-1){
        if(tbl->GetIndexNum()!=0){
            BPlusTree tree(tbl->GetIndex(0),hdl_,cm_,db_name_);
            int value=tree.GetVal(tkey_values[pk_index]);
            if(value!=-1){
                
            }
        }
    }
}