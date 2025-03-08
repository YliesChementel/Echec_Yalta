#include "Plateau.h"
#include <iostream>
#include "Piece.h"

Plateau::Plateau(){
    InitMatrice();
}

void Plateau::InitMatrice(){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            matrice[i][j] = nullptr;
        }
    }
}

void Plateau::PlacerPiece(Piece* ListePiece1, Piece* ListePiece2, Piece* ListePiece3) {
    int index1 = 0, index2 = 0, index3 = 0;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (i < 2 && j < 8 && index1 < 16) {
                matrice[i][j] = &ListePiece1[index1++];
            } else if (((i < 8 && i > 5 && j < 4) || (i > 3 && i < 6 && j > 7)) && index2 < 16) {
                matrice[i][j] = &ListePiece2[index2++];
            } else if (i > 9 && j > 3 && index3 < 16) {
                matrice[i][j] = &ListePiece3[index3++];
            } else {
                matrice[i][j] = nullptr;
            }
        }
    }
}


void Plateau::AffichageMatrice() {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (matrice[i][j] != nullptr) {
                std::cout << matrice[i][j]->GetCamp() << " ";
            } else {
                std::cout << "X ";
            }
        }
        std::cout << std::endl;
    }
}



void Plateau::UpdateMatrice(Piece* piece, int coupX, int coupY){
    matrice[coupX][coupY]=piece;
}