#include "sql_statement.h"

#include <iomanip>
#include <iostream>

#include <boost/algorithm/string.hpp>

// #include "commons.h"
#include "exceptions.h"

using namespace boost::algorithm;
using namespace std;


void SQLCreateDatabase::Parse(std::vector<std::string> sql_vector){
    sql_type_=30;
    if(sql_vector.size()<=2){
        throw SyntaxErrorException();
    }else{
        std::cout<<"DB NAME: "<<sql_vector[2]<<std::endl;
        db_name_=sql_vector[2];
    }
}