compile: main.o FILEHANDLER.o NODES.o PATRICIATREE.o
	g++ main.o FILEHANDLER.o NODES.o PATRICIATREE.o
main.o: main.cpp
	g++ main.cpp -c
FILEHANDLER.o: FILEHANDLER.cpp
	g++ FILEHANDLER.cpp -c
NODES.o: NODES.cpp
	g++ NODES.cpp -c
PATRICIATREE.o: PATRICIATREE.cpp
	g++ PATRICIATREE.cpp -c
clear: main.o  FILEHANDLER.o NODES.o PATRICIATREE.o
	rm *.o *.out