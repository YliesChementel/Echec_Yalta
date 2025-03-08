#ifndef PLATEAU_H
#define PLATEAU_H
#include "Piece.h"

class Plateau {
public:
    Plateau();
    void InitMatrice();
    void PlacerPiece(Piece* ListePiece1, Piece* ListePiece2, Piece* ListePiece3);
    void UpdateMatrice(Piece* piece, int coupX, int coupY);
    void AffichageMatrice();

private:
    Piece* matrice[12][12];
};


#endif
