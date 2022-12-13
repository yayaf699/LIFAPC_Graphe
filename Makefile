all: bin/main

CC= g++
CFLAGS= -ggdb -Wall
OBJ= obj/main.o obj/Graphe.o

bin/main: $(OBJ)
	$(CC) $(OBJ) -o $@

obj/main.o: src/main.cpp src/Graphe.h
	$(CC) $(CFLAGS) -o $@ -c src/main.cpp

obj/Graphe.o: src/Graphe.cpp src/Graphe.h
	$(CC) $(CFLAGS) -o $@ -c src/Graphe.cpp

clean:
	rm bin/main obj/*.o data/voronoi.* data/voronoiLivraison.*
