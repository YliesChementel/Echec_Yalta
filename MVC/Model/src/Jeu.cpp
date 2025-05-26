/**
 * @file Jeu.cpp
 * @brief Implémentation de la classe Jeu
 */

#include "include/Jeu.hpp"
#include "include/Piece.hpp"
#include "include/Joueur.hpp"
#include <iostream>

/**
 * @brief Constructeur de la classe Jeu
 * 
 * Initialise le jeu en :
 * 1. Créant un tableau de 3 joueurs
 * 2. Initialisant chaque joueur avec ses pièces
 * 3. Plaçant les pièces sur le plateau
 * 4. Affichant la matrice initiale (debug)
 */
Jeu::Jeu(){
    playerList = new Joueur[3];
    for(int i=0;i<3;i++){
        playerList[i] = Joueur();
        InitPieceList(playerList[i], i + 1);
    }
    board.PlacePiece(playerList[0].getListPiece(), playerList[1].getListPiece(), playerList[2].getListPiece());
    //board.AffichageMatrice(board.getMatrix());
}

/**
 * @brief Initialise la liste des pièces pour un joueur
 * 
 * Crée et place les pièces dans l'ordre suivant :
 * - 8 pions
 * - 2 tours
 * - 2 cavaliers
 * - 2 fous
 * - 1 reine
 * - 1 roi
 * 
 * Note : Pour le joueur rouge (side=2), le roi et la reine sont inversés
 * 
 * @param joueur Référence au joueur à initialiser
 * @param side Numéro du joueur (1: Blanc, 2: Rouge, 3: Noir)
 */
void Jeu::InitPieceList(Joueur& joueur, int side) {
    Piece** list = new Piece*[16];
    // Création des 8 pions
    for (int i = 0; i < 8; i++) {
        list[i] = new Pion(side);
    }
    // Création des pièces majeures
    list[8] = new Tour(side);
    list[9] = new Cavalier(side);
    list[10] = new Fou(side);
    // Placement spécial pour le joueur rouge
    if(side==2){
        list[11] = new Roi(side);
        list[12] = new Reine(side);
    }
    else{
        list[11] = new Reine(side);
        list[12] = new Roi(side);
    }
    list[13] = new Fou(side);
    list[14] = new Cavalier(side);
    list[15] = new Tour(side);
    joueur.setListPiece(list);
}
