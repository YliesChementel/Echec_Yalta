#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include "Piece.hpp"

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
