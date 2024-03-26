#flip is the executable for file
TARGET= flip 
#gcc needed flags are stored inside CFLAG
CFLAG= -Wall -DBSD -DNDEBUG
CC = gcc
# the all, clean are standard targets 
all: $(TARGET)
#once called the exe creates the obj files , file.o getopt.o
$(TARGET): flip.o getopt.o
	$(CC) $(CFLAG) -o $@ flip.o getopt.o
#action line uses gcc to compile the files
flip.o: flip.c flip.h
	$(CC) $(CFLAG) -c $*.c

getopt.o: getopt.c flip.h
	$(CC) $(CFLAG) -c $*.c


clean:
	rm -rf *.o $(TARGET)

flip.man: flip.1
	nroff -man flip.1>flip.man