#include "Piece.h"
#include <iostream>
#include "Plateau.h"


std::vector<std::pair<int, int>> Piece::DeplacementCoup(int xOrigine, int yOrigine){}

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

    else if ((matriceOrigine == 6 && matriceDestination == 5) || (matriceOrigine == 5 && ydestination == 3)) { // Inversion horizontale de la matrice bas-milieu
        ydestination = 11 - ydestination;
        if ((xCoup == 0 || xCoup == 1 || xCoup == -1) && yCoup == -1) {// Pour toutes les directions où yCoup == -1, donc gauche, bas-gauche et haut-gauche
            yCoup = 1;
        }
    }
    else if ((matriceOrigine == 6 && matriceDestination == 4) || (matriceOrigine == 4 && xdestination == 3)) { // Inversion verticale de la matrice milieu-droite
        xdestination = 11 - xdestination;
        if (xCoup == -1 && (yCoup == 0 || yCoup == -1 || yCoup == 1)) { // Pour toutes les directions où xCoup == -1, donc haut, haut-gauche et haut-droite
            xCoup = 1;
        }
    }
}


void Piece::CoupRecursif(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles) {
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
        CoupRecursif(4,8, xCoup, yCoup, coupsPossibles);
        CoupRecursif(8,4, xCoup, yCoup, coupsPossibles);
    }
    else if((xOrigine==3 && yOrigine==4) && (xCoup==1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 8);
        CoupRecursif(8,8, 1, 1, coupsPossibles);
    }
    else if((xOrigine==4 && yOrigine==3) && (xCoup==-1 && yCoup==1)){
        coupsPossibles.emplace_back(8, 8);
        CoupRecursif(8,8, 1, 1, coupsPossibles);
    }
    else if((xOrigine==8 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(3, 4);
        coupsPossibles.emplace_back(4, 3);
        CoupRecursif(3,4, -1, 1, coupsPossibles);
        CoupRecursif(4,3, 1, -1, coupsPossibles);
    }
    else if((xOrigine==8 && yOrigine==4) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(4, 8);
        coupsPossibles.emplace_back(3, 3);
        CoupRecursif(4,8, 1, 1, coupsPossibles);
        CoupRecursif(3,3, -1, -1, coupsPossibles);
    }
    else if((xOrigine==4 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
        coupsPossibles.emplace_back(8, 4);
        coupsPossibles.emplace_back(3, 3);
        CoupRecursif(8,4, 1, 1, coupsPossibles);
        CoupRecursif(3,3, -1, -1, coupsPossibles);
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
            CoupRecursif(xdestination, ydestination, xCoup, yCoup, coupsPossibles);
        }
        else if(plateau.matrice[xdestination][ydestination] != nullptr && plateau.matrice[xdestination][ydestination]->GetCamp()!=this->GetCamp()){
            coupsPossibles.emplace_back(xdestination, ydestination);
        }
    }
}

void Piece::CoupCavalier(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles,int verification,bool methodeDeux) {
    int xdestination = xOrigine + xCoup;
    int ydestination = yOrigine + yCoup;
    if((yOrigine==7 && ydestination==8) && ((xCoup==0 && yCoup==1) || (xCoup==-1 && yCoup==1) || (xCoup==1 && yCoup==1))){
        std::cout << "Mur de la matrice 5" << std::endl;
    }
    else if((xOrigine==7 && xdestination==8) && ((xCoup==1 && yCoup==-1) || (xCoup==1 && yCoup==0) || (xCoup==1 && yCoup==1))){
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
        else if(verification==0){
            if(methodeDeux){
                CoupCavalier(xdestination,ydestination,xCoup,yCoup,coupsPossibles,1,true);
            }
            else{
                if(xCoup==0){
                    CoupCavalier(xdestination,ydestination,-1,0,coupsPossibles,1,false);
                    CoupCavalier(xdestination,ydestination,1,0,coupsPossibles,1,false);
                }
                else{
                    CoupCavalier(xdestination,ydestination,0,-1,coupsPossibles,1,false);
                    CoupCavalier(xdestination,ydestination,0,1,coupsPossibles,1,false);
                }
            }
            
        }
        else if(verification==1){
            if(methodeDeux){
                if(xCoup==0){
                    CoupCavalier(xdestination,ydestination,-1,0,coupsPossibles,2,true);
                    CoupCavalier(xdestination,ydestination,1,0,coupsPossibles,2,true);
                }
                else{
                    CoupCavalier(xdestination,ydestination,0,-1,coupsPossibles,2,true);
                    CoupCavalier(xdestination,ydestination,0,1,coupsPossibles,2,true);
                }
            }
            else{
                CoupCavalier(xdestination,ydestination,xCoup,yCoup,coupsPossibles,2,false);
            }
        }
        else if (plateau.matrice[xdestination][ydestination] == nullptr){
            coupsPossibles.emplace_back(xdestination, ydestination);
        }
        else if(plateau.matrice[xdestination][ydestination] != nullptr && plateau.matrice[xdestination][ydestination]->GetCamp()!=this->GetCamp()){
            coupsPossibles.emplace_back(xdestination, ydestination);
        }
    }
}

