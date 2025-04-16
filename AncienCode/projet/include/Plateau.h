#ifndef PLATEAU_H
#define PLATEAU_H
#include "Piece.h"
#include "Joueur.h"
#include <vector>

class Piece;

class Plateau {
public:
    Plateau();
    void InitMatrice();
    void PlacerPiece(Piece** ListePiece1, Piece** ListePiece2, Piece** ListePiece3);
    void AffichageMatrice(Piece* matrice[12][12]);
    std::vector<std::pair<int, int>> DeplacerPiece(int xOrigine, int yOrigine);
    std::vector<std::pair<int, int>> ObtenirCoupsPossibles(Piece* piece, int xOrigine, int yOrigine);
    void AfficherCoupsPossibles(std::vector<std::pair<int, int>> coupsPossibles);
    Piece* matrice[12][12];
    
    void Deplacement(int xOrigine, int yOrigine,int xCoup,int yCoup,Joueur* ListeJoueur, Piece* matrice[12][12]);
    std::vector<std::string> VerifierEnEchec(Joueur* ListeJoueur, Piece* matrice[12][12]);
    bool EstEchecEtMat(int indexJoueur, std::string nomJoueur, Joueur* ListeJoueur);
};


#endif
