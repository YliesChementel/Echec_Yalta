#include "Piece.h"
#include <iostream>
#include <algorithm>
#include "Plateau.h"


std::vector<std::pair<int, int>> Piece::possibleMove(int xStart, int yStart, Piece* matrix[12][12]){
    return std::vector<std::pair<int, int>>{std::make_pair(-1, -1)};
}

int Piece::getSide() {
    return side;
}

void Piece::setSide(int side) {
    this->side=side;
}

int Piece::determineSubMatrix(int x, int y) const {
    if (x < 4 && y < 4) return 1; // haut gauche
    if (x < 4 && y >= 4 && y < 8) return 2; // haut milieu
    if (y < 4 && x >= 4 && x < 8) return 3; // milieu gauche
    if (y >= 7 && x >= 4 && x < 8) return 4; // milieu droite
    if (x >= 7 && y >= 4 && y < 8) return 5; // bas milieu
    if (x >= 7 && y >= 7) return 6; // bas droite
    return 0;
}

void Piece::adjustCoordinates(int& xStart, int& yStart, int& xDestination, int& yDestination,int& xMove, int& yMove) const {
    int matrixStart = determineSubMatrix(xStart, yStart);
    int matrixDestination = determineSubMatrix(xDestination, yDestination);

    if((xDestination > 3 && xDestination < 8) && (yDestination > 3 && yDestination < 8)){

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Lignes

        if(xMove==-1 && yMove==0){//va en haut
            xDestination-=4;
        }
        else if(xMove==0 && yMove==1){//va à droite
            yDestination+=4;
        }
        else if(xMove==1 && yMove==0){// va en bas
            xDestination+=4;
        }
        else if(xMove==0 && yMove==-1){//va à gauche
            yDestination-=4;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Diagonales

        else if(xMove==-1 && yMove==-1){// va haut-gauche
            if(matrixStart==4){
                yDestination-=4;
            }
            else if(matrixStart==5){
                xDestination-=4;
            }
        }
        else if(xMove==-1 && yMove==1){// va haut-droite
            if(matrixStart==3){
                yDestination+=4;
            }
            else if(matrixStart==5){
                xDestination-=4;
            }
        }
        else if(xMove==1 && yMove==1){// va bas-droite
            if(matrixStart==2){
                xDestination+=4;
            }
            else if(matrixStart==3){
                yDestination+=4;
            }
        }
        else if(xMove==1 && yMove==-1){// va bas-gauche
            if(matrixStart==2){
                xDestination+=4;
            }
            else if(matrixStart==4){
                yDestination-=4;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Intéractions des matrices 4, 5 et 6 qui sont inversées

    else if ((matrixStart == 6 && matrixDestination == 5) || (matrixStart == 5 && yDestination == 3)) { // Inversion horizontale de la matrix bas-milieu + (cas particulier 7-3)
        yDestination = 11 - yDestination;
        if ((xMove == 0 || xMove == 1 || xMove == -1) && yMove == -1) {// Pour toutes les directions où yMove == -1, donc gauche, bas-gauche et haut-gauche
            yMove = 1;
        }
    }
    else if ((matrixStart == 6 && matrixDestination == 4) || (matrixStart == 4 && xDestination == 3 )) { // Inversion verticale de la matrix milieu-droite
        xDestination = 11 - xDestination;
        if (xMove == -1 && (yMove == 0 || yMove == -1 || yMove == 1)) { // Pour toutes les directions où xMove == -1, donc haut, haut-gauche et haut-droite
            xMove = 1;
        }
    }
}

// Vérifie si les coordonnées sont en dehors du plateau
bool isOutOfBoard(int x, int y) {
    return x < 0 || x >= 12 || y < 0 || y >= 12;
}

// Vérifie si la case ciblée n'existe pas
bool isSquareExist(int x, int y) {
    return (x < 4 && y > 7) || (x > 7 && y < 4);
}

// Vérifie si le déplacement rencontre le mur de la matrix 5
bool isWallInMatrix5(int xStart, int yStart, int xMove, int yMove) {
    return (yStart == 7 && (yStart + yMove == 8)) && ((xMove == 0 && yMove == 1) || (xMove == -1 && yMove == 1) || (xMove == 1 && yMove == 1));
}

// Vérifie si le déplacement rencontre le mur de la matrix 4
bool isWallInMatrix4(int xStart, int yStart, int xMove, int yMove) {
    return (xStart == 7 && (xStart + xMove == 8)) && ((xMove == 1 && yMove == -1) || (xMove == 1 && yMove == 0) || (xMove == 1 && yMove == 1));
}


void Piece::recursiveMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves,Piece* matrix[12][12]) {
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;
    if (!isWallInMatrix5(xStart, yStart, xMove, yMove)) {
        if (!isWallInMatrix4(xStart, yStart, xMove, yMove)) {

            if((xStart==3 && yStart==3) && (xMove==1 && yMove==1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                    recursiveMove(4,8, xMove, yMove, possibleMoves,matrix);
                }
                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                    recursiveMove(8,4, xMove, yMove, possibleMoves,matrix);
                }
            }

            else if((xStart==3 && yStart==4) && (xMove==1 && yMove==-1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                    recursiveMove(8,8, 1, 1, possibleMoves,matrix);
                }
                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                    recursiveMove(4,3, 1, -1, possibleMoves,matrix);
                }
            }

            else if((xStart==4 && yStart==3) && (xMove==-1 && yMove==1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                    recursiveMove(8,8, 1, 1, possibleMoves,matrix);
                }
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                    recursiveMove(3,4, -1, 1, possibleMoves,matrix);
                }
            }

            else if((xStart==8 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                    recursiveMove(3,4, -1, 1, possibleMoves,matrix);
                }

                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                    recursiveMove(4,3, 1, -1, possibleMoves,matrix);
                }
            }

            else if((xStart==8 && yStart==4) && (xMove==-1 && yMove==-1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4,8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                    recursiveMove(4,8, 1, 1, possibleMoves,matrix);
                }

                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                    recursiveMove(3,3, -1, -1, possibleMoves,matrix);
                }

            }

            else if((xStart==4 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8,4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                    recursiveMove(8,4, 1, 1, possibleMoves,matrix);
                }
                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                    recursiveMove(3,3, -1, -1, possibleMoves,matrix);
                }
                
            }
            
            else{
                adjustCoordinates(xStart,yStart,xDestination,yDestination,xMove,yMove);
                if (!isOutOfBoard(xDestination, yDestination)) {
                    if (!isSquareExist(xDestination, yDestination)) {
                        if (matrix[xDestination][yDestination] == nullptr){
                            possibleMoves.emplace_back(xDestination, yDestination);
                            recursiveMove(xDestination, yDestination, xMove, yMove, possibleMoves,matrix);
                        }
                        else if(matrix[xDestination][yDestination] != nullptr && matrix[xDestination][yDestination]->getSide()!=this->getSide()){
                            possibleMoves.emplace_back(xDestination, yDestination);
                        }
                    }
                }
            }
        }
    }
}

