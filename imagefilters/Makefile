CC=g++
OUTNAME=imagefilter
# LIBDIRS=
LIBS=jpeg
CFLAGS= --std=c++0x -g -l $(LIBS)
OBJECTS= imagereader.o imagewriter.o imageops.o 

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o imagefilter $(OBJECTS)

rebuild: clean $(OBJECTS)
	$(CC) $(CFLAGS) -o imagefilter $(OBJECTS)

clean:
	-rm *.o
	cd tests/ ; make cleanup

%.o: %.cpp
	$(CC) $(CFLAGS) -o $*.o -c $*.cpp

test: $(OBJECTS)
	cd tests/ ; make tests