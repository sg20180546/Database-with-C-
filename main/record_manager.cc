
#include "record_manager.h"
#include <iomanip>
#include <iostream>

#include "index_manager.h"
using namespace std;

BlockInfo* RecordManager::GetBlockInfo(Table* tbl,int block_num){
    if(block_num==-1) return NULL;
    BlockInfo* block=hdl_->GetFileBlock(db_name_,tbl->tb_name(),0,block_num);
    return block;
}

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
                throw PrimaryKeyConflictException();
            }
        }else{
            int block_num=tbl->first_block_num();
            for(int i=0;i<tbl->block_count();++i){
                BlockInfo *bp=GetBlockInfo(tbl,block_num);
                for(int j=0;j<bp->GetRecordCount();++j){
                    vector<Tkey> tkey_value=GetRecord(tbl,block_num,j);
                    if(tkey_value[pk_index] == tkey_values[pk_index]){
                        throw PrimaryKeyConflictException();
                    }
                }
                block_num=bp->GetNextBlockNUm();
            }
        }   
    }

    char* content;


}

std::vector<Tkey> RecordManager::GetRecord(Table* tbl, int block_num, int offset){
    vector<Tkey> keys;
    BlockInfo*bp=GetBlockInfo(tbl,block_num);
    char* content=bp->data()+ offset *tbl->record_length()+12;
    for(int i=0;i<tbl->GetAttributeNum();++i){
        int value_type=tbl->ats()[i].data_type();
        int length=tbl->ats()[i].length();
        
        Tkey tmp(value_type,length);
        memcpy(tmp.key(),content,length);
        keys.push_back(tmp);
        content+=length;
    }
    return keys;
}