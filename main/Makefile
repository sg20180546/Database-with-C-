main.out:
	g++ -o main main.cc minidb_api.cc interpreter.cc catalog_manager.cc sql_statement.cc -lboost_filesystem -lboost_regex -lreadline -lboost_serialization

# main.out:
# 	g++ block_handle.cc block_info.cc buffer_manager.cc catalog_manager.cc file_handle.cc file_info.cc index_manager.cc interpreter.cc main.cc minidb_api.cc record_manager.cc sql_statement.cc -lboost_filesystem -lreadline -lboost_serialization


# main.o : main.cc interpreter.h interpreter.o
# 	g++ -c -o main.o main.cc interpreter.o -lreadline -lboost_algorithm

# interpreter.o : interpreter.cc interpreter.h exceptions.h minidb_api.h minidb_api.o
# 	g++ -c -o interpreter.o interpreter.cc minidb_api.o -lreadline -lboost_algorithm -lboost_regex -lboost_filesystem

# minidb_api.o : minidb_api.cc minidb_api.h exceptions.h
# 	g++ -c -o minidb_api.o minidb_api.cc -lboost_filesystem


# main.out: main.o interpreter.o minidb_api.o sql_statement.o catalog_manager.o interpreter.h
# 	g++ -o main.out main.o interpreter.o minidb_api.o catalog_manager.o sql_statement.o -lreadline

# main.o : main.cc interpreter.h interpreter.o
# 	g++ -c -o main.o main.cc interpreter.o -lreadline -lboost_algorithm

# interpreter.o : interpreter.cc minidb_api.o sql_statement.o interpreter.h exceptions.h minidb_api.h sql_statement.h
# 	g++ -c -o interpreter.o interpreter.cc minidb_api.o sql_statement.o -lreadline -lboost_algorithm -lboost_regex -lboost_filesystem




# catalog_manager.o : catalog_manager.cc catalog_manager.h sql_statement.h
# 	g++ -c -o catalog_manager.o catalog_manager.cc -lreadline -lboost_filesystem -lboost_archive -lboost_serialization

# sql_statement.o : sql_statement.cc sql_statement.h exceptions.h catalog_manager.h
# 	g++ -c -o sql_statement.o sql_statement.cc -lreadline -lboost_algorithm


# -Lusr/lib/x86_64-linux-gnu