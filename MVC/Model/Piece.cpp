#include "Piece.h"
#include <iostream>
#include <algorithm>
#include "Plateau.h"


std::vector<std::pair<int, int>> Piece::DeplacementCoup(int xOrigine, int yOrigine, Piece* matrice[12][12]){
    return std::vector<std::pair<int, int>>{std::make_pair(-1, -1)};
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

    else if ((matriceOrigine == 6 && matriceDestination == 5) || (matriceOrigine == 5 && ydestination == 3)) { // Inversion horizontale de la matrice bas-milieu + (cas particulier 7-3)
        ydestination = 11 - ydestination;
        if ((xCoup == 0 || xCoup == 1 || xCoup == -1) && yCoup == -1) {// Pour toutes les directions où yCoup == -1, donc gauche, bas-gauche et haut-gauche
            yCoup = 1;
        }
    }
    else if ((matriceOrigine == 6 && matriceDestination == 4) || (matriceOrigine == 4 && xdestination == 3 )) { // Inversion verticale de la matrice milieu-droite
        xdestination = 11 - xdestination;
        if (xCoup == -1 && (yCoup == 0 || yCoup == -1 || yCoup == 1)) { // Pour toutes les directions où xCoup == -1, donc haut, haut-gauche et haut-droite
            xCoup = 1;
        }
    }
}

// Vérifie si les coordonnées sont en dehors du plateau
bool estHorsPlateau(int x, int y) {
    return x < 0 || x >= 12 || y < 0 || y >= 12;
}

// Vérifie si la case ciblée n'existe pas
bool caseNonExistante(int x, int y) {
    return (x < 4 && y > 7) || (x > 7 && y < 4);
}

// Vérifie si le déplacement rencontre le mur de la matrice 5
bool estMurMatrice5(int xOrigine, int yOrigine, int xCoup, int yCoup) {
    return (yOrigine == 7 && (yOrigine + yCoup == 8)) && ((xCoup == 0 && yCoup == 1) || (xCoup == -1 && yCoup == 1) || (xCoup == 1 && yCoup == 1));
}

// Vérifie si le déplacement rencontre le mur de la matrice 4
bool estMurMatrice4(int xOrigine, int yOrigine, int xCoup, int yCoup) {
    return (xOrigine == 7 && (xOrigine + xCoup == 8)) && ((xCoup == 1 && yCoup == -1) || (xCoup == 1 && yCoup == 0) || (xCoup == 1 && yCoup == 1));
}


