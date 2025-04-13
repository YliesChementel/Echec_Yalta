#ifndef PLATEAU_H
#define PLATEAU_H
#include "Piece.h"
#include <vector>

class Piece;

class Plateau {
public:
    Plateau();
    void InitMatrice();
    void PlacerPiece(Piece** ListePiece1, Piece** ListePiece2, Piece** ListePiece3);
    void AffichageMatrice();
    std::vector<std::pair<int, int>> DeplacerPiece(int xOrigine, int yOrigine);
    std::vector<std::pair<int, int>> ObtenirCoupsPossibles(Piece* piece, int xOrigine, int yOrigine);
    void AfficherCoupsPossibles(std::vector<std::pair<int, int>> coupsPossibles);
    Piece* matrice[12][12];
    
    void DeplacementAutoriser(int xOrigine, int yOrigine,int xCoup,int yCoup);
};


#endif
