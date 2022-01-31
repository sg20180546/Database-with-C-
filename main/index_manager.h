#ifndef MINIDB_INDEX_MANAGER_H_
#define MINIDB_INDEX_MANAGER_H_

#include <string>

#include "catalog_manager.h"
#include "sql_statement.h"
#include "buffer_manager.h"
class BPlusTree;
class BPlusTreeNode;
// https://velog.io/@mongle/Data-structure-B-tree-B-tree
// https://velog.io/@emplam27/자료구조-그림으로-알아보는-B-Tree
class IndexManager{
private:
    BufferManager *hdl_;
    CatalogManager *cm_;
    std::string db_name_;
    public:
        IndexManager(CatalogManager *cm,BufferManager* hdl ,std::string db){
            hdl_=hdl;
            cm_=cm;
            db_name_=db;
        }
        ~IndexManager(){}
        void CreateIndex(SQLCreateIndex &st);
};


typedef struct{
    BPlusTreeNode* pnode;
    int index;
    bool flag;
}FindNodeParam;

class BPlusTree{
private:
    Index *idx_;
    int degree_;
    BufferManager *hdl_;
    CatalogManager *cm_;
    std::string db_name_;

public:
    BPlusTree(Index* idx,BufferManager* hdl,CatalogManager *cm,std::string db_name){
        hdl_=hdl;
        cm_=cm;
        idx_=idx;
        db_name_=db_name;
        degree_=2*idx_->rank()+1;
    }
    ~BPlusTree(){}
    Index *idx(){return idx_;}
    int degree(){return degree_;}
    BufferManager* hdl(){return hdl_;}
    CatalogManager* cm(){return cm_;}
    std::string db_name(){return db_name_;}

    bool Add(Tkey &key,int block_num,int offset);
    bool AdjustAfterAdd(int node);

    bool Remove(Tkey key);
    bool AdjustAfterRemove(int node);

    FindNodeParam Search(int node, Tkey &key);
    FindNodeParam SearchBranch(int node, Tkey &key);
    BPlusTreeNode * GetNode(int num);
    int GetVal(Tkey key);

    int GetNewBlockNum(){return idx_->IncreaseMaxCount();}
    void Print();
    void PrintNode(int num);
private:
    void InitTree();
};
class BPlusTreeNode{

private:
    BPlusTree* tree_;
    int block_num_;
    int rank_;
    // what is buffer?
    char* buffer_;
    bool is_leaf_;
    bool is_new_node_;
public:
    BPlusTreeNode(bool isnew,BPlusTree* tree, int blocknum,bool newleaf=false);
    ~BPlusTreeNode(){}
    int block_num(){return block_num_;}
    Tkey GetKeys(int i);
    int GetValues(int i);
    int GetNextLeaf();
    int GetParent();
    int GetNodeType();
    int GetCount();
    bool GetIsLeaf();

    void SetKeys(int i,Tkey key);
    void SetValues(int i, int val);
    void SetNextLeaf(int val);
    void SetParent(int val);
    void SetNodeType(int val);
    void SetCount(int val);
    void SetIsLeaf(bool val);

    void GetBuffer();

    bool Search(Tkey key,int & index);
    int Add(Tkey &key);
    int Add(Tkey &key,int &val);
    BPlusTreeNode *Split(Tkey &key);
    bool IsRoot(){
        if(GetParent()!=-1) return false;
        return true;
    }
    bool RemoveAt(int indx);

    void Print();

};

#endif