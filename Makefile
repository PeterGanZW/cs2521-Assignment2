# Makefile for Ass2

CC = gcc
CFLAGS =  -Wall -std=c11 -Werror -g
AR = ar
objs = Graph.o GraphVis.o CentralityMeasures.o PQ.o Dijkstra.o lance.o LanceWilliamsHAC.o

all : testGraph testPQ testDijkstra testCentralityMeasures testL testLance

$(objs) : %.o : %.c

GraphLib.a : $(objs)
	$(AR) rcs $@ $^

testGraph : testGraph.c GraphLib.a
	$(CC) -o testGraph testGraph.c GraphLib.a -lm

testPQ : testPQ.c PQ.o
	$(CC) -o testPQ  testPQ.c PQ.o -lm

testLance : testLance.c GraphLib.a
	$(CC) -o testLance testLance.c LanceWilliamsHAC.c GraphLib.a -lm


testDijkstra : testDijkstra.c GraphLib.a
	$(CC) -o  testDijkstra testDijkstra.c GraphLib.a -lm

testCentralityMeasures : testCentralityMeasures.c GraphLib.a
	$(CC) -o testCentralityMeasures testCentralityMeasures.c GraphLib.a -lm

clean :
	rm -f *.o testCentralityMeasures testDijkstra testGraph testPQ testLance GraphLib.a

