# LIFAPC TP n°9 : Graphes et algorithme de Dijkstra

## FERHAOUI Yanisse 11909519 - CHOGLI Sofiane 12005328

### Que contient cette archive?

- Un dossier "src" contenant tous les fichier source (.cpp, .h)
- un dossier "data" ou sont stockés les fichiers .txt que nous utiliserons pour initialiser nos variables, ainsi que les fichiers .txt et images .ppm de sortie après le lancement du programme.
- un dossier "obj" et "bin" où seront stockés les fichiers .o et l'éxécutable une fois que l'on aura tout compilé
- un Makefile qui nous servira à tout compiler


### Comment lancer le programme?

Il faut tout d'abord lancer la commande 
```
make
 ```

et tous les fichiers objets ainsi que l'éxécutable seront créé.

Ensuite on lance le programme avec

```$
 bin/main [LIEN_VERS_FICHIER1] [LIEN_VERS_FICHIER2]
```

avec comme FICHIER1 le fichier .txt de la carte qui contient longueur, hauteur de la grille puis toutes ses altitudes (exemple: data/carte.txt et data/test.txt) et FICHIER2 correspond au fichier .txt où sont stockés le nombre de coordonnées ainsi que les coordonnées x1,y1 ... xn,yn (exemple: data/coordtest.txt).