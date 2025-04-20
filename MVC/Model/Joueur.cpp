#include "Joueur.h"
#include <iostream>

Joueur::Joueur() : listePiece(nullptr) {}



void Joueur::JouerUnCoup(Piece* piece, int coup) {
    
}

Piece** Joueur::getListePiece(){
    return listePiece;
}

int Joueur::getTaille(){
    return tailleListePiece;
}

void Joueur::setTaille(int tailleListePiece){
    this->tailleListePiece = tailleListePiece;
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

void Joueur::retirerPiece(Piece* piece) {
    for (int i = 0; i < tailleListePiece; ++i) {
        if (listePiece[i] == piece) {
            for (int j = i; j + 1 < tailleListePiece; ++j) {
                listePiece[j] = listePiece[j + 1];
            }

            listePiece[tailleListePiece - 1] = nullptr;
            --tailleListePiece;
            break;
        }
    }
}


void Joueur::remplacerPiece(Piece* anciennePiece,Piece* nouvellePiece) {
    for (int i = 0; i < tailleListePiece; ++i) {
        if (listePiece[i] == anciennePiece) {
            listePiece[i] = nouvellePiece;
            break;
        }
    }
}

Joueur::~Joueur() {
    if (listePiece != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete listePiece[i];
        }
        delete[] listePiece;
    }
}