void Piece::CoupRecursif(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles,Piece* matrice[12][12]) {
    int xdestination = xOrigine + xCoup;
    int ydestination = yOrigine + yCoup;
    if (!estMurMatrice5(xOrigine, yOrigine, xCoup, yCoup)) {
        if (!estMurMatrice4(xOrigine, yOrigine, xCoup, yCoup)) {

            if((xOrigine==3 && yOrigine==3) && (xCoup==1 && yCoup==1)){
                if(matrice[4][8] != nullptr){
                    if(matrice[4][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 8);
                    CoupRecursif(4,8, xCoup, yCoup, coupsPossibles,matrice);
                }
                if(matrice[8][4] != nullptr){
                    if(matrice[8][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 4);
                    CoupRecursif(8,4, xCoup, yCoup, coupsPossibles,matrice);
                }
            }

            else if((xOrigine==3 && yOrigine==4) && (xCoup==1 && yCoup==-1)){
                if(matrice[8][8] != nullptr){
                    if(matrice[8][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 8);
                    CoupRecursif(8,8, 1, 1, coupsPossibles,matrice);
                }
                if(matrice[4][3] != nullptr){
                    if(matrice[4][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4,3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 3);
                    CoupRecursif(4,3, 1, -1, coupsPossibles,matrice);
                }
            }

            else if((xOrigine==4 && yOrigine==3) && (xCoup==-1 && yCoup==1)){
                if(matrice[8][8] != nullptr){
                    if(matrice[8][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 8);
                    CoupRecursif(8,8, 1, 1, coupsPossibles,matrice);
                }
                if(matrice[3][4] != nullptr){
                    if(matrice[3][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3,4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 4);
                    CoupRecursif(3,4, -1, 1, coupsPossibles,matrice);
                }
            }

            else if((xOrigine==8 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
                if(matrice[3][4] != nullptr){
                    if(matrice[3][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3,4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 4);
                    CoupRecursif(3,4, -1, 1, coupsPossibles,matrice);
                }

                if(matrice[4][3] != nullptr){
                    if(matrice[4][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4,3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 3);
                    CoupRecursif(4,3, 1, -1, coupsPossibles,matrice);
                }
            }

            else if((xOrigine==8 && yOrigine==4) && (xCoup==-1 && yCoup==-1)){
                if(matrice[4][8] != nullptr){
                    if(matrice[4][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4,8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 8);
                    CoupRecursif(4,8, 1, 1, coupsPossibles,matrice);
                }

                if(matrice[3][3] != nullptr){
                    if(matrice[3][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3,3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 3);
                    CoupRecursif(3,3, -1, -1, coupsPossibles,matrice);
                }

            }

            else if((xOrigine==4 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
                if(matrice[8][4] != nullptr){
                    if(matrice[8][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8,4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 4);
                    CoupRecursif(8,4, 1, 1, coupsPossibles,matrice);
                }
                if(matrice[3][3] != nullptr){
                    if(matrice[3][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3,3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 3);
                    CoupRecursif(3,3, -1, -1, coupsPossibles,matrice);
                }
                
            }
            
            else{
                ajustementCoordonnees(xOrigine,yOrigine,xdestination,ydestination,xCoup,yCoup);
                if (!estHorsPlateau(xdestination, ydestination)) {
                    if (!caseNonExistante(xdestination, ydestination)) {
                        if (matrice[xdestination][ydestination] == nullptr){
                            coupsPossibles.emplace_back(xdestination, ydestination);
                            CoupRecursif(xdestination, ydestination, xCoup, yCoup, coupsPossibles,matrice);
                        }
                        else if(matrice[xdestination][ydestination] != nullptr && matrice[xdestination][ydestination]->GetCamp()!=this->GetCamp()){
                            coupsPossibles.emplace_back(xdestination, ydestination);
                        }
                    }
                }
            }
        }
    }
}

void Piece::CoupCavalier(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles,int verification,bool methodeDeux, Piece* matrice[12][12]) {
    int xdestination = xOrigine + xCoup;
    int ydestination = yOrigine + yCoup;
    if (!estMurMatrice5(xOrigine, yOrigine, xCoup, yCoup)) {
        if (!estMurMatrice4(xOrigine, yOrigine, xCoup, yCoup)) {
            ajustementCoordonnees(xOrigine,yOrigine,xdestination,ydestination,xCoup,yCoup);
            if (!estHorsPlateau(xdestination, ydestination)) {
                if (!caseNonExistante(xdestination, ydestination)) {
                    if(verification==0){
                        if(methodeDeux){
                            CoupCavalier(xdestination,ydestination,xCoup,yCoup,coupsPossibles,1,true,matrice);
                        }
                        else{
                            if(xCoup==0){
                                CoupCavalier(xdestination,ydestination,-1,0,coupsPossibles,1,false,matrice);
                                CoupCavalier(xdestination,ydestination,1,0,coupsPossibles,1,false,matrice);
                            }
                            else{
                                CoupCavalier(xdestination,ydestination,0,-1,coupsPossibles,1,false,matrice);
                                CoupCavalier(xdestination,ydestination,0,1,coupsPossibles,1,false,matrice);
                            }
                        }
                        
                    }
                    else if(verification==1){
                        if(methodeDeux){
                            if(xCoup==0){
                                CoupCavalier(xdestination,ydestination,-1,0,coupsPossibles,2,true,matrice);
                                CoupCavalier(xdestination,ydestination,1,0,coupsPossibles,2,true,matrice);
                            }
                            else{
                                CoupCavalier(xdestination,ydestination,0,-1,coupsPossibles,2,true,matrice);
                                CoupCavalier(xdestination,ydestination,0,1,coupsPossibles,2,true,matrice);
                            }
                        }
                        else{
                            CoupCavalier(xdestination,ydestination,xCoup,yCoup,coupsPossibles,2,false,matrice);
                        }
                    }
                    else if (matrice[xdestination][ydestination] == nullptr){
                        coupsPossibles.emplace_back(xdestination, ydestination);
                    }
                    else if(matrice[xdestination][ydestination] != nullptr && matrice[xdestination][ydestination]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(xdestination, ydestination);
                    }
                }
            }
        }
    }
}

void Piece::CoupRoi(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles, Piece* matrice[12][12]) {
    int xdestination = xOrigine + xCoup;
    int ydestination = yOrigine + yCoup;
    if (!estMurMatrice5(xOrigine, yOrigine, xCoup, yCoup)) {
        if (!estMurMatrice4(xOrigine, yOrigine, xCoup, yCoup)) {
            if((xOrigine==3 && yOrigine==3) && (xCoup==1 && yCoup==1)){
                if(matrice[4][8] != nullptr){
                    if(matrice[4][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 8);
                }

                if(matrice[8][4] != nullptr){
                    if(matrice[8][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 4);
                }
                
                
            }
            else if((xOrigine==3 && yOrigine==4) && (xCoup==1 && yCoup==-1)){
                if(matrice[8][8] != nullptr){
                    if(matrice[8][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 8);
                }
                if(matrice[4][3] != nullptr){
                    if(matrice[4][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 3);
                }
            }
            else if((xOrigine==4 && yOrigine==3) && (xCoup==-1 && yCoup==1)){
                if(matrice[8][8] != nullptr){
                    if(matrice[8][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 8);
                }
                if(matrice[3][4] != nullptr){
                    if(matrice[3][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3, 4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 4);
                }
            }
            else if((xOrigine==8 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
                if(matrice[3][4] != nullptr){
                    if(matrice[3][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3, 4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 4);
                }
                if(matrice[4][3] != nullptr){
                    if(matrice[4][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 3);
                }
            }
            else if((xOrigine==8 && yOrigine==4) && (xCoup==-1 && yCoup==-1)){
                if(matrice[4][8] != nullptr){
                    if(matrice[4][8]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(4, 8);
                    }
                }
                else{
                    coupsPossibles.emplace_back(4, 8);
                }
                if(matrice[3][3] != nullptr){
                    if(matrice[3][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3, 3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 3);
                }
            }
            else if((xOrigine==4 && yOrigine==8) && (xCoup==-1 && yCoup==-1)){
                if(matrice[8][4] != nullptr){
                    if(matrice[8][4]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(8, 4);
                    }
                }
                else{
                    coupsPossibles.emplace_back(8, 4);
                }

                if(matrice[3][3] != nullptr){
                    if(matrice[3][3]->GetCamp()!=this->GetCamp()){
                        coupsPossibles.emplace_back(3, 3);
                    }
                }
                else{
                    coupsPossibles.emplace_back(3, 3);
                }
            }
            else{
                ajustementCoordonnees(xOrigine,yOrigine,xdestination,ydestination,xCoup,yCoup);
                if (!estHorsPlateau(xdestination, ydestination)) {
                    if (!caseNonExistante(xdestination, ydestination)) {
                        if (matrice[xdestination][ydestination] == nullptr){
                            coupsPossibles.emplace_back(xdestination, ydestination);
                        }
                        else if(matrice[xdestination][ydestination] != nullptr && matrice[xdestination][ydestination]->GetCamp()!=this->GetCamp()){
                            coupsPossibles.emplace_back(xdestination, ydestination);
                        }
                    }
                }
            }
        }
    }
}

void Piece::CoupPion(int xOrigine, int yOrigine, std::vector<std::pair<int, int>>& coupsPossibles, int arret, Piece* matrice[12][12]) {
    if (arret == 2) return;

    int xCoup;
    int matriceOrigine = determineSousMatrice(xOrigine, yOrigine);

    if (camp == 1 || (camp == 2 && (matriceOrigine == 5 || matriceOrigine == 6)) || (camp == 3 && (matriceOrigine == 3 || matriceOrigine == 4))) {
        xCoup = 1;
    } else {
        xCoup = -1;
    }

    int yCoup = 0;
    int xdestination = xOrigine + xCoup;
    int ydestination = yOrigine + yCoup;

    if (estMurMatrice4(xOrigine, yOrigine, xCoup, yCoup)) return;

    if (arret == 0) {
        // Capture diagonale à droite
        capturePion(xOrigine, yOrigine, xCoup, 1, coupsPossibles, matrice);

        // Capture diagonale à gauche
        capturePion(xOrigine, yOrigine, xCoup, -1, coupsPossibles, matrice);

        // Gérer les cas particuliers de captures de la rosaces
        CapturesRosaces(xOrigine, yOrigine, coupsPossibles, matrice);
    }

    // Coup en avant
    ajustementCoordonnees(xOrigine, yOrigine, xdestination, ydestination, xCoup, yCoup);
    if (!estHorsPlateau(xdestination, ydestination) && !caseNonExistante(xdestination, ydestination)) {
        if (matrice[xdestination][ydestination] == nullptr) {
            coupsPossibles.emplace_back(xdestination, ydestination);
            CoupPion(xdestination, ydestination, coupsPossibles, arret + 1, matrice);
        }
    }
}

void Piece::capturePion(int x, int y, int xCoup, int yCoup, std::vector<std::pair<int, int>>& coups, Piece* matrice[12][12]) {
    int xCapture = x + xCoup;
    int yCapture = y + yCoup;
    ajustementCoordonnees(x, y, xCapture, yCapture, xCoup, yCoup);
    if (estMurMatrice5(x, y, xCoup, yCoup)) return;
    if (!estHorsPlateau(xCapture, yCapture)) {
        Piece* piece = matrice[xCapture][yCapture];
        if (piece != nullptr && piece->GetCamp() != this->GetCamp()) {
            coups.emplace_back(xCapture, yCapture);
        }
    }
}

void Piece::CapturesRosaces(int x, int y, std::vector<std::pair<int, int>>& coups, Piece* matrice[12][12]) {
    std::vector<std::pair<int, int>> coupsRosaces;

    if (x == 3 && y == 3) {
        coupsRosaces = {{4, 8}, {8, 4}};
    } else if ((x == 3 && y == 4) || (x == 4 && y == 3)) {
        coupsRosaces = {{8, 8}};
    } else if (x == 8 && y == 8) {
        coupsRosaces = {{3, 4}, {4, 3}};
    } else if (x == 8 && y == 4) {
        coupsRosaces = {{4, 8}, {3, 3}};
        coups.erase(std::find(coups.begin(), coups.end(), std::make_pair(7,3))); // cas de bug particulier pour le pion 
    } else if (x == 4 && y == 8) {
        coupsRosaces = {{8, 4}, {3, 3}};
        coups.erase(std::find(coups.begin(), coups.end(), std::make_pair(8,7))); // cas de bug particulier pour le pion 
    }

    for (const auto& coup : coupsRosaces) {
        Piece* piece = matrice[coup.first][coup.second];
        if (piece != nullptr && piece->GetCamp() != this->GetCamp()) {
            coups.emplace_back(coup);
        }
    }
}
