#include "Joueur.h"
#include <iostream>

Joueur::Joueur() : listePiece(nullptr) {}



void Joueur::JouerUnCoup(Piece* piece, int coup) {
    
}

Piece** Joueur::getListePiece(){
    return listePiece;
}

void Joueur::setListePiece(Piece** liste) {
    if (listePiece != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete listePiece[i];
        }
        delete[] listePiece;
    }
    listePiece = liste;
}


Joueur::~Joueur() {
    if (listePiece != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete listePiece[i];
        }
        delete[] listePiece;
    }
}
