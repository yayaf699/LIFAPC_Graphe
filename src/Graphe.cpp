#include "Graphe.h"
#include <cassert>
#include <exception>
#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

Graphe::Graphe(unsigned int _L, unsigned int _C){

    L = _L;
    C = _C;
    for(int i = 0; i < L*C ; ++i){
        Terrain.push_back(0);
    }
}

Graphe::Graphe(const char* file){
    std::ifstream fichier(file); 
    fichier >> L >> C;
    for(int i = 0; i < L*C; ++i) Terrain.push_back(0);
    int val;
    for(int j = 0; j < C; ++j){
        for(int i = 0; i < L; ++i){
            fichier >> Terrain[indice(i, j)];
        }
    }
}

void recupere_coordonnees(const char* filename, std::vector<Coordonnees>&c){
    std::ifstream fichier(filename);
    assert(fichier.is_open());
    int nb, x, y;

    fichier >> nb;
    for(int i = 0; i < nb; ++i){
        fichier >> x >> y;
        c.push_back({x, y});
    }


}

Graphe::~Graphe(){
    
}

int Graphe::getLC() const { return L*C; }

int Graphe::getL() const{ return L; }
int Graphe::getC() const{ return C; }

int Graphe::altitude( int indice) const{ return indice == -1 ? -1 : Terrain[indice]; }

int Graphe::indice(unsigned int i, unsigned int j) const{ return i*C+j; }

int Graphe::ligne(int indice) const{ return indice/C; }

int Graphe::colonne(int indice) const { return indice%C; }

int Graphe::voisin(int indice, Direction dir) const{

    switch (dir)
    {
    case 0: //Est
        return (indice+1)%C != 0 ? indice + 1 : -1;
        break;
    case 1: //Nord
        return indice >= C ? indice - C : -1;
        break;
    
    case 2: // Ouest
        return (indice+1)%C != 1 ? indice - 1 : -1;
        break;
    
    case 3: // Sud
        return indice <= L*(C - 1) ? indice + C : -1;
        break;
    
    default:
        throw std::invalid_argument("dir doit etre plus petit que 4");
    }
}


void Graphe::afficher() const{
    for(int j = 0; j < C; ++j){
        for(int i = 0; i < L; ++i){
            std::cout << altitude(indice(i, j)) << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<double>> dijkstra(Graphe g, std::vector<Coordonnees>departs){

    std::vector<std::vector<double>> res;
    std::vector<int>precedent(g.getLC());
    std::vector<double>distance(g.getLC());
    int n;
    int v, dv, dn, dnv;

    
    for(int l = 0; l < departs.size(); ++l) {
        for(int i = 0; i < g.getLC(); ++i){
            precedent[i] = i;
            distance[i] = -1;
        }
        int indice_depart = g.indice(departs[l].x, departs[l].y);

        std::vector<bool>visite(g.getLC(), false);

        std::cout << indice_depart << ": pt de depart" << std::endl;
        
        std::priority_queue<int, std::vector<int>, std::less<int>>fp;
        distance[indice_depart] = INFINITY;
        visite[indice_depart] = true;
        fp.push(indice_depart);

        while(!fp.empty()){
            n = fp.top();
            fp.pop();
            for(int i = 0; i < 4; ++i){
                v = g.voisin(n, (Direction)(i));
                if(v != -1 && visite[v] == false){
                    visite[v] = true;
                    dv = distance[v];
                    dn = distance[n];
                    dnv = dn + sqrt(pow(g.altitude(n)-g.altitude(v), 2) + 1);
                    if(precedent[v] == v || dnv < dv){
                        //std::cout << n << " " << v << " " << dn << " " << dv << " " << dnv << std::endl;
                        precedent[v] = n;
                        distance[v] = dnv;
                        fp.push(v);
                    }
                }
            }
        }
        res.push_back(distance);
    }
    return res;
    
}


void voronoi(Graphe g, std::vector<std::vector<double>>distances, std::vector<Color>c){
    int taille_tab = (int)distances.size();
    assert(taille_tab < g.getLC());    
    std::vector<int>res(g.getLC(), 0);

    for(int i = 1; i < taille_tab; ++i){
        for(int j = 0; j < g.getLC(); ++j){
            res[j] = distances[i][j] < distances[res[j]][j] ? i : res[j];
        }
    }

    for(int j = 0; j < g.C; ++j){
        for(int i = 0; i < g.L; ++i){
            std::cout << res[g.indice(i, j)] << "  ";
        }
        std::cout << std::endl;
    }
    
    sauver_fichier_img("data/voronoi.ppm", g, res, c);

    //sauver_fichier_txt(g, "data/voronoi.txt", res);


}

void afficher_grille_res_txt(Graphe g, std::vector<int> res){
    for(int j = 0; j < g.C; ++j){
        for(int i = 0; i < g.L; ++i){
            std::cout << res[g.indice(i, j)] << "  ";
        }
        std::cout << std::endl;
    }
}

void afficher_grille_res_clr(Graphe g, std::vector<int> res, std::vector<Color>){

}

void sauver_fichier_txt(Graphe g, const char* filename, std::vector<int> res){
    std::ofstream fichier(filename);
    assert(fichier.is_open());
    fichier << g.L << " " << g.C << std::endl;

    for(int j = 0; j < g.C; ++j){
        for(int i = 0; i < g.L; ++i){
            std::cout << res[g.indice(i, j)] << "  ";
        }
        std::cout << std::endl;
    }
}

void sauver_fichier_img(const char* filename, Graphe g,std::vector<int>ind, std::vector<Color> c)  {
    std::ofstream fichier (filename);
    assert(fichier.is_open());
    fichier << "P3" << std::endl;
    fichier << g.L << " " << g.C << std::endl;
    fichier << "255" << std::endl;
    for(int j = 0; j < g.C; ++j){
        for(int i = 0; i < g.L; ++i){
        fichier << +c[ind[g.indice(i, j)]].r << " " << +c[ind[g.indice(i, j)]].g << " " << +c[ind[g.indice(i, j)]].b << " ";
        }
        fichier << std::endl;
    }
    std::cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}