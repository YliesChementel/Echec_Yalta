#ifndef JOUEUR_H
#define JOUEUR_H
#include "Piece.h"

class Joueur {
public:
    Joueur();
    void JouerUnCoup(Piece* piece, int coup);
    Piece** getListePiece();
    int getTaille();
    void setTaille(int tailleListePiece);
    void setListePiece(Piece** listePiece);
    void retirerPiece(Piece* piece);
    void remplacerPiece(Piece* anciennePiece,Piece* nouvellePiece);
    ~Joueur();

private:
    bool statut;
    int tailleListePiece = 16;
    Piece** listePiece;
};


#endif