void Piece::CoupRoi(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles) {
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
        else if (plateau.matrice[xdestination][ydestination] == nullptr){
            coupsPossibles.emplace_back(xdestination, ydestination);
        }
        else if(plateau.matrice[xdestination][ydestination] != nullptr && plateau.matrice[xdestination][ydestination]->GetCamp()!=this->GetCamp()){
            coupsPossibles.emplace_back(xdestination, ydestination);
        }
    }
}

void Piece::CoupPion(int xOrigine, int yOrigine, std::vector<std::pair<int, int>>& coupsPossibles, int arret) {
    if(arret!=2){
        int xdestination;
        int ydestination;
        int xCoup;
        int yCoup = 0;

        int matriceOrigine = determineSousMatrice(xOrigine, yOrigine);

        if(this->camp==1){
            xCoup=1;
        }
        else if(this->camp==2){
            if(matriceOrigine==6 || matriceOrigine==5){ xCoup=1; }
            else{ xCoup=-1; }
        }
        else{
            if(matriceOrigine==4 || matriceOrigine==3){ xCoup=1; }
            else{ xCoup=-1; }
        }
        xdestination = xOrigine + xCoup;
        ydestination = yOrigine + yCoup;
        if((xOrigine==7 && xdestination==8) && (xCoup==1 && yCoup==0)){
            std::cout << "Mur de la matrice 4" << std::endl;
        }
        else{
            ajustementCoordonnees(xOrigine,yOrigine,xdestination,ydestination,xCoup,yCoup);
            if(arret==0){
                int xcapture = xOrigine + xCoup;
                int ycapture = yOrigine + 1;
                int yCoupTemp = 1;
                ajustementCoordonnees(xOrigine,yOrigine,xcapture,ycapture,xCoup,yCoupTemp);
                if(plateau.matrice[xcapture][ycapture] != nullptr && plateau.matrice[xcapture][ycapture]->GetCamp()!=this->GetCamp()){
                    coupsPossibles.emplace_back(xcapture, ycapture);
                }
                xcapture = xOrigine + xCoup;
                ycapture = yOrigine - 1;
                yCoupTemp = -1;
                ajustementCoordonnees(xOrigine,yOrigine,xcapture,ycapture,xCoup,yCoupTemp);
                if(plateau.matrice[xcapture][ycapture] != nullptr && plateau.matrice[xcapture][ycapture]->GetCamp()!=this->GetCamp()){
                    coupsPossibles.emplace_back(xcapture, ycapture);
                }

                if(xOrigine==3 && yOrigine==3){
                    if(plateau.matrice[4][8] != nullptr && plateau.matrice[4][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 8);
                    }
                    if(plateau.matrice[8][4] != nullptr && plateau.matrice[8][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 4);
                    }
                }
                else if(xOrigine==3 && yOrigine==4){
                    if(plateau.matrice[8][8] != nullptr && plateau.matrice[8][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 8);
                    }
                }
                else if(xOrigine==4 && yOrigine==3){
                    if(plateau.matrice[8][8] != nullptr && plateau.matrice[8][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 8);
                    }
                }
                else if(xOrigine==8 && yOrigine==8){
                    if(plateau.matrice[3][4] != nullptr && plateau.matrice[3][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3, 4);
                    }
                    if(plateau.matrice[4][3] != nullptr && plateau.matrice[4][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 3);
                    }
                }
                else if(xOrigine==8 && yOrigine==4){
                    if(plateau.matrice[4][8] != nullptr && plateau.matrice[4][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 8);
                    }
                    if(plateau.matrice[3][3] != nullptr && plateau.matrice[3][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3, 3);
                    }
                }
                else if(xOrigine==4 && yOrigine==8){
                    if(plateau.matrice[8][4] != nullptr && plateau.matrice[8][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 4);
                    }
                    if(plateau.matrice[3][3] != nullptr && plateau.matrice[3][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3, 3);
                    }
                }
            }

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