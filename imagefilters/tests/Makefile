
include ../Makefile

INCLUDES= -I "../"
DEPS= ../imagereader.o ../imagewriter.o ../imageops.o ../bwfilter.o
PROGS= rwtest bwtest

tests: $(PROGS)
	@echo "done making tests!"

# change this to something more clever (DRY)
rwtest:
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIR) -o rwtest rwtest.cpp $(DEPS)

bwtest:	
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIR) -o bwtest bwtest.cpp $(DEPS)

cleanup:
	-rm $(PROGS)
