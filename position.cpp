#include "headerSnake.h"
#include <ncurses.h>
#include <chrono>
#include <iostream>
#include <thread>

extern int row,col;

void bougerSerpent(){
    curs_set(0); //rendre le curseur invisible
    initEcran();
    noecho(); //on affiche pas la touche récupérée sur le clavier 
    pointSerpent* tete = new pointSerpent(); //initialisation position tete Serpent
    tete->x = row/2;
    tete->y = col/2;
    majSerpent(*tete);
    }

void majSerpent(pointSerpent tete){
    using namespace std::this_thread; //module de pause du programme
    using namespace std::chrono; //module d'unités de temps
    char c = 'z';
    while(true){
    c = wgetch(stdscr);
    
    calculMouv(&tete,c); 
    /* mvprintw(tete.x-1,tete.y, "col = %d", col); */

    //initialisation d'une adresse temporaire qui pointe vers la tete du serpent 
    pointSerpent* temp = &tete;
    while(temp->suivant !=NULL){
        temp->suivant->x = temp->x; // les coordonnées de chaque point sont
        temp->suivant->y = temp->y; // transmises au prochain dans la liste
        temp = temp->suivant;
    }

    /*switch(c){
        case'z':  
            affichagePoint('S',tete.x,tete.y);
            break; 
        case'q':
            affichagePoint('S',tete.x,tete.y); 
            break;
        case's':
            affichagePoint('S',tete.x,tete.y);
            break;
        case'd':
            affichagePoint('S',tete.x,tete.y);
            break;
            // if pour la pomme
    }
    */
}
}
/*
void affichagePoint(char typePoint, int x, int y){
    //on détermine d'abord le type de point à imprimer
    switch(typePoint){ 
        //arobase pour la pomme,
        case 'P':
            mvaddch(x,y,'@');
        //caractère noir pour le serpent, 
        case 'S':
            mvaddch(x,y,'*');
        //et vide pour le vide 
        case ' ':
            mvaddch(x,y,' ');
    }
}
*/
