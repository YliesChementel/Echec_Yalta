#include "Jeu.h"
#include "Piece.h"
#include "Joueur.h"
#include <iostream>

Jeu::Jeu(){
    playerList = new Joueur[3];
    for(int i=0;i<3;i++){
        playerList[i] = Joueur();
        InitPieceList(playerList[i], i + 1);
    }
    board.PlacePiece(playerList[0].getListPiece(), playerList[1].getListPiece(), playerList[2].getListPiece());
}

void Jeu::InitPieceList(Joueur& joueur, int side) {
    Piece** list = new Piece*[16];
    for (int i = 0; i < 8; i++) {
        list[i] = new Pion(side);
    }
    list[8] = new Tour(side);
    list[9] = new Cavalier(side);
    list[10] = new Fou(side);
    if(side==2){
        list[11] = new Reine(side);
        list[12] = new Roi(side);
        
    }
    else{
        list[11] = new Roi(side);
        list[12] = new Reine(side);
    }
    list[13] = new Fou(side);
    list[14] = new Cavalier(side);
    list[15] = new Tour(side);
    joueur.setListPiece(list);
}
