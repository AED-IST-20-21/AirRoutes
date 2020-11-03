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
SOURCES = main.c interface.c

#	Objects
OBJECTS = main.o interface.o

backbone: $(OBJECTS) $(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c interface.h

interface.o: interface.c interface.h

clean:
	rm -f *.o backbone

VALG = valgrind --leak-check=full

t:
	for F in ${FILES}; do  ./backbone $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./backbone $${F} ; done;


tt:
	for F in ${FILES}; do  time ./backbone $${F} ; done;

