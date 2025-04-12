#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <vector>

class Plateau;

class Piece {
public:
Piece(int camp, Plateau& plateau) : camp(camp), plateau(plateau) {}

    virtual bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup);
    virtual std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine);
    int GetCamp();
    void SetCamp(int camp);
    virtual std::string GetType() const = 0;

private:
    int camp;
    Plateau& plateau;

protected:
    std::vector<std::pair<int, int>> directions = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};

    // Détermine la sous-matrice en fonction des coordonnées
    int determineSousMatrice(int x, int y) const;

    //Ajustement obligatoirement pour toutes les pièces pour que le plateau fonctionne comme un plateau normal
    void ajustementCoordonnees(int& xOrigine, int& yOrigine, int& xCoup, int& yCoup) const;

    void ajustementCoordonnees2(int& xOrigine, int& yOrigine, int& xdestination, int& ydestination,int& xCoup, int& yCoup) const;

    void recursive(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles);
};


class Tour : public Piece {
    public:
        Tour(int camp, Plateau& plateau) : Piece(camp, plateau) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "T"; }
        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine){
            std::vector<std::pair<int, int>> coupsPossibles;
            recursive(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles);
            recursive(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles);
            recursive(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles);
            recursive(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles);
            return coupsPossibles;
        }
};


class Fou : public Piece {
    public:
        Fou(int camp, Plateau& plateau) : Piece(camp, plateau) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "F"; }
        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine){
            std::vector<std::pair<int, int>> coupsPossibles;
            recursive(xOrigine,yOrigine,directions[0].first,directions[0].second,coupsPossibles);
            recursive(xOrigine,yOrigine,directions[2].first,directions[2].second,coupsPossibles);
            recursive(xOrigine,yOrigine,directions[4].first,directions[4].second,coupsPossibles);
            recursive(xOrigine,yOrigine,directions[6].first,directions[6].second,coupsPossibles);
            return coupsPossibles;
        }
};

#endif