#include "Graphe.h"
#include <iostream>
#include <time.h>

int main(int argc, char ** argv){

    srand(time(NULL));

    // if(argv[1] == nullptr) {
    //     std::cout << "il manque des arguments pour que le programme fonctionne," << std::endl
    //     << "SVP regardez le README.md" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    Graphe g("carte.txt");
    // std::cout << argv[1] << std::endl;
    g.afficher();

    voronoi(g, 76);

    
    return 0;
}