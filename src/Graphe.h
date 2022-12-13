#ifndef _GRAPHE_H
#define _GRAPHE_H

#include <vector>

enum Direction {EST = 0, NORD = 1, OUEST = 2, SUD = 3};

struct N_D
    {
        int noeud;
        double distance;
        bool operator<(const N_D& truc) const{
            return this->distance<truc.distance;
        }

        bool operator>(const N_D& truc) const{
            return this->distance>truc.distance;
        }
        
    };

struct Coordonnees{
    int x, y;

};

struct Color{
    int r, g, b;

    Color(int _r, int _g, int _b): r(_r), g(_g), b(_b){}
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

    int getL() const;

    int getC() const;

    int altitude(int indice) const;

    int indice(unsigned int i, unsigned int j) const;

    int ligne(int indice) const;

    int colonne(int indice) const;

    int voisin(int indice, Direction dir) const;

    void afficher() const;


};


std::vector<std::vector<double>> dijkstra(Graphe g, std::vector<Coordonnees>departs);

void voronoi(Graphe g, std::vector<std::vector<double>>distances, std::vector<Color>c);

void voronoiLivraison(Graphe g, std::vector<std::vector<double>>distances, std::vector<Color>c);

void afficher_grille_res_txt(std::vector<int> res);

void sauver_fichier_img(const char* filename, Graphe g,std::vector<int>ind, std::vector<Color> c);

void sauver_fichier_txt(Graphe g, const char* filename, std::vector<int> res);

void recupere_coordonnees(const char* filename, std::vector<Coordonnees>&c);


#endif