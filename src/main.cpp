#include "Graphe.h"
#include <iostream>
#include <time.h>

int main(int argc, char ** argv){

    srand(time(NULL));

    if(argv[1] == nullptr) exit(EXIT_FAILURE);
    Graphe g(argv[1]);
    std::cout << argv[1] << std::endl;
    int indice =7;
    std::cout << g.altitude(indice) << std::endl;
    std::cout << g.altitude(g.voisin(indice , EST)) << std::endl;
    g.afficher();
    
    dijkstra(g, rand()%g.getLC());

    
    return 0;
}