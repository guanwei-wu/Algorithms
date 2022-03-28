# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O3 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/cb
bin/cb	: main.o
	$(CC) $(OPTFLAGS) main.o -o bin/cb
main.o	: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*