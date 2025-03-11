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

    int xOrigine, yOrigine, xCoup, yCoup;
    bool tour;
    while(etatDeParti==false){
        tour=false;
        ChangerTourJoueur();
        std::cout << "Tour du joueur " << tourJoueur << std::endl;
        while(tour==false){
            std::cout << "Entrer les coordonnées de la pièce et de son coup" << std::endl;
            std::cin >> xOrigine >> yOrigine >> xCoup >> yCoup;
            tour=plateau.DeplacerPiece(tourJoueur,xOrigine, yOrigine, xCoup, yCoup);
        }
        plateau.AffichageMatrice();
        std::cout << std::endl;
    }
}

void Jeu::InitListePiece(Joueur& joueur, int camp) {
    Piece** liste = new Piece*[16];
    for (int i = 0; i < 8; i++) {
        liste[i] = new Pion(camp);
    }
    liste[8] = new Tour(camp);
    liste[9] = new Cavalier(camp);
    liste[10] = new Fou(camp);
    liste[11] = new Reine(camp);
    liste[12] = new Roi(camp);
    liste[13] = new Fou(camp);
    liste[14] = new Cavalier(camp);
    liste[15] = new Tour(camp);
    joueur.setListePiece(liste);
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
