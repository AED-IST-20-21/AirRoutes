# AirRoutes
#
# To compile progs:
# 	make
#
# --------------------------------------------------------------
#  	Compiler, Compiler Flags
CC = gcc 
DB = gdb
CFLAGS = -g -Wall -std=c99

OBJECTS = main.o FileOp.o Graph.o List.o

EXE = backbone

#Test file
TEST = .routes0

#Temporary Object Files
TMPOBJECTS = main.c FileOp.c FileOp.h

backbone: main.o FileOp.o Graph.o List.o
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c ListGraph.h Zero.h

FileOp.o: FileOp.c FileOp.h ListGraph.h

Graph.o: ListGraph.c ListGraph.h

List.o: Zero.c Zero.h FileOp.h ListGraph.h

clean:
	rm -f *.o backbone temp

VALG = valgrind --leak-check=full

FILES = $(shell ls ../test/*.txt)

#
valgrind: $(EXE)
	$(CC) $(VALG) ./$(EXE) $(TEST)
#
debug: $(EXE)
	$(DB) ./$(EXE)
#
temp: $(TMPOBJECTS)
	$(CC) $(CFLAGS) -o $@ $(TMPOBJECTS)


t:
	for F in ${FILES}; do  ./backbone $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./backbone $${F} ; done;


tt:
	for F in ${FILES}; do  time ./backbone $${F} ; done;