void Piece::knightMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves,int verification,bool methodTwo, Piece* matrix[12][12]) {
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;
    if (!isWallInMatrix5(xStart, yStart, xMove, yMove)) {
        if (!isWallInMatrix4(xStart, yStart, xMove, yMove)) {
            adjustCoordinates(xStart,yStart,xDestination,yDestination,xMove,yMove);
            if (!isOutOfBoard(xDestination, yDestination)) {
                if (!isSquareExist(xDestination, yDestination)) {
                    if(verification==0){
                        if(methodTwo){
                            knightMove(xDestination,yDestination,xMove,yMove,possibleMoves,1,true,matrix);
                        }
                        else{
                            if(xMove==0){
                                knightMove(xDestination,yDestination,-1,0,possibleMoves,1,false,matrix);
                                knightMove(xDestination,yDestination,1,0,possibleMoves,1,false,matrix);
                            }
                            else{
                                knightMove(xDestination,yDestination,0,-1,possibleMoves,1,false,matrix);
                                knightMove(xDestination,yDestination,0,1,possibleMoves,1,false,matrix);
                            }
                        }
                        
                    }
                    else if(verification==1){
                        if(methodTwo){
                            if(xMove==0){
                                knightMove(xDestination,yDestination,-1,0,possibleMoves,2,true,matrix);
                                knightMove(xDestination,yDestination,1,0,possibleMoves,2,true,matrix);
                            }
                            else{
                                knightMove(xDestination,yDestination,0,-1,possibleMoves,2,true,matrix);
                                knightMove(xDestination,yDestination,0,1,possibleMoves,2,true,matrix);
                            }
                        }
                        else{
                            knightMove(xDestination,yDestination,xMove,yMove,possibleMoves,2,false,matrix);
                        }
                    }
                    else if (matrix[xDestination][yDestination] == nullptr){
                        possibleMoves.emplace_back(xDestination, yDestination);
                    }
                    else if(matrix[xDestination][yDestination] != nullptr && matrix[xDestination][yDestination]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(xDestination, yDestination);
                    }
                }
            }
        }
    }
}

