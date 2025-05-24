#include "include/Joueur.hpp"
#include <iostream>

Joueur::Joueur() : pieceList(nullptr) {}

Piece** Joueur::getListPiece(){
    return pieceList;
}

int Joueur::getSize(){
    return pieceListSize;
}

void Joueur::setSize(int pieceListSize){
    this->pieceListSize = pieceListSize;
}

void Joueur::setListPiece(Piece** liste) {
    if (pieceList != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete pieceList[i];
        }
        delete[] pieceList;
    }
    pieceList = liste;
}

void Joueur::removePiece(Piece* piece) {
    for (int i = 0; i < pieceListSize; ++i) {
        if (pieceList[i] == piece) {
            for (int j = i; j + 1 < pieceListSize; ++j) {
                pieceList[j] = pieceList[j + 1];
            }

            pieceList[pieceListSize - 1] = nullptr;
            --pieceListSize;
            break;
        }
    }
}


void Joueur::replacePiece(Piece* oldPiece,Piece* newPiece) {
    for (int i = 0; i < pieceListSize; ++i) {
        if (pieceList[i] == oldPiece) {
            pieceList[i] = newPiece;
            break;
        }
    }
}

Joueur::~Joueur() {
    if (pieceList != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete pieceList[i];
        }
        delete[] pieceList;
    }
}
