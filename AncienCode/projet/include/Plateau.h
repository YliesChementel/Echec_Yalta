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
    bool DeplacerPiece(int tourJoueur,int xOrigine, int yOrigine, int xCoup, int yCoup);
    void AffichageMatrice();
    std::vector<std::pair<int, int>> ObtenirCoupsPossibles(Piece* piece, int xOrigine, int yOrigine);
    void AfficherCoupsPossibles(std::vector<std::pair<int, int>> coupsPossibles);
    bool CheminLibre(int xOrigine, int yOrigine, int xCoup, int yCoup);
    Piece* GetPiece(int x, int y) const { return matrice[x][y]; }
    Piece* matrice[12][12];
    std::vector<std::pair<int, int>> DeplacerPiece2(int xOrigine, int yOrigine);
    void DeplacementAutoriser(int xOrigine, int yOrigine,int xCoup,int yCoup);
};


#endif
