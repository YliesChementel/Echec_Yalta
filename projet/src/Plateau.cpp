#include "Plateau.h"
#include <iostream>
#include "Piece.h"

Plateau::Plateau(){
    
}

void Plateau::InitMatrice() {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            Piece piece = Piece(5);
            if(i<2 && j<8){
                piece.SetCamp(1);
            }
            else if((i<8 && i>5 && j<4) || ( i>3 && i<6 && j>7)){
                piece.SetCamp(2);
            }
            else if(i>9 && j>3){
                piece.SetCamp(3);
            }
            else if((i<4 && j>7) || (i>7 && j<4) || ((i>3 && i<8) && (j>3 && j<8)) ){
                piece.SetCamp(4);
            }
            matrice[i][j] = piece;
        }
    }
}

void Plateau::AffichageMatrice(){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            std::cout << matrice[i][j].GetCamp() << " ";
        }
        std::cout << std::endl;
    }
}
