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

#vpath = /mnt/c/Users/UX430UA/Desktop/Tests_AED

OBJECTS = main.o FileOp.o ListGraph.o Zero.o One.o VectorGraph.o Kruskal.o Graph.o

EXE = backbone

#Test file
TEST = 15_020C.routes

#Temporary Object Files
TMPOBJECTS = main.c FileOp.c FileOp.h

backbone: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c Zero.h FileOp.h One.h

FileOp.o: FileOp.c FileOp.h Graph.h

Zero.o: Zero.c Zero.h FileOp.h ListGraph.h Graph.h

One.o: One.c One.h FileOp.h VectorGraph.h Kruskal.h Graph.h

ListGraph.o: ListGraph.c ListGraph.h Graph.h

VectorGraph.o: VectorGraph.c VectorGraph.h FileOp.h Kruskal.h

Kruskal.o: Kruskal.c Kruskal.h Graph.h

Graph.o: Graph.c Graph.h

clean:
	rm -f *.o backbone temp

VALG = valgrind --leak-check=full --show-leak-kinds=all -s


FILES = $(shell ls ../test/*.routes0)

ZIP = $(zip AirRoutes main.c FileOp.c ListGraph.c Zero.c FileOp.h ListGraph.h Zero.h Makefile)
#
zip: $(EXE)
	$(ZIP)

#
valgrind: $(EXE)
	$(VALG) ./$(EXE) $(TEST)
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

