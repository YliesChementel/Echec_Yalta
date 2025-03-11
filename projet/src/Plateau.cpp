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
void Plateau::PlacerPiece(Piece** ListePiece1, Piece** ListePiece2, Piece** ListePiece3) {
    int index1 = 0, index2 = 0, index3 = 0;

    // Placer les pièces du joueur 1
    for (int j = 0; j < 8; ++j) {
        matrice[1][j] = ListePiece1[index1++];
    }
    for (int j = 0; j < 8; ++j) {
        matrice[0][j] = ListePiece1[index1++];
    }

    // Placer les pièces du joueur 2
    for (int j = 0; j < 4; ++j) {
        matrice[7][j] = ListePiece2[index2++];
    }
    for (int j = 8; j < 12; ++j) {
        matrice[7][j] = ListePiece2[index2++];
    }
    for (int j = 0; j < 4; ++j) {
        matrice[6][j] = ListePiece2[index2++];
    }
    for (int j = 8; j < 12; ++j) {
        matrice[6][j] = ListePiece2[index2++];
    }

    // Placer les pièces du joueur 3
    for (int j = 4; j < 12; ++j) {
        matrice[10][j] = ListePiece3[index3++];
    }
    for (int j = 4; j < 12; ++j) {
        matrice[11][j] = ListePiece3[index3++];
    }

    // Mettre les cases restantes vides 
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (matrice[i][j] == nullptr) {
                matrice[i][j] = nullptr;
            }
        }
    }
}





void Plateau::AffichageMatrice() {
    std::cout << "   ";
    for (int j = 0; j < 12; ++j) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 12; ++i) {
        if(i<10){
            std::cout << i << "  ";
        }else{
            std::cout << i << " ";
        }
        
        for (int j = 0; j < 12; ++j) {
            if (matrice[i][j] != nullptr) {
                std::cout << matrice[i][j]->GetType() << " ";
            } else {
                if ((i < 4 && j > 7) || (i >7 && j < 4)) {// Case non existante du plateau yalta
                    std::cout << "  ";
                }
                else if((i >3 && i < 8) && (j > 3 && j < 8)){// Case non existante du plateau yalta (milieu)
                    std::cout << "  ";
                }
                else{
                    std::cout << "X ";
                }
                
            }
        }
        std::cout << std::endl;
    }
}



bool Plateau::DeplacerPiece(int tourJoueur,int xOrigine, int yOrigine, int xCoup, int yCoup) {
    Piece* piece = matrice[xOrigine][yOrigine];
    if(piece->GetCamp() != tourJoueur){
        std::cout << "Ce n'est pas votre pièce" << std::endl;
        return false;
    };
    std::cout << "Type de pièce déplacée : " << piece->GetType() << std::endl;
    if (piece == nullptr || !piece->Deplacement(xOrigine, yOrigine, xCoup, yCoup)) {
        std::cout << "Déplacement invalide" << std::endl;
        return false;
    }
    

    if (matrice[xOrigine][yOrigine] == nullptr) { //verif si la pièce est présente
        std::cout << "Aucune pièce à cette position" << std::endl;
        return false;
    }

    if (xCoup < 0 || xCoup >= 12 || yCoup < 0 || yCoup >= 12) {//Bord du plateau
        std::cout << "Déplacement hors du plateau" << std::endl;
        return false;
    }

    if ((xCoup < 4 && yCoup > 7) || (xCoup >7 && yCoup < 4)) {// Case non existante du plateau yalta
        std::cout << "Case non existante" << std::endl;
        return false;
    }

    if((xCoup >3 && xCoup < 8) && (yCoup > 3 && yCoup < 8)){// Case non existante du plateau yalta (milieu)
        std::cout << "Case non existante du plateau yalta (milieu)" << std::endl;
        return false;
    }

    if (matrice[xCoup][yCoup] != nullptr) {
        if(matrice[xCoup][yCoup]->GetCamp() == tourJoueur){
            std::cout << "Vous essayez de capturer votre propre pièce" << std::endl;
            return false;
        }
        else{
            std::cout << "Capture" << std::endl;
        }
    }

    matrice[xCoup][yCoup] = matrice[xOrigine][yOrigine];
    matrice[xOrigine][yOrigine] = nullptr;

    std::cout << "Pièce déplacée de (" << xOrigine << "," << yOrigine 
              << ") vers (" << xCoup << "," << yCoup << ")" << std::endl;
    
    return true;
}
