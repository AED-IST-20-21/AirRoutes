# AirRoutes
#
# To compile progs:
# 	make
#
# --------------------------------------------------------------
#  	Compiler, Compiler Flags



backbone: main.o FileOp.o Graph.o
	gcc -g -Wall -std=c99

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

