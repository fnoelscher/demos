
include ../Makefile

INCLUDES= -I "../"
LIBDIR= -L "../"
DEPS= ../imagereader.o ../imagewriter.o ../imageops.o
PROGS= rwtest

tests: $(PROGS)
	@echo "done making tests!"

# change this to something more clever (DRY)
rwtest:
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIR) -o rwtest rwtest.cpp $(DEPS)

cleanup:
	-rm $(PROGS)