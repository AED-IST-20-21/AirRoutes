# AirRoutes
#
# To compile progs:
# 	make
#
# --------------------------------------------------------------
#  	Compiler, Compiler Flags
CC = gcc 
DB = gdb
CFLAGS = -O3 -Wall -std=c99

OBJECTS = main.o FileOp.o ListGraph.o Zero.o

EXE = backbone

#Test file
TEST = enunciado_mix.routes0

#Temporary Object Files
TMPOBJECTS = main.c FileOp.c FileOp.h

backbone: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c ListGraph.h Zero.h FileOp.h

FileOp.o: FileOp.c FileOp.h ListGraph.h

ListGraph.o: ListGraph.c ListGraph.h

Zero.o: Zero.c Zero.h FileOp.h ListGraph.h

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

