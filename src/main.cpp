#include "Graphe.h"
#include <iostream>
#include <time.h>

int main(int argc, char ** argv){

    srand(time(NULL));

    int departs = 1;
    if(argv[1] == nullptr) exit(EXIT_FAILURE);
    Graphe g(argv[1]);
    std::cout << argv[1] << std::endl;
    g.afficher();

    dijkstra(g, departs);

    
    return 0;
}