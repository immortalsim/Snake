#include <iostream>


//structure d'un point du corps du serpent 
struct pointSerpent{
    int x, y; //coordonnées
    pointSerpent* suivant; //pointeur vers le prochain pointSerpent
}; 

// typedef struct pointSerpent pointSerpent; 

/* fonction globale permettant d'initializer 
 * et de mettre à jour l'écran en récuperant 
 * les touches du clavier */
void bougerSerpent();

/*fonction globale permettanat de mettre à jour le corps
 * du serpent */ 
void majSerpent(pointSerpent tete);

/* fonction permettant d'afficher un point en fonction 
 * de son type à savoir pomme, serpent ou vide et de
 * ses coordonnées x et y*/ 
// void affichagePoint(char typePoint, int x, int y);

//Initialise l'écran ncurses
void initEcran();
    
//(ré-)Initialise la liste chainée du Serpent avec un élément en plus
void reinitSerpent(pointSerpent* prNoeud);

//Calculateur de mouvement du serpent
void calculMouv(pointSerpent* Noeud,char c);

//Fonction de mise à jour de l'écran 
void majEcran(pointSerpent* tete);

//Fonction de mise à jour des coordonnées des points du Serpent
void calculxy(pointSerpent* Noeud);
