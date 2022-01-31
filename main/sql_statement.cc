#include "sql_statement.h"

#include <iomanip>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include "commons.h"
#include "exceptions.h"

using namespace boost::algorithm;
using namespace std;


std::ostream &operator<<(std::ostream &out, const Tkey &object){
    switch(object.key_type_){
        case 0:{
        }break;
        case 1:{
            float a;
            memcpy(&a,object.key_,object.length_);
            cout<<setw(9)<<left<<a;
        } break;
        case 2:{
            cout<<setw(9)<<left<<object.key_;
        } break;
    }
    return out;
}


int SQL::ParseDataType(std::vector<std::string> sql_vector,Attribute &attr,unsigned int pos){
    boost::algorithm::to_lower(sql_vector[pos]);
    if(sql_vector[pos]=="int"){
        std::cout<<"TYPE: "
                <<"int"<<std::endl;
        attr.set_data_type(T_INT);
        attr.set_length(4);
        pos++;
    }
    if(sql_vector[pos]==","){
        pos++;
    }else if(sql_vector[pos]=="float"){
        std::cout<<"TYPE: "<<"float"<<std::endl;
        attr.set_data_type(T_FLOAT);
        attr.set_length(4);
        if(sql_vector[pos]==","){
            pos++;
        }
    }else if(sql_vector[pos]=="char"){
        attr.set_data_type(T_CHAR);
        pos++;
        if(sql_vector[pos]=="("){
            pos++;
        }
        attr.set_length(atoi(sql_vector[pos].c_str()));
        pos++;
        if(sql_vector[pos]==")"){
            pos++;
        }
        if(sql_vector[pos]==","){
            pos++;
        }
    }else{
        throw SyntaxErrorException();
    }
    return pos;
    // error can be occur in char
}


void SQLCreateDatabase::Parse(std::vector<std::string> sql_vector){
    sql_type_=30;
    if(sql_vector.size()<=2){
        throw SyntaxErrorException();
    }else{
        std::cout<<"DB NAME: "<<sql_vector[2]<<std::endl;
        db_name_=sql_vector[2];
    }
}

void SQLCreateTable::Parse(std::vector<std::string> sql_vector){
    // CREATE {TABLENAME} ((PRIMARY KEY) {columnname} char)
    sql_type_=31;
    unsigned int pos=2;
    bool is_attr=true;
    if(sql_vector.size()<=pos){
        throw SyntaxErrorException();
    }
    std::cout<<"TABLE NAME: "<<sql_vector[pos]<<std::endl;
    tb_name_=sql_vector[pos];
    pos++;
    if(sql_vector[pos]!="("){
        throw SyntaxErrorException();
    }
    pos++;
    bool has_pk=false;
    while(is_attr){
        is_attr=false;
        if(sql_vector[pos]=="primary"){
            pos++;
            if(sql_vector[pos]!="key") throw SyntaxErrorException();
        
        pos++;
        if(has_pk){
            throw SyntaxErrorException();
        }
        if(sql_vector[pos]!="("){
            throw SyntaxErrorException();
        }
        pos++;
        for(unsigned int i=0;i<attrs_.size();++i){
            if(attrs_[i].attr_name()==sql_vector[pos]){
                attrs_[i].set_attr_type(1);
                std::cout<<"PRIMARY KEY: "<<sql_vector[pos]<<std::endl;
            }
        }
        pos++;
        if(sql_vector[pos]!=")"){
            throw SyntaxErrorException();
        }
        has_pk=true;
    }else{
        std::cout<<"COLUMN: "<<sql_vector[pos]<<std::endl;
        Attribute attr;
        attr.set_attr_name(sql_vector[pos]);
        pos++;
        pos=ParseDataType(sql_vector,attr,pos);
        attrs_.push_back(attr);
        if(sql_vector[pos]!=")"){
            is_attr=true;
        }
        }
    }
}

void SQLCreateIndex::Parse(std::vector<std::string> sql_vector){
    sql_type_=32;
    unsigned int pos=2;
    if(sql_vector.size()<=pos){
        throw SyntaxErrorException();
    }
    std::cout<<"INDEX NAME: "<<sql_vector[pos]<<std::endl;
    index_name_=sql_vector[pos];
    pos++;
    if(to_lower_copy(sql_vector[pos])!="on"){
        throw SyntaxErrorException();
    }
    pos++;
    std::cout<<"TABLE NAME: "<<sql_vector[pos]<<std::endl;
    tb_name_=sql_vector[pos];
    pos++;
    if(to_lower_copy(sql_vector[pos]!="(")){
        throw SyntaxErrorException();
    }
    pos++;
    std::cout<<"COLUMN NAME: "<<sql_vector[pos]<<std::endl;
    col_name_=sql_vector[pos];
    pos++;
    if(to_lower_copy(sql_vector[pos])!=")"){
        throw SyntaxErrorException();
    }
    pos++;
}

void SQLUse::Parse(std::vector<std::string> sql_vector){
    sql_type_=60;
    if(sql_vector.size()<=1){
        throw SyntaxErrorException();
    }else{
        std::cout<<"DB NAME "<<sql_vector[1]<<std::endl;
        db_name_=sql_vector[1];
    }
}

void SQLInsert::Parse(std::vector<std::string> sql_vector){
    // "INSERT INTO {TABLENAME} ("
    sql_type_=70;
    unsigned int pos=1;
    bool is_attr=true;
    if(to_lower_copy(sql_vector[pos])!="into"){
        throw SyntaxErrorException();
    }
    pos++;
    cout<<"TABLE NAME: "<<sql_vector[pos]<<endl;
    pos++;
    if(to_lower_copy(sql_vector[pos])!="("){
        throw SyntaxErrorException();
    }
    pos++;
    while(is_attr){
        is_attr=false;
        SQLValue sql_value;
        std::string value=sql_vector[pos];
        if(value.at(0)='\''||value.at(0)=='\"'){
            // ??
            value.assign(value,1,value.length()-2);
            sql_value.data_type=2;
        }else{
            if(value.find(".")!=string::npos){
                sql_value.data_type=1;
            }else{
                sql_value.data_type=0;
            }
        }
        sql_value.value=value;
        cout<<sql_value.data_type<<" : "<<value<<endl;
        pos++;
        values_.push_back(sql_value);
        if(sql_vector[pos]!=")"){
            is_attr=true;
        }
        pos++;
    }
}