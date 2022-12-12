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
    int val;
    for(int i = 0; i < L*C ; i++) {
        fichier >> val;
        Terrain.push_back(+val);
        }
}

Graphe::~Graphe(){
    
}

int Graphe::getLC() const { return L*C; }

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

bool Graphe::voisin_existe(int indice, Direction dir) const{
    switch(dir){

        case 0: //Est
            return indice%C < C - 1;

        case 1: //Nord
            return indice >= C;

        case 2: //Ouest
            return (indice-1)%C > 0 && (indice-1)%C < indice%C;

        case 3: //Sud
            return indice + C <= L*C - 1;

        default:
            return false;
    }
}

void Graphe::afficher() const{
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; ++j){
            std::cout << altitude(indice(i, j)) << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int>dijkstra(Graphe g, int departs){

    std::vector<int>tabDeparts;
    tabDeparts.push_back(rand()%g.getLC());
    std::vector<int>precedent(g.getLC());
    std::vector<double>distance(g.getLC());
    std::vector<bool>visite(g.getLC(), false);
    int n;
    int v, dv, dn, dnv;

    for(int i = 0; i < g.getLC(); ++i){
        precedent[i] = i;
        distance[i] = -1;
    }
    std::priority_queue<int>fp;
    
    for(auto i: tabDeparts){
    distance[i] = 0;
    fp.push(i);
    }

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
                    std::cout << n << "  " << v << "  " << dn << " " << dv << " " << dnv << std::endl;
                    precedent[v] = n;
                    distance[v] = dnv;
                    fp.push(v);
                }
            }
        }
    }

    
}