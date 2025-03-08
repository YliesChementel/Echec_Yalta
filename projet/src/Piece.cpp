#include "Piece.h"
#include <iostream>

Piece::Piece(int camp) : camp(camp){
    camp;
}

void Piece::Deplacement() {

}

int Piece::GetCamp() {
    return camp;
}

void Piece::SetCamp(int camp) {
    this->camp=camp;
}
