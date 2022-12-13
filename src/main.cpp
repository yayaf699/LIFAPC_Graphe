#include "Graphe.h"
#include <iostream>
#include <time.h>

int main(int argc, char ** argv){

    srand(time(NULL));
    //on initialise tout ce dont on a bestoin
    std::vector<std::vector<double>> distances;
    std::vector<Coordonnees>co;
    std::vector<Color>couleurs;

    if(argv[1] == nullptr && argv[2] == nullptr) {
        std::cout << "il manque des arguments pour que le programme fonctionne," << std::endl
        << "SVP regardez le README.md" << std::endl;
        exit(EXIT_FAILURE);
    }
    //initialisation de la grille depuis le fichier
    Graphe g(argv[1]);
    std::cout << "Graphe recupere depuis " << argv[1] << std::endl;

    std::cout << "Graphe initial :" << std::endl;
    g.afficher();

    recupere_coordonnees(argv[2], co);
    for(int i = 0; i < (int)co.size(); ++i){
        couleurs.push_back({rand()%256, rand()%256, rand()%256});
    }

    std::cout << "coordonnees et couleurs recuperees" << std::endl;

    std::cout << "recuperation des distances, lancement de l'algo de dijkstra:" << std::endl;
    distances = dijkstra(g, co);
    std::cout << "distances recuperees" << std::endl;
    
    std::cout << "creation du diagramme de voronoi:" << std::endl;
    voronoi(g, distances, couleurs); 
    std::cout << "voronoi OK!" << std::endl;

    std::cout << "creation du diagramme de voronoi avec variations de cout kilometriques: " << std::endl;
    voronoiLivraison(g, distances, couleurs);      
    std::cout << "voronoiLivraison OK!" << std::endl;


    std::cout << "les resultats se trouvent dans le dossier data" << std::endl;         

    
    return 0;
}