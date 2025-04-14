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
            for (int j = i; j < 15; ++j) {// Décale les éléments à gauche pour supprimer l'élément
                listePiece[j] = listePiece[j + 1];
            }
            listePiece[15] = nullptr; // Réduit la taille logique
            tailleListePiece--;
            break;
        }
    }
    listePieceRetirer[16-tailleListePiece]==piece;
}

Joueur::~Joueur() {
    if (listePiece != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete listePiece[i];
        }
        delete[] listePiece;
    }
}
