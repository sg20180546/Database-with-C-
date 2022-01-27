#include "interpreter.h"

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "exceptions.h"
#include "minidb_api.h"

using namespace std;

Interpreter::Interpreter() : sql_type_(-1) {
    // std::string p="/home/gs201/Desktop/db/";
  string p = string(getenv("MiniEnv"));
    api= new MiniDBAPI(p);
}

Interpreter::~Interpreter() { delete api; }

vector<string> split(string str,string sep){
    char *cstr=const_cast<char*>(str.c_str());
    char *current;
    vector <string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

void Interpreter::FormatSQL(){
    boost::regex reg("[\r\n\t]");
    // reg=;
    sql_statement_=boost::regex_replace(sql_statement_,reg," ");

    reg=";.*$";
    sql_statement_=boost::regex_replace(sql_statement_,reg,"");

    reg="(^ +)|( +$)";
    sql_statement_=boost::regex_replace(sql_statement_,reg,"");

    reg=" +";
    sql_statement_=boost::regex_replace(sql_statement_,reg," ");

    reg=" ?(\\(|\\)|,|=|(<>)|<|>) ?";
    sql_statement_=boost::regex_replace(sql_statement_,reg," $1 ");
    reg="< *>";
    sql_statement_=boost::regex_replace(sql_statement_,reg,"<>");
    reg="< *=";
    sql_statement_=boost::regex_replace(sql_statement_,reg,"<=");
    reg="> *=";
    sql_statement_=boost::regex_replace(sql_statement_,reg,">=");

    sql_vector_=split(sql_statement_," ");
}

void Interpreter::TellSQLType(){
    if(sql_vector_.size()==0){
        sql_type_=-1;
        cout<<"SQL TYPE: #EMPTY#"<<endl;
        return;
    }
    boost::algorithm::to_lower(sql_vector_[0]);
    if(sql_vector_[0]=="quit"){
        cout<<"SQL TYPE: #QUIT#"<<endl;
        sql_type_=10;
    }
    else if(sql_vector_[0]=="help"){
        cout<<"SQL TYPE: #HELP#"<<endl;
        sql_type_=20;
    }
    else if(sql_vector_[0]=="create"){
        boost::algorithm::to_lower(sql_vector_[1]);
        if(sql_vector_[1]=="database"){
            cout<<"SQL TYPE #CREATE DATABASE#"<<endl;
            sql_type_=30;
        }else if(sql_vector_[1]=="table"){
            cout<<"SQL_TYPE: #CREATE TABLE#"<<endl;
            sql_type_=31;
        }else if(sql_vector_[1]=="index"){
            cout<<"SQL_TYPE: #CREATE INDEX#"<<endl;
            sql_type_=32;
        }else{
            sql_type_=-1;
        }
    }else if(sql_vector_[0]=="show"){
        boost::algorithm::to_lower(sql_vector_[1]);
        if(sql_vector_[1]=="databases"){
            cout<<"SQL TYPE: #SHOW DATABASES#"<<endl;
            sql_type_=40;
        }else if(sql_vector_[1]=="tables"){
            cout<<"SQL_TYPE: #SHOW TABLES#"<<endl;
            sql_type_=41;
        }else{
            sql_type_=-1;
        }
    }else if(sql_vector_[0]=="drop"){
        boost::algorithm::to_lower(sql_vector_[1]);
        if(sql_vector_[1]=="database"){
            cout<<"SQL TYPE: #DROP DATABASE#"<<endl;
            sql_type_=50;
        }else if(sql_vector_[1]=="table"){
            cout<<"SQL TYPE: #DROP TABLE#"<<endl;
            sql_type_=51;
        }else if(sql_vector_[1]=="index"){
            cout<<"SQL TYPE: #DROP INDEX#"<<endl;
            sql_type_=52;
        }else{
            sql_type_=-1;
        }
    }else if(sql_vector_[0]=="use"){
        cout<<"SQL TYPE: #USE#"<<endl;
        sql_type_=60;

    }else if(sql_vector_[0]=="insert"){
        cout<<"SQL TYPE: #INSERT#"<<endl;
        sql_type_=70;
    }else if(sql_vector_[0]=="exec"){
        cout<<"SQL TYPE: #EXEC#"<<endl;
        sql_type_=80;
    }else if(sql_vector_[0]=="select"){
        cout<<"SQL TYPE: #SELECT#"<<endl;
        sql_type_=90;
    }else if(sql_vector_[0]=="delete"){
        cout<<"SQL TYPE: #DELETE#"<<endl;
        sql_type_=100;
    }else if(sql_vector_[0]=="update"){
        cout<<"SQL TYPE:: #UPDATE#"<<endl;
        sql_type_=110;
    }else{
        sql_type_=-1;
        cout<<"SQL TYPE: #UNKNOWN#"<<endl;
    }
}
void Interpreter::Run(){
    try{
        switch(sql_type_){
            case 10:{
                api->Quit();
                exit(0);
            } break;
            case 20:{
                api->Help();
            } break;
            case 30:{
                SQLCreateDatabase *st=new SQLCreateDatabase(sql_vector_);
                api->CreateDatabase(*st);
                delete st;
            } break;
            case 31:{
                SQLCreateTable *st= new SQLCreateTable(sql_vector_);
                api->CreateTable(*st);
                delete st;
            }
            case 32: {
                SQLCreateIndex *st= new SQLCreateIndex(sql_vector_);
                // 
            }break;
            case 60:{
                SQLUse* st=new SQLUse(sql_vector_);
                api->Use(*st);
                delete st;
            }
            default:
             break;
        }
    }catch(SyntaxErrorException &e){
        cerr<<"SynTax Error!"<<endl;
    }
}

void Interpreter::ExecSQL(string statement){
    sql_statement_=statement;
    FormatSQL();
    TellSQLType();
    cout<<"SQL STATEMENT "<<sql_statement_<<endl;
    Run();
    cout<<endl;
}
