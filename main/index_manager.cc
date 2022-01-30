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

//  BplusTree

void BPlusTree::InitTree(){
    BPlusTreeNode *root_node=new BPlusTreeNode(true,this,GetNewBlockNum(),true);
    // 
}

int BPlusTree::GetVal(Tkey key){
    int ret=-1;
    FindNodeParam fnp=Search(idx_->root(),key);
    if(fnp.flag){
        ret=fnp.pnode->GetValues(fnp.index);
    }
    return ret;
}

FindNodeParam BPlusTree::Search(int node,Tkey &key){
    FindNodeParam ret;
    int index=0;
    BPlusTreeNode* pnode=GetNode(node);
    if(pnode->Search(key,index)){
        if(pnode->GetIsLeaf()){
            ret.flag=true;
            ret.index=index;
            ret.pnode=pnode;
        }else{
            pnode=GetNode(pnode->GetValues(index));
        }
    }


    return ret;
}
BPlusTreeNode* BPlusTree::GetNode(int num){
    BPlusTreeNode * pnode=new BPlusTreeNode(false,this,num);
    return pnode;
}

bool BPlusTreeNode::Search(Tkey key,int &index){
    bool ret=false;
    if(GetCount()==0){
        index=0;
        return false;
    }
    if(GetKeys(0) > key ){
        index=0;
        return false;
    }
    if(GetKeys(GetCount()-1)<key){
        index=GetCount();
        return false;
    }
    if(GetCount()>20){
        int m,s,e;
        s=0;
        e=GetCount()-1;
        while(s<e){
            m=(s+e)/2;
            if(key==GetKeys(m)){
                index=m;
                return true;
            }else if(key<GetKeys(m)){
                e=m;
            }else{
                s=m;
            }
            if(s==e-1){
                if(key==GetKeys(s)){
                    index=s;
                    return true;
                }
                if(key==GetKeys(e)){
                    index=e;
                    return true;
                }
                if(key<GetKeys(s)){
                    index=s;
                    return false;
                }
                if(key<GetKeys(e)){
                    index=e;
                    return false;
                }
                if(key>GetKeys(e)){
                    index=e+1;
                    return false;
                }
            }

        }
        return false;
    }else{
        for(int i=0;i<GetCount();i++){
            if(key<GetKeys(i)){
                index=i;
                ret=false;
                break;
            }else if(key==GetKeys(i)){
                index=i;
                ret=true;
                break;
            }
        }
        return ret;
    }
}
int BPlusTreeNode::GetCount(){return *((int*)(&buffer_[4]));}
bool BPlusTreeNode::GetIsLeaf(){return GetNodeType()==1;}
int BPlusTreeNode::GetNodeType(){
    int val;
    val=*((int*)(&buffer_[0]));
    return val;
}


Tkey BPlusTreeNode::GetKeys(int index){
    Tkey k(tree_->idx()->key_type(),tree_->idx()->key_len());
    int base=12;
    int lenr=4+tree_->idx()->key_len();
    memcpy(k.key(),&buffer_[base+index*lenr+4],tree_->idx()->key_len());
    return k;
}