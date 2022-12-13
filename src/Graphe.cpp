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

/**
 * @brief Fonction qui retourne un tableau (de tableau) resultat dans lequel il y a à chaque case pour tous les points de
 * départ la distance minimale entre un point de la grille et le départ selon l'algo de Djikstra 
 * 
 * @param g le graphe
 * @return std::vector<std::vector<double>> /tableau resultat
 */
std::vector<std::vector<double>> dijkstra(Graphe g, std::vector<Coordonnees>departs){

    std::vector<std::vector<double>> res;   //resultat
    std::vector<int>precedent(g.getLC());   //tableau des précédents de chaque points 
    std::vector<double>distance(g.getLC()); //tableau de distance de chaque points (par rapport à un point de départ)
    int n; // numero d'un point de la grille 
    int dv, dn, dnv;//les distance pour aller à v (voisin de n), à n et la distance de n à v 
    N_D v;// structure qui va rentrer dans la file un voisin de n 

    std::priority_queue<N_D>fp;// 

    for(int l = 0; l < (int)departs.size(); ++l) { // init du tableau de toutes les cases des précedents de chaque point 
        for(int i = 0; i < g.getLC(); ++i){        // et du tableau de distance pour y arriver init à -1 si on n'a pas encore sa distance pour y arriver
            precedent[i] = i;
            distance[i] = -1;
        }
        N_D indice_depart;// 
        indice_depart.noeud = g.indice(departs[l].x, departs[l].y);//convert en indice grace aux coordonnées pour retrouver les points (l => librairie)
        indice_depart.distance=0;

        std::vector<bool>visite(g.getLC(), false);
        
        distance[indice_depart.noeud] = 0;
        visite[indice_depart.noeud] = true;
        fp.push(indice_depart);

        while(!fp.empty()){
            n = fp.top().noeud;
            fp.pop();
            for(int i = 0; i < 4; ++i){
                v.noeud = g.voisin(n, (Direction)(i)); //on visite les 4 cotes
                if(v.noeud != -1 && visite[v.noeud] == false){ //si le voisin existe et que le noeud n est pas visite
                    visite[v.noeud] = true;
                    dv = distance[v.noeud];
                    dn = distance[n];
                    dnv = dn + sqrt(pow(g.altitude(n)-g.altitude(v.noeud), 2) + 1);
                    if(precedent[v.noeud] == v.noeud || dnv < dv){
                        precedent[v.noeud] = n;
                        distance[v.noeud] = dnv;
                        v.distance =dnv;
                        fp.push(v);
                    }
                }
            }
        }

        res.push_back(distance); //un push les distances de chaque librairies
    }
    return res;
    
}

/**
 * @brief reproduction du diagramme de voronoi en utilisant le tableau de distances
 * @brief obtenu apres avoir lance l'algorithme de dijkstra
 * 
 * 
 */
void voronoi(Graphe g, std::vector<std::vector<double>>distances, std::vector<Color>c){
    int taille_tab = (int)distances.size();
    assert(taille_tab < g.getLC());    
    std::vector<int>res(g.getLC(), 0);

    for(int i = 1; i < taille_tab; ++i){
        for(int j = 0; j < g.getLC(); ++j){
            res[j] = distances[i][j] < distances[res[j]][j] ? i : res[j];
            //on ecrit l'indice de la librairie la plus proche pour chaque case de la grille
        }
    }
    
    sauver_fichier_img("data/voronoi.ppm", g, res, c);

    sauver_fichier_txt(g, "data/voronoi.txt", res);


}


/**
 * @brief meme fonction que voronoi sauf qu'on multiplie un cout (fixe aleatoirement entre 6 et 12 et different pour chaque librairies)
 * @brief puis creation du diagramme
 * 
 */
void voronoiLivraison(Graphe g, std::vector<std::vector<double>>distances, std::vector<Color>c){
    int taille_tab = (int)distances.size();
    assert(taille_tab < g.getLC());    
    std::vector<int>res(g.getLC(), 0);

    float cout;

    for(int i = 0; i < taille_tab; ++i){
        cout = (rand()%(120-60+10)+60)/10.0;
        std::cout << "cout de la librairie " << i+1 << " : " << cout << std::endl;
        for(int j = 0; j < g.getLC(); ++j){
            distances[i][j]*=cout;
        }
    }

    for(int i = 1; i < taille_tab; ++i){
        for(int j = 0; j < g.getLC(); ++j){
            res[j] = distances[i][j] < distances[res[j]][j] ? i : res[j];
        }
    }

    
    sauver_fichier_img("data/voronoiLivraison.ppm", g, res, c);

    sauver_fichier_txt(g, "data/voronoiLivraison.txt", res);


}

void afficher_grille_res_txt(Graphe g, std::vector<int> res){
    for(int j = 0; j < g.C; ++j){
        for(int i = 0; i < g.L; ++i){
            std::cout << res[g.indice(i, j)] << "  ";
        }
        std::cout << std::endl;
    }
}


void sauver_fichier_txt(Graphe g, const char* filename, std::vector<int> res){
    std::ofstream fichier(filename);
    assert(fichier.is_open());
    fichier << g.L << " " << g.C << std::endl;

    for(int j = 0; j < g.C; ++j){
        for(int i = 0; i < g.L; ++i){
            fichier << res[g.indice(i, j)] << "  ";
        }
        fichier << std::endl;
    }

    std::cout << "Sauvegarde du fichier " << filename << " ... OK\n";
    fichier.close();
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