void Piece::kingMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]) {
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;
    if (!isWallInMatrix5(xStart, yStart, xMove, yMove)) {
        if (!isWallInMatrix4(xStart, yStart, xMove, yMove)) {
            if((xStart==3 && yStart==3) && (xMove==1 && yMove==1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                }

                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                }
                
                
            }
            else if((xStart==3 && yStart==4) && (xMove==1 && yMove==-1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                }
                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                }
            }
            else if((xStart==4 && yStart==3) && (xMove==-1 && yMove==1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                }
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                }
            }
            else if((xStart==8 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                }
                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                }
            }
            else if((xStart==8 && yStart==4) && (xMove==-1 && yMove==-1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                }
                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                }
            }
            else if((xStart==4 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                }

                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                }
            }
            else{
                adjustCoordinates(xStart,yStart,xDestination,yDestination,xMove,yMove);
                if (!isOutOfBoard(xDestination, yDestination)) {
                    if (!isSquareExist(xDestination, yDestination)) {
                        if (matrix[xDestination][yDestination] == nullptr){
                            possibleMoves.emplace_back(xDestination, yDestination);
                        }
                        else if(matrix[xDestination][yDestination] != nullptr && matrix[xDestination][yDestination]->getSide()!=this->getSide()){
                            possibleMoves.emplace_back(xDestination, yDestination);
                        }
                    }
                }
            }
        }
    }
}

void Piece::castling(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]){
    Piece* piece = matrix[xStart][yStart];
    if(piece->side==1){
        if(matrix[0][0]!=nullptr && !matrix[0][0]->getHasAlreadyMoved()){
            if(matrix[0][1]==nullptr && matrix[0][2]==nullptr && matrix[0][3]==nullptr){
                possibleMoves.emplace_back(0, 2);
            }
        }
        if(matrix[0][7]!=nullptr && !matrix[0][7]->getHasAlreadyMoved()){
            if(matrix[0][5]==nullptr && matrix[0][6]==nullptr){
                possibleMoves.emplace_back(0, 6);
            }
        }
    }
    else if(piece->side==2){
        if(matrix[7][0]!=nullptr && !matrix[7][0]->getHasAlreadyMoved()){
            if(matrix[7][1]==nullptr && matrix[7][2]==nullptr){
                possibleMoves.emplace_back(7, 1);
            }
        }
        if(matrix[7][11]!=nullptr && !matrix[7][11]->getHasAlreadyMoved()){
            if(matrix[7][8]==nullptr && matrix[7][9]==nullptr && matrix[7][10]==nullptr){
                possibleMoves.emplace_back(7, 9);
            }
        }
    }
    else{
        if(matrix[11][11]!=nullptr && !matrix[11][11]->getHasAlreadyMoved()){
            if(matrix[11][10]==nullptr && matrix[11][9]==nullptr){
                possibleMoves.emplace_back(11, 10);
            }
        }
        if(matrix[11][7]!=nullptr && !matrix[11][7]->getHasAlreadyMoved()){
            if(matrix[11][6]==nullptr && matrix[11][5]==nullptr && matrix[11][4]==nullptr){
                possibleMoves.emplace_back(11, 5);
            }
        }
    }
}

