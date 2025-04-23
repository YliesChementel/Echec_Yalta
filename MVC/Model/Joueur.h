#ifndef JOUEUR_H
#define JOUEUR_H
#include "Piece.h"

class Joueur {
public:
    Joueur();
    Piece** getListPiece();
    int getSize();
    void setSize(int pieceListSize);
    void setListPiece(Piece** pieceList);
    void removePiece(Piece* piece);
    void replacePiece(Piece* oldPiece,Piece* newPiece);
    ~Joueur();

private:
    int pieceListSize = 16;
    Piece** pieceList;
};


#endif
