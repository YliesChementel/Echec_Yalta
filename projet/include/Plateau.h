#ifndef PLATEAU_H
#define PLATEAU_H
#include "Piece.h"
#include <vector>

class Plateau {
public:
    Plateau();
    void InitMatrice();
    void PlacerPiece(Piece** ListePiece1, Piece** ListePiece2, Piece** ListePiece3);
    bool DeplacerPiece(int tourJoueur,int xOrigine, int yOrigine, int xCoup, int yCoup);
    void AffichageMatrice();
    std::vector<std::pair<int, int>> ObtenirCoupsPossibles(Piece* piece, int xOrigine, int yOrigine);
    void AfficherCoupsPossibles(int xOrigine, int yOrigine);
    bool CheminLibre(int xOrigine, int yOrigine, int xCoup, int yCoup);


private:
    Piece* matrice[12][12];
};


#endif
