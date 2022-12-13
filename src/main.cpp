#include "Graphe.h"
#include <iostream>
#include <time.h>

int main(int argc, char ** argv){

    srand(time(NULL));
    std::vector<std::vector<double>> distances;
    std::vector<Coordonnees>co;
    std::vector<Color>couleurs;

    // if(argv[1] == nullptr) {
    //     std::cout << "il manque des arguments pour que le programme fonctionne," << std::endl
    //     << "SVP regardez le README.md" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    Graphe g("test.txt");
    // std::cout << "Graphe recupere depuis " << argv[1] << std::endl;

    std::cout << "Graphe initial :" << std::endl;
    g.afficher();

    recupere_coordonnees("coordtest.txt", co);
    for(int i = 0; i < (int)co.size(); ++i){
        couleurs.push_back({rand()%256, rand()%256, rand()%256});
    }

    distances = dijkstra(g, co);
    
    voronoi(g, distances, couleurs); 


    voronoiLivraison(g, distances, couleurs);                  

    
    return 0;
}