#ifndef JOUEUR_H
#define JOUEUR_H
#include "Piece.h"

class Joueur {
public:
    Joueur();
    void JouerUnCoup(Piece piece, int coup);

private:
    bool statut;
    Piece listePiece[];
};


#endif
