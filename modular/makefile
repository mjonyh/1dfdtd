CC=gcc
CFLAGS=-I -Wall-03
DEPS = ezinc.h fdtd.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fdtdmake: ezinc.o update.o abc.o snapshot.o tfsf.o gridinit.o main.o 
	$(CC) ezinc.o update.o abc.o snapshot.o tfsf.o gridinit.o main.o -o fdtd -lm
	rm -r *.o

clean_all:
	rm -rv *.log fdtd
