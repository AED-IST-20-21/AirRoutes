# AirRoutes
#
# To compile progs:
# 	make
#
# --------------------------------------------------------------
#  	Compiler, Compiler Flags

CC = gcc
CFLAGS = -g -Wall -std=c99

#	Sources
SOURCES = main.c FilOp.c Graph.c

#	Objects
OBJECTS = main.o FileOp.o Graph.o

backbone: $(OBJECTS) $(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c FileOp.h

FileOp.o: FileOp.c FileOp.h

Graph.o: Graph.c Graph.h

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

