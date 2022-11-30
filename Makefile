PROJ_NAME=Patriciatree
Compiler=g++
compile: main.o FILEHANDLER.o NODES.o PATRICIATREE.o
	$(Compiler) main.o FILEHANDLER.o NODES.o PATRICIATREE.o -o $(PROJ_NAME).out
main.o: main.cpp
	@echo 'Compilando o arquivo main'
	g++ main.cpp -c
FILEHANDLER.o: FILEHANDLER.cpp
	@echo 'Compilando o arquivo FileHandler'
	g++ FILEHANDLER.cpp -c
NODES.o: NODES.cpp
	@echo 'Compilando o arquivo Nodes'
	g++ NODES.cpp -c
PATRICIATREE.o: PATRICIATREE.cpp
	@echo 'Compilando o arquivo PATRICIATREE'
	g++ PATRICIATREE.cpp -c
clear: main.o  FILEHANDLER.o NODES.o PATRICIATREE.o
	rm *.o *.out 
erasedb:
	rm *.dat