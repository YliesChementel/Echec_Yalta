#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Plateau;

class Piece {
public:
Piece(int camp, Plateau& plateau) : camp(camp), plateau(plateau) {}
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
    void ajustementCoordonnees(int& xOrigine, int& yOrigine, int& xdestination, int& ydestination,int& xCoup, int& yCoup) const;

    //Différents types de coup des pièces 
    void CoupRecursif(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles);
    void CoupCavalier(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles,int verification,bool methodeDeux);
    void CoupRoi(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles);
    void CoupPion(int xOrigine, int yOrigine,std::vector<std::pair<int, int>>& coupsPossibles, int arret);
};


class Tour : public Piece {
    public:
        Tour(int camp, Plateau& plateau) : Piece(camp, plateau) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "T"; }
        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupRecursif(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles);
            return coupsPossibles;
        }
};

class Cavalier : public Piece {
    public:
        Cavalier(int camp, Plateau& plateau) : Piece(camp, plateau) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "C"; }
        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupCavalier(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles,0,false);
            CoupCavalier(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles,0,false);
            CoupCavalier(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles,0,false);
            CoupCavalier(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles,0,false);

            CoupCavalier(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles,0,true);
            CoupCavalier(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles,0,true);
            CoupCavalier(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles,0,true);
            CoupCavalier(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles,0,true);

            ////////////////////////////////////////////////////
            //Trier les doublons
            std::sort(coupsPossibles.begin(), coupsPossibles.end());
            auto last = std::unique(coupsPossibles.begin(), coupsPossibles.end());
            coupsPossibles.erase(last, coupsPossibles.end());

            if(xOrigine==3 && yOrigine==3){
                coupsPossibles.emplace_back(8, 8);
            }
            else if(xOrigine==3 && yOrigine==4){
                coupsPossibles.emplace_back(4, 8);
            }
            else if(xOrigine==4 && yOrigine==3){
                coupsPossibles.emplace_back(8, 4);
            }
            else if(xOrigine==8 && yOrigine==8){
                coupsPossibles.emplace_back(3, 3);

            }
            else if(xOrigine==8 && yOrigine==4){
                coupsPossibles.emplace_back(4, 3);
            }
            else if(xOrigine==4 && yOrigine==8){
                coupsPossibles.emplace_back(3, 4);
            }

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
            CoupRecursif(xOrigine,yOrigine,directions[0].first,directions[0].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[2].first,directions[2].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[4].first,directions[4].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[6].first,directions[6].second,coupsPossibles);
            return coupsPossibles;
        }
};

class Reine : public Piece {
    public:
        Reine(int camp, Plateau& plateau) : Piece(camp, plateau) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "R"; }
        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupRecursif(xOrigine,yOrigine,directions[0].first,directions[0].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[2].first,directions[2].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[4].first,directions[4].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[6].first,directions[6].second,coupsPossibles);
            CoupRecursif(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles);
            return coupsPossibles;
        }
};

class Roi : public Piece {
    public:
        Roi(int camp, Plateau& plateau) : Piece(camp, plateau) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "r"; }
        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupRoi(xOrigine,yOrigine,directions[0].first,directions[0].second,coupsPossibles);
            CoupRoi(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles);
            CoupRoi(xOrigine,yOrigine,directions[2].first,directions[2].second,coupsPossibles);
            CoupRoi(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles);
            CoupRoi(xOrigine,yOrigine,directions[4].first,directions[4].second,coupsPossibles);
            CoupRoi(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles);
            CoupRoi(xOrigine,yOrigine,directions[6].first,directions[6].second,coupsPossibles);
            CoupRoi(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles);
            return coupsPossibles;
        }
};

class Pion : public Piece {
    public:
        Pion(int camp, Plateau& plateau) : Piece(camp, plateau) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "P"; }
        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupPion(xOrigine,yOrigine,coupsPossibles,0);
            return coupsPossibles;
        }
};

#endif