#include "Jeu.h"
#include "Piece.h"
#include "Joueur.h"
#include <iostream>

Jeu::Jeu(){
    etatDeParti = false;
    ListeJoueur = new Joueur[3];
    for(int i=0;i<3;i++){
        ListeJoueur[i] = Joueur();
        InitListePiece(ListeJoueur[i], i + 1);
    }
    plateau.PlacerPiece(ListeJoueur[0].getListePiece(), ListeJoueur[1].getListePiece(), ListeJoueur[2].getListePiece());
    plateau.AffichageMatrice();
}


void Jeu::ChangerTourJoueur() {
   if(tourJoueur==1){
    tourJoueur=2;
   }
   else if(tourJoueur==2){
    tourJoueur=3;
   }
   else{
    tourJoueur=1;
   }
}

void Jeu::VerifStatutJoueur() {
    
}

void Jeu::InitListePiece(Joueur& joueur, int camp) {
    Piece* liste = new Piece[16];
    for (int i = 0; i < 16; i++) {
        liste[i] = Piece(camp);
    }
    joueur.setListePiece(liste);
}

Jeu::~Jeu() {
    delete[] ListeJoueur;
}