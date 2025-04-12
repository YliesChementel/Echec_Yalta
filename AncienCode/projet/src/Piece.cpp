#include "Piece.h"
#include <iostream>
#include "Plateau.h"  // Needed for full definition of Plateau

bool Piece::Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) {
    return true;
}

int Piece::GetCamp() {
    return camp;
}

void Piece::SetCamp(int camp) {
    this->camp=camp;
}

int Piece::determineSousMatrice(int x, int y) const {
    if (x < 4 && y < 4) return 1; // haut gauche
    if (x < 4 && y >= 4 && y < 8) return 2; // haut milieu
    if (y < 4 && x >= 4 && x < 8) return 3; // milieu gauche
    if (y >= 7 && x >= 4 && x < 8) return 4; // milieu droite
    if (x >= 7 && y >= 4 && y < 8) return 5; // bas milieu
    if (x >= 7 && y >= 7) return 6; // bas droite
    return 0;
}

void Piece::ajustementCoordonnees(int& xOrigine, int& yOrigine, int& xdestination, int& ydestination,int& xCoup, int& yCoup) const {
    int matriceOrigine = determineSousMatrice(xOrigine, yOrigine);
    int matriceDestination = determineSousMatrice(xdestination, ydestination);

    if((xdestination > 3 && xdestination < 8) && (ydestination > 3 && ydestination < 8)){
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Lignes
        if(xCoup==-1 && yCoup==0){//va en haut
            xdestination-=4;
        }
        else if(xCoup==0 && yCoup==1){//va à droite
            ydestination+=4;
        }
        else if(xCoup==1 && yCoup==0){// va en bas
            xdestination+=4;
        }
        else if(xCoup==0 && yCoup==-1){//va à gauche
            ydestination-=4;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Diagonales
        else if(xCoup==-1 && yCoup==-1){// va haut-gauche
            if(matriceOrigine==4){
                ydestination-=4;
            }
            else if(matriceOrigine==5){
                xdestination-=4;
            }
        }
        else if(xCoup==-1 && yCoup==1){// va haut-droite
            if(matriceOrigine==3){
                ydestination+=4;
            }
            else if(matriceOrigine==5){
                xdestination-=4;
            }
        }
        else if(xCoup==1 && yCoup==1){// va bas-droite
            if(matriceOrigine==2){
                xdestination+=4;
            }
            else if(matriceOrigine==3){
                ydestination+=4;
            }
        }
        else if(xCoup==1 && yCoup==-1){// va bas-gauche
            if(matriceOrigine==2){
                xdestination+=4;
            }
            else if(matriceOrigine==4){
                ydestination-=4;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Intéractions des matrices 4, 5 et 6 qui sont inversées
    else if (matriceOrigine == 6 && matriceDestination == 5) { // matrice bas-milieu inversé horizontalement
        ydestination = 11 - ydestination;
        if(xCoup==0 && yCoup==-1){//va à gauche
            yCoup = 1;
        }
        else if(xCoup==1 && yCoup==-1){// va bas-gauche
            yCoup = 1;
        }
        else if(xCoup==-1 && yCoup==-1){// va haut-gauche
            yCoup = 1;
        }
    }
    else if (matriceOrigine == 5 && ydestination==3) { // matrice bas-milieu inversé horizontalement
        ydestination = 11 - ydestination;
        if(xCoup==0 && yCoup==-1){//va à gauche
            yCoup = 1;
        }
        else if(xCoup==1 && yCoup==-1){// va bas-gauche
            yCoup = 1;
        }
        else if(xCoup==-1 && yCoup==-1){// va haut-gauche
            yCoup = 1;
        }
    }

    else if (matriceOrigine == 6 && matriceDestination == 4) { // matrice milieu-droite inversé verticalement
        xdestination = 11 - xdestination;
        if(xCoup==-1 && yCoup==0){//va en haut
            xCoup = 1;
        }
        else if(xCoup==-1 && yCoup==-1){// va haut-gauche
            xCoup = 1;
        }
        else if(xCoup==-1 && yCoup==1){// va haut-droite
            xCoup = 1;
        }
    } 
    else if (matriceOrigine == 4 && xdestination==3) { // matrice milieu-droite inversé verticalement
        xdestination = 11 - xdestination;
        if(xCoup==-1 && yCoup==0){//va en haut
            xCoup = 1;
        }
        else if(xCoup==-1 && yCoup==-1){// va haut-gauche
            xCoup = 1;
        }
        else if(xCoup==-1 && yCoup==1){// va haut-droite
            xCoup = 1;
        }
    } 
}



void Piece::recursive(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles) {
    int xdestination = xOrigine + xCoup;
    int ydestination = yOrigine + yCoup;
    if((yOrigine==7 && ydestination==8) && ((xCoup==0 && yCoup==1) || (xCoup==-1 && yCoup==1) || (xCoup==1 && yCoup==1))){
        std::cout << "Mur de la matrice 5" << std::endl;
    }
    else if((xOrigine==7 && xdestination==8) && ((xCoup==1 && yCoup==-1) || (xCoup==1 && yCoup==0) || (xCoup==1 && yCoup==1))){
        std::cout << "Mur de la matrice 4" << std::endl;
    }
    else if((xOrigine==3 && yOrigine==3) && (xCoup==1 && yCoup==1)){
        coupsPossibles.emplace_back(4, 8);
        coupsPossibles.emplace_back(8, 4);
        recursive(4,8, xCoup, yCoup, coupsPossibles);
        recursive(8,4, xCoup, yCoup, coupsPossibles);
    }
    else if((xOrigine==3 && yOrigine==4) && (xCoup==1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 8);
        recursive(8,8, 1, 1, coupsPossibles);
    }
    else if((xOrigine==4 && yOrigine==3) && (xCoup==-1 && yCoup==1)){
        coupsPossibles.emplace_back(8, 8);
        recursive(8,8, 1, 1, coupsPossibles);
    }
    else if((xOrigine==8 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(3, 4);
        coupsPossibles.emplace_back(4, 3);
        recursive(3,4, -1, 1, coupsPossibles);
        recursive(4,3, 1, -1, coupsPossibles);
    }
    else if((xOrigine==8 && yOrigine==4) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(4, 8);
        coupsPossibles.emplace_back(3, 3);
        recursive(4,8, 1, 1, coupsPossibles);
        recursive(3,3, -1, -1, coupsPossibles);
    }
    else if((xOrigine==4 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 4);
        coupsPossibles.emplace_back(3, 3);
        recursive(8,4, 1, 1, coupsPossibles);
        recursive(3,3, -1, -1, coupsPossibles);
    }
    else{
        ajustementCoordonnees(xOrigine,yOrigine,xdestination,ydestination,xCoup,yCoup);
        if (xdestination < 0 || xdestination >= 12 || ydestination < 0 || ydestination >= 12) {//Bord du plateau
            std::cout << "Déplacement hors du plateau" << std::endl;
        }
        else if((xdestination < 4 && ydestination > 7) || (xdestination > 7 && ydestination < 4)) {// Case non existante du plateau yalta
            std::cout << "Case non existante" << std::endl;
        }
        else if((yOrigine==7 && ydestination==8) && (xCoup==0 && yCoup==1)){
            std::cout << "Mur de la matrice 5" << std::endl;
        }
        else if (plateau.matrice[xdestination][ydestination] == nullptr){
            coupsPossibles.emplace_back(xdestination, ydestination);
            recursive(xdestination, ydestination, xCoup, yCoup, coupsPossibles);
        }
    }
}

std::vector<std::pair<int, int>> Piece::DeplacementCoup(int xOrigine, int yOrigine){
    std::vector<std::pair<int, int>> coupsPossibles;
    recursive(xOrigine,yOrigine,directions[5].first,directions[5].second, coupsPossibles);
    return coupsPossibles;
}


void Piece::Coup(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles) {
    int xdestination = xOrigine + xCoup;
    int ydestination = yOrigine + yCoup;
    if((yOrigine==7 && ydestination==8) && ((xCoup==0 && yCoup==1) || (xCoup==-1 && yCoup==1) || (xCoup==1 && yCoup==1))){
        std::cout << "Mur de la matrice 5" << std::endl;
    }
    else if((xOrigine==7 && xdestination==8) && ((xCoup==1 && yCoup==-1) || (xCoup==1 && yCoup==0) || (xCoup==1 && yCoup==1))){
        std::cout << "Mur de la matrice 4" << std::endl;
    }
    else if((xOrigine==3 && yOrigine==3) && (xCoup==1 && yCoup==1)){
        coupsPossibles.emplace_back(4, 8);
        coupsPossibles.emplace_back(8, 4);
    }
    else if((xOrigine==3 && yOrigine==4) && (xCoup==1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 8);
    }
    else if((xOrigine==4 && yOrigine==3) && (xCoup==-1 && yCoup==1)){
        coupsPossibles.emplace_back(8, 8);
    }
    else if((xOrigine==8 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(3, 4);
        coupsPossibles.emplace_back(4, 3);
    }
    else if((xOrigine==8 && yOrigine==4) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(4, 8);
        coupsPossibles.emplace_back(3, 3);
    }
    else if((xOrigine==4 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 4);
        coupsPossibles.emplace_back(3, 3);
    }
    else{
        ajustementCoordonnees(xOrigine,yOrigine,xdestination,ydestination,xCoup,yCoup);
        if (xdestination < 0 || xdestination >= 12 || ydestination < 0 || ydestination >= 12) {//Bord du plateau
            std::cout << "Déplacement hors du plateau" << std::endl;
        }
        else if((xdestination < 4 && ydestination > 7) || (xdestination > 7 && ydestination < 4)) {// Case non existante du plateau yalta
            std::cout << "Case non existante" << std::endl;
        }
        else if((yOrigine==7 && ydestination==8) && (xCoup==0 && yCoup==1)){
            std::cout << "Mur de la matrice 5" << std::endl;
        }
        else if (plateau.matrice[xdestination][ydestination] == nullptr){
            coupsPossibles.emplace_back(xdestination, ydestination);
        }
    }
}

void Piece::CoupPion(int xOrigine, int yOrigine, std::vector<std::pair<int, int>>& coupsPossibles, int arret) {
    std::cout << "arret " << arret << std::endl;
    if(arret!=2){
        int xdestination;
        int ydestination;
        int xCoup;
        int yCoup;

        int matriceOrigine = determineSousMatrice(xOrigine, yOrigine);

        if(this->camp==1){
            xCoup=1;
            yCoup=0;
        }
        else if(this->camp==2){
            if(matriceOrigine==6 || matriceOrigine==5){
                xCoup=1;
                yCoup=0;
            }
            else{
                xCoup=-1;
                yCoup=0;
            }
        }
        else{
            if(matriceOrigine==4 || matriceOrigine==3){
                xCoup=1;
                yCoup=0;
            }else{
                xCoup=-1;
                yCoup=0;
            }
            
        }
        xdestination = xOrigine + xCoup;
        ydestination = yOrigine + yCoup;
        if((xOrigine==7 && xdestination==8) && (xCoup==1 && yCoup==0)){
            std::cout << "Mur de la matrice 4" << std::endl;
        }
        else{
            ajustementCoordonnees(xOrigine,yOrigine,xdestination,ydestination,xCoup,yCoup);
            if (xdestination < 0 || xdestination >= 12 || ydestination < 0 || ydestination >= 12) {//Bord du plateau
                std::cout << "Déplacement hors du plateau" << std::endl;
            }
            else if((xdestination < 4 && ydestination > 7) || (xdestination > 7 && ydestination < 4)) {// Case non existante du plateau yalta
                std::cout << "Case non existante" << std::endl;
            }
            else if (plateau.matrice[xdestination][ydestination] == nullptr){
                coupsPossibles.emplace_back(xdestination, ydestination);
                CoupPion(xdestination,ydestination,coupsPossibles,arret+=1);
            }
        }
    }
}

/*
void Piece::ajustementRosasse(int xOrigine, int yOrigine, int xCoup, int yCoup, std::vector<std::pair<int, int>>& coupsPossibles){
    if((xOrigine==3 && yOrigine==3) && (xCoup==1 && yCoup==1)){
        coupsPossibles.emplace_back(4, 8);
        coupsPossibles.emplace_back(8, 4);
        recursive(4,8, xCoup, yCoup, coupsPossibles);
        recursive(8,4, xCoup, yCoup, coupsPossibles);
    }
    else if((xOrigine==3 && yOrigine==4) && (xCoup==1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 8);
        recursive(8,8, 1, 1, coupsPossibles);
    }
    else if((xOrigine==4 && yOrigine==3) && (xCoup==-1 && yCoup==1)){
        coupsPossibles.emplace_back(8, 8);
        recursive(8,8, 1, 1, coupsPossibles);
    }
    else if((xOrigine==8 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(3, 4);
        coupsPossibles.emplace_back(4, 3);
        recursive(3,4, -1, 1, coupsPossibles);
        recursive(4,3, 1, -1, coupsPossibles);
    }
    else if((xOrigine==8 && yOrigine==4) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(4, 8);
        coupsPossibles.emplace_back(3, 3);
        recursive(4,8, 1, 1, coupsPossibles);
        recursive(3,3, -1, -1, coupsPossibles);
    }
    else if((xOrigine==4 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 4);
        coupsPossibles.emplace_back(3, 3);
        recursive(8,4, 1, 1, coupsPossibles);
        recursive(3,3, -1, -1, coupsPossibles);
    }
}
*/