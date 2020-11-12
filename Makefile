# AirRoutes
#
# To compile progs:
# 	make
#
# --------------------------------------------------------------
#  	Compiler, Compiler Flags
CC = gcc -g -Wall -std=c99


backbone: main.o FileOp.o Graph.o
	$(CC)

main.o: main.c FileOp.h
	$(CC)

FileOp.o: FileOp.c FileOp.h
	$(CC)

Graph.o: Graph.c Graph.h
	$(CC)

clean:
	rm -f *.o backbone

VALG = valgrind --leak-check=full

FILES = $(shell ls ../test/*.txt)

t:
	for F in ${FILES}; do  ./backbone $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./backbone $${F} ; done;


tt:
	for F in ${FILES}; do  time ./backbone $${F} ; done;