void Piece::pawnMove(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, int stop, Piece* matrix[12][12]) {
    if (stop == 2) return;

    int xMove;
    int matrixStart = determineSubMatrix(xStart, yStart);

    if (side == 1 || (side == 2 && (matrixStart == 5 || matrixStart == 6)) || (side == 3 && (matrixStart == 3 || matrixStart == 4))) {
        xMove = 1;
    } else {
        xMove = -1;
    }

    int yMove = 0;
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;

    if (isWallInMatrix4(xStart, yStart, xMove, yMove)) return;

    if (stop == 0) {
        // Capture diagonale à droite
        captureByPawn(xStart, yStart, xMove, 1, possibleMoves, matrix);

        // Capture diagonale à gauche
        captureByPawn(xStart, yStart, xMove, -1, possibleMoves, matrix);

        // Gérer les cas particuliers de captures de la rosaces
        captureOnBoardCenter(xStart, yStart, possibleMoves, matrix);
    }

    // Coup en avant
    adjustCoordinates(xStart, yStart, xDestination, yDestination, xMove, yMove);
    if (!isOutOfBoard(xDestination, yDestination) && !isSquareExist(xDestination, yDestination)) {
        if (matrix[xDestination][yDestination] == nullptr) {
            possibleMoves.emplace_back(xDestination, yDestination);
            pawnMove(xDestination, yDestination, possibleMoves, stop + 1, matrix);
        }
    }
}

void Piece::pawnMove2(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]) {
    int xMove;
    int matrixStart = determineSubMatrix(xStart, yStart);

    if (side == 1 || (side == 2 && (matrixStart == 5 || matrixStart == 6)) || (side == 3 && (matrixStart == 3 || matrixStart == 4))) {
        xMove = 1;
    } else {
        xMove = -1;
    }

    int yMove = 0;
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;

    if (isWallInMatrix4(xStart, yStart, xMove, yMove)) return;

    // Capture diagonale à droite
    captureByPawn(xStart, yStart, xMove, 1, possibleMoves, matrix);

    // Capture diagonale à gauche
    captureByPawn(xStart, yStart, xMove, -1, possibleMoves, matrix);

    // Gérer les cas particuliers de captures de la rosaces
    captureOnBoardCenter(xStart, yStart, possibleMoves, matrix);

    // Coup en avant
    adjustCoordinates(xStart, yStart, xDestination, yDestination, xMove, yMove);
    if (!isOutOfBoard(xDestination, yDestination) && !isSquareExist(xDestination, yDestination)) {
        if (matrix[xDestination][yDestination] == nullptr) {
            possibleMoves.emplace_back(xDestination, yDestination);
        }
    }
}


void Piece::captureByPawn(int x, int y, int xMove, int yMove, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]) {
    int xCapture = x + xMove;
    int yCapture = y + yMove;
    adjustCoordinates(x, y, xCapture, yCapture, xMove, yMove);
    if (isWallInMatrix5(x, y, xMove, yMove)) return;
    if (!isOutOfBoard(xCapture, yCapture)) {
        Piece* piece = matrix[xCapture][yCapture];
        if (piece != nullptr && piece->getSide() != this->getSide()) {
            moves.emplace_back(xCapture, yCapture);
        }
    }
}

void Piece::captureOnBoardCenter(int x, int y, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]) {
    std::vector<std::pair<int, int>> centerMoves;

    if (x == 3 && y == 3) {
        centerMoves = {{4, 8}, {8, 4}};
    } else if ((x == 3 && y == 4) || (x == 4 && y == 3)) {
        centerMoves = {{8, 8}};
    } else if (x == 8 && y == 8) {
        centerMoves = {{3, 4}, {4, 3}};
    } else if (x == 8 && y == 4) {
        centerMoves = {{4, 8}, {3, 3}};
        auto it = std::find(moves.begin(), moves.end(), std::make_pair(7, 8));// cas de bug particulier pour le pion 
        if (it != moves.end()) {
            moves.erase(it);
        } 
    } else if (x == 4 && y == 8) {
        centerMoves = {{8, 4}, {3, 3}};
        auto it = std::find(moves.begin(), moves.end(), std::make_pair(8, 7));// cas de bug particulier pour le pion 
        if (it != moves.end()) {
            moves.erase(it);
        } 
    }

    for (const auto& move : centerMoves) {
        Piece* piece = matrix[move.first][move.second];
        if (piece != nullptr && piece->getSide() != this->getSide()) {
            moves.emplace_back(move);
        }
    }
}
