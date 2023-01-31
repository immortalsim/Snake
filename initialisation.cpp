#include <iostream>
#include <ncurses.h>
#include "headerSnake.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <stdlib.h>

int row,col;
int pommex,pommey;
int score; 

void initEcran(){
    initscr(); //initialisation de l'écran 
    noecho(); //enlever les caractères parasites de l'écran 
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, row, col); //initialisation valeur de colonnes et lignes
    pommex = rand() % row; 
    pommey = rand() % col;
}

void calculMouv(pointSerpent* Noeud,char c){
    using namespace std::this_thread;
    using namespace std::chrono;
    int tempx1,tempx2,tempy1,tempy2;
    bool pomme = true;
    switch(c){
        case 'z':
            while(true){
                tempx1 = Noeud->x;
                tempy1 = Noeud->y;
                if(Noeud->x > 0){
                    Noeud->x--;
                }
                else{
                    gameOver(score);
                }
                
                if(Noeud->x == pommex && Noeud->y == pommey){
                    pomme = false;
                    reinitSerpent(Noeud);
                    score++;
                }
                else{
                    pomme = true;
                } 
                pointSerpent* temp = Noeud;
                while(temp->suivant != NULL){
                    temp = temp->suivant;
                    if(temp->x == Noeud->x && temp->y == Noeud->y){
                        gameOver(score);
                    }
                    tempx2 = temp->x;
                    tempy2 = temp->y; 
                    temp->x = tempx1; 
                    temp->y = tempy1;
                    tempx1 = tempx2;
                    tempy1 = tempy2;

                }
                majEcran(Noeud,pomme);
                sleep_for(150ms);
                if ((c = getch()) != ERR){
                    if(c == 'a'){
                        reinitSerpent(Noeud);
                    }
                    else{
                        calculMouv(Noeud,c); 
                    }
                }
                }
            break; 
        case 'q':
            while(true){
                tempx1 = Noeud->x;
                tempy1 = Noeud->y;
                if(Noeud->y > 0){    
                    Noeud->y--;
                }
                else{
                    gameOver(score);
                }
                if(Noeud->x == pommex && Noeud->y == pommey){
                    pomme = false;
                    reinitSerpent(Noeud);
                    score++;
                }
                else{
                    pomme = true; 
                }
                pointSerpent* temp = Noeud;
                while(temp->suivant != NULL){
                    temp = temp->suivant; 
                    if(temp->x == Noeud->x && temp->y == Noeud->y){
                        gameOver(score);
                    }
                    tempx2 = temp->x;
                    tempy2 = temp->y; 
                    temp->x = tempx1; 
                    temp->y = tempy1;
                    tempx1 = tempx2;
                    tempy1 = tempy2; 
                }
                majEcran(Noeud,pomme);
                sleep_for(150ms);
                if ((c = getch()) != ERR){
                    calculMouv(Noeud, c);
                }
            }
            break;
        case 's':
            while(true){
                tempx1 = Noeud->x; 
                tempy1 = Noeud->y;
                if(Noeud->x < row){
                    Noeud->x++; 
                }
                else{
                    gameOver(score);
                }
                if(Noeud->x == pommex && Noeud->y == pommey){
                    pomme = false;
                    reinitSerpent(Noeud);
                    score++;
                }
                else{
                    pomme = true; 
                }
                pointSerpent* temp = Noeud;
                while(temp->suivant != NULL){
                    temp = temp->suivant; 
                    if(Noeud->x == temp->x && Noeud->y == temp->y){
                        gameOver(score);
                    }
                    tempx2 = temp->x;
                    tempy2 = temp->y; 
                    temp->x = tempx1; 
                    temp->y = tempy1;
                    tempx1 = tempx2;
                    tempy1 = tempy2; 
                }
                majEcran(Noeud,pomme);
                sleep_for(150ms);
                if((c = getch()) != ERR){
                    calculMouv(Noeud,c);
                }
            }
            break;
        case 'd':
            while(true){ 
                tempx1 = Noeud->x; 
                tempy1 = Noeud->y; 
                if(Noeud->y < col){
                    Noeud->y++;
                }
                else{ 
                    gameOver(score);
                }
                if(Noeud->x == pommex && Noeud->y == pommey){
                    pomme = false;
                    reinitSerpent(Noeud);
                    score++;
                }
                else{
                    pomme = true; 
                }
                pointSerpent* temp = Noeud;
                while(temp->suivant != NULL){
                    temp = temp->suivant; 
                    if(temp->x == Noeud->x && temp->y == Noeud->y){
                        gameOver(score);
                    }
                    tempx2 = temp->x;
                    tempy2 = temp->y; 
                    temp->x = tempx1; 
                    temp->y = tempy1;
                    tempx1 = tempx2;
                    tempy1 = tempy2; 
                }
                majEcran(Noeud,pomme);
                sleep_for(150ms);
                if((c = getch()) != ERR){
                    calculMouv(Noeud,c);
                }
            }
            break;
        return;
    }
}

void reinitSerpent(pointSerpent* tete){
    //on alloue l'espace nécessaire au nouveau noeud 
    pointSerpent* nvNoeud = new pointSerpent(); 
    
    /*variables qui permettront d'initialiser la 
     * position du nouveau noeud*/
    int diffx = 0;
    int diffy = 0; 

    /* on donne les coordonnées
    nvNoeud->x = tete->x;
    nvNoeud->y = tete->y; */ 
    
    /*le pointeur vers le noeud suivant est nul
     * car celui qu'on définit est dernier*/ 
    nvNoeud->suivant = NULL;

    /*boucle permettant de traverser toute la chaine 
     *jusqu'au dernier noeud et de mettre à jour la 
     *variable dernier à chaque fois que le prochain noeud
     *n'est pas nul*/ 
    pointSerpent* temp = tete;
    while(temp->suivant != NULL){
        diffx = temp->x - temp->suivant->x;
        diffy = temp->y - temp->suivant->y;
        temp = temp->suivant;
    }

    /*on donne les coordonnées du nouveau noeud 
     * en fonction des coordonnées du dernier noeud */
    if(diffx == -1){
        nvNoeud->x=temp->x--;
        nvNoeud->y=temp->y;
    }
    else if(diffx == 1){
        nvNoeud->x=temp->x++;
        nvNoeud->y=temp->y;
    }
    else{ 
        if(diffy == -1){
            nvNoeud->x=temp->x;
            nvNoeud->y=temp->y--;
        }
        else if(diffy == 1){
            nvNoeud->x=temp->x;
            nvNoeud->y=temp->y++;
        }
        else{
            nvNoeud->x=temp->x++;
            nvNoeud->y=temp->y;
        }
    }

    /*rajouter un noeud en donnant à la variable
     *'suivant' du dernier noeud l'adresse du nouveau*/
    temp->suivant = nvNoeud; 

return;
}

void majEcran(pointSerpent* tete, bool pomme){
    wclear(stdscr);
    pointSerpent* temp = tete;
    mvprintw(temp->x, temp->y,"+");
    refresh();
    while(temp->suivant != NULL){
        temp = temp->suivant; 
        mvprintw(temp->x, temp->y,"+");
        refresh();
    }
    if(pomme){
        mvprintw(pommex,pommey,"O");
        refresh();
    }
    else{
        pommex = std::rand() % row; 
        pommey = std::rand() % col;
        mvprintw(pommex,pommey,"O");
        refresh();
    }
}
 
void gameOver(int score){

    endwin(); 
    std::cout << "bravo ! tu finis avec " << score << " points\n";
    exit(0);
}
