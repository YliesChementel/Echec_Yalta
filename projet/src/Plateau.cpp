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
            } else if (((i < 8 && i > 5 && j < 4) || (i < 8 && i > 5 && j > 7)) && index2 < 16) {
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



bool Plateau::DeplacerPiece(int xOrigine, int yOrigine, int xCoup, int yCoup) {
    if (matrice[xOrigine][yOrigine] == nullptr) { //verif si la pièce est présente
        std::cout << "Aucune pièce à cette position" << std::endl;
        return false;
    }

    if (xCoup < 0 || xCoup >= 12 || yCoup < 0 || yCoup >= 12) {//Bord du plateau
        std::cout << "Déplacement hors limites" << std::endl;
        return false;
    }

    if ((xCoup < 4 && yCoup > 7) || (xCoup >7 && yCoup < 4)) {// Case non existante du plateau yalta
        std::cout << "Déplacement hors limites" << std::endl;
        return false;
    }

    if((xCoup >3 && xCoup < 8) || (yCoup > 3 && yCoup < 8)){// Case non existante du plateau yalta (milieu)
        std::cout << "Déplacement hors limites" << std::endl;
        return false;
    }

    if (matrice[xCoup][yCoup] != nullptr) {
        std::cout << "Capture" << std::endl;
        // gérer la capture ici
    }

    matrice[xCoup][yCoup] = matrice[xOrigine][yOrigine];
    matrice[xOrigine][yOrigine] = nullptr;

    std::cout << "Pièce déplacée de (" << xOrigine << "," << yOrigine 
              << ") vers (" << xCoup << "," << yCoup << ")" << std::endl;
    
    return true;
}
