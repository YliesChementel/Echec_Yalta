#include "Piece.h"
#include <iostream>

Piece::Piece(int camp) : camp(camp){
    camp;
}

bool Piece::Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) {
    return true;
}

int Piece::GetCamp() {
    return camp;
}

void Piece::SetCamp(int camp) {
    this->camp=camp;
}