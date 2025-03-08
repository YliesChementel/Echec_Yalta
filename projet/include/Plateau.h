#ifndef PLATEAU_H
#define PLATEAU_H
#include "Piece.h"

class Plateau {
public:
    Plateau();
    void InitMatrice();
    void UpdateMatrice(Piece piece, int coup);

private:
    Piece **Matrice;
};


#endif
