#ifndef MINIDB_EXCEPTIONS_H_
#define MINIDB_EXCEPTIONS_H_

#include <exception>

class SyntaxErrorException:public std::exception{};

class NoDatabaseSelectedException: public std::exception{};

class DataBaseNotExistException:public std::exception{};

class DatabaseAlreadyExistsException : public std::exception{};

class TableNotExistException:public std::exception{};

class TableAlreadyExistsException: public std::exception{};


#endif