#ifndef PLATEAU_H
#define PLATEAU_H
#include "Piece.h"

class Plateau {
public:
    Plateau();
    void InitMatrice();
    void UpdateMatrice(Piece piece, int coup);
    void AffichageMatrice();

private:
    Piece matrice[12][12];
};


#endif
