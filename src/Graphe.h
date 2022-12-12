#ifndef _GRAPHE_H
#define _GRAPHE_H

#include <vector>

enum Direction {EST = 0, NORD = 1, OUEST = 2, SUD = 3};

struct N_D{
    int precedent;
    double distance;

    bool operator<(const N_D& n) const{
        return this->distance < n.distance;
        }

    N_D(int _prec, int _dist): precedent(_prec), distance(_dist){}
};

struct Color{
    unsigned char r, g, b;

    Color(unsigned char _r, unsigned char _g, unsigned char _b): r(_r), g(_g), b(_b){}
};

class Graphe{

    private:

public:
    int L, C;
    std::vector<int> Terrain;

    

    Graphe(unsigned int L, unsigned int C);

    Graphe(const char* file);


    ~Graphe();

    int getLC() const;

    int altitude(int indice) const;

    int indice(unsigned int i, unsigned int j) const;

    int ligne(int indice) const;

    int colonne(int indice) const;

    int voisin(int indice, Direction dir) const;

    void afficher() const;


};




std::vector<double> dijkstra(Graphe g, int departs);

std::vector<int> voronoi(Graphe g, int nb_departs);


#endif