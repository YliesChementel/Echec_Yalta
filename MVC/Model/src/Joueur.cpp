/**
 * @file Joueur.cpp
 * @brief Implémentation de la classe Joueur
 */

#include "include/Joueur.hpp"
#include <iostream>

/**
 * @brief Constructeur de la classe Joueur
 * 
 * Initialise un joueur vide avec sa liste de pièces à nullptr
 */
Joueur::Joueur() : pieceList(nullptr) {}

/**
 * @brief Accède à la liste des pièces du joueur
 * @return Pointeur vers le tableau des pièces
 */
Piece** Joueur::getListPiece(){
    return pieceList;
}

/**
 * @brief Obtient le nombre de pièces du joueur
 * @return Nombre de pièces
 */
int Joueur::getSize(){
    return pieceListSize;
}

/**
 * @brief Modifie le nombre de pièces du joueur
 * @param pieceListSize Nouveau nombre de pièces
 */
void Joueur::setSize(int pieceListSize){
    this->pieceListSize = pieceListSize;
}

/**
 * @brief Définit la liste des pièces du joueur
 * 
 * Libère d'abord la mémoire de l'ancienne liste si elle existe
 * avant d'assigner la nouvelle liste
 * 
 * @param liste Nouvelle liste de pièces
 */
void Joueur::setListPiece(Piece** liste) {
    if (pieceList != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete pieceList[i];
        }
        delete[] pieceList;
    }
    pieceList = liste;
}

/**
 * @brief Supprime une pièce de la liste
 * 
 * Déplace les pièces suivantes pour combler le trou
 * et décrémente le compteur de pièces
 * 
 * @param piece Pointeur vers la pièce à supprimer
 */
void Joueur::removePiece(Piece* piece) {
    for (int i = 0; i < pieceListSize; ++i) {
        if (pieceList[i] == piece) {
            // Déplace les pièces suivantes
            for (int j = i; j + 1 < pieceListSize; ++j) {
                pieceList[j] = pieceList[j + 1];
            }

            pieceList[pieceListSize - 1] = nullptr;
            --pieceListSize;
            break;
        }
    }
}

/**
 * @brief Remplace une pièce par une autre
 * 
 * Utilisé notamment pour la promotion des pions
 * 
 * @param oldPiece Pièce à remplacer
 * @param newPiece Nouvelle pièce
 */
void Joueur::replacePiece(Piece* oldPiece,Piece* newPiece) {
    for (int i = 0; i < pieceListSize; ++i) {
        if (pieceList[i] == oldPiece) {
            pieceList[i] = newPiece;
            break;
        }
    }
}

/**
 * @brief Destructeur de la classe Joueur
 * 
 * Libère la mémoire de toutes les pièces et de la liste
 */
Joueur::~Joueur() {
    if (pieceList != nullptr) {
        for (int i = 0; i < 16; ++i) {
            delete pieceList[i];
        }
        delete[] pieceList;
    }
}
