#include "Joueur.h"
#include <iostream>

Joueur::Joueur() : listePiece(nullptr) {}



void Joueur::JouerUnCoup(Piece piece, int coup) {
    
}

Piece* Joueur::getListePiece(){
    return listePiece;
}

void Joueur::setListePiece(Piece* liste) {
    if (listePiece != nullptr) {
        delete[] listePiece;
    }
    listePiece = liste;
}


Joueur::~Joueur() {
    delete[] listePiece;
}
