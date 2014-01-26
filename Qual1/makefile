CC      = g++
CFLAGS  =
LDFLAGS =

all: gcj clean

gcj: GCJ.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

GCJ.o: GCJ.cpp GCJ.hpp
	$(CC) -c $(CFLAGS) $<
    
main.o: main.cpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm gcj