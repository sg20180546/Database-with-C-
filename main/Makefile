main.out: main.o interpreter.o minidb_api.o sql_statement.o catalog_manager.o
	g++ -o main.out main.o interpreter.o minidb_api.o catalog_manager.o sql_statement.o -lreadline -lboost_system

main.o : main.cc interpreter.h interpreter.o
	g++ -c -o main.o main.cc interpreter.o -lreadline -lboost_system

interpreter.o : interpreter.cc minidb_api.o sql_statement.o interpreter.h exceptions.h minidb_api.h sql_statement.h
	g++ -c -o interpreter.o interpreter.cc minidb_api.o sql_statement.o -lreadline -lboost_system

minidb_api.o : minidb_api.cc catalog_manager.o sql_statement.o minidb_api.h exceptions.h sql_statement.h catalog_manager.h 
	g++ -c -o minidb_api.o minidb_api.cc sql_statement.o -lreadline -lboost_system


catalog_manager.o : catalog_manager.cc sql_statement.o catalog_manager.h sql_statement.h
	g++ -c -o catalog_manager.o catalog_manager.cc sql_statement.o -lreadline -lboost_system

sql_statement.o : sql_statement.cc sql_statement.h exceptions.h catalog_manager.h
	g++ -c -o sql_statement.o sql_statement.cc -lreadline -lboost_system

