CC=g++
OUTNAME=imagefilter
# LIBDIRS=
LIBS=jpeg
CFLAGS= --std=c++0x -g -l $(LIBS)
OBJECTS= imagereader.o imagewriter.o imageops.o main.o 

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o imagefilter $(OBJECTS)

rebuild: clean $(OBJECTS)
	$(CC) $(CFLAGS) -o imagefilter $(OBJECTS)

clean:
	-rm *.o

%.o: %.cpp
	$(CC) $(CFLAGS) -o $*.o -c $*.cpp
