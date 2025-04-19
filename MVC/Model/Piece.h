#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Piece {
public:
Piece(int camp) : camp(camp) {}
    virtual std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine,Piece* matrice[12][12]);
    int GetCamp();
    void SetCamp(int camp);
    int GetXPosition(){ return xPosition;};
    int GetYPosition(){ return yPosition;};
    void SetXPosition(int xPosition){this->xPosition=xPosition;};
    void SetYPosition(int yPosition){this->yPosition=yPosition;};
    virtual std::string GetType() const = 0;

    // Méthode virtuelle pure pour cloner une pièce
    virtual Piece* clone() const = 0;
    // Destructeur virtuel pour éviter les fuites de mémoire en cas de suppression à travers un pointeur de base.
    virtual ~Piece() {}

private:
    int camp;
    int xPosition;
    int yPosition;

protected:
    std::vector<std::pair<int, int>> directions = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};

    // Détermine la sous-matrice en fonction des coordonnées
    int determineSousMatrice(int x, int y) const;

    //Ajustement obligatoirement pour toutes les pièces pour que le plateau fonctionne comme un plateau normal
    void ajustementCoordonnees(int& xOrigine, int& yOrigine, int& xdestination, int& ydestination,int& xCoup, int& yCoup) const;

    //Différents types de coup des pièces 
    void CoupRecursif(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles,Piece* matrice[12][12]);
    void CoupCavalier(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles,int verification,bool methodeDeux,Piece* matrice[12][12]);
    void CoupRoi(int xOrigine, int yOrigine, int xCoup, int yCoup,std::vector<std::pair<int, int>>& coupsPossibles,Piece* matrice[12][12]);
    void CoupPion(int xOrigine, int yOrigine,std::vector<std::pair<int, int>>& coupsPossibles, int arret,Piece* matrice[12][12]);
    void capturePion(int x, int y, int xCoup, int yCoup, std::vector<std::pair<int, int>>& coups, Piece* matrice[12][12]);
    void CapturesRosaces(int x, int y, std::vector<std::pair<int, int>>& coups, Piece* matrice[12][12]);
};


class Tour : public Piece {
    public:
        Tour(int camp) : Piece(camp) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "T"; }

        virtual Piece* clone() const override {
            return new Tour(*this);
        }

        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine, Piece* matrice[12][12]){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupRecursif(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles,matrice);
            return coupsPossibles;
        }
};

class Cavalier : public Piece {
    public:
        Cavalier(int camp) : Piece(camp) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "C"; }

        virtual Piece* clone() const override {
            return new Cavalier(*this);
        }

        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine,Piece* matrice[12][12]){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupCavalier(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles,0,false,matrice);
            CoupCavalier(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles,0,false,matrice);
            CoupCavalier(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles,0,false,matrice);
            CoupCavalier(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles,0,false,matrice);

            CoupCavalier(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles,0,true,matrice);
            CoupCavalier(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles,0,true,matrice);
            CoupCavalier(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles,0,true,matrice);
            CoupCavalier(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles,0,true,matrice);

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
        Fou(int camp) : Piece(camp) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "F"; }

        virtual Piece* clone() const override {
            return new Fou(*this);
        }

        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine, Piece* matrice[12][12]){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupRecursif(xOrigine,yOrigine,directions[0].first,directions[0].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[2].first,directions[2].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[4].first,directions[4].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[6].first,directions[6].second,coupsPossibles,matrice);
            return coupsPossibles;
        }
};

class Reine : public Piece {
    public:
        Reine(int camp) : Piece(camp) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "R"; }

        virtual Piece* clone() const override {
            return new Reine(*this);
        }

        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine, Piece* matrice[12][12]){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupRecursif(xOrigine,yOrigine,directions[0].first,directions[0].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[2].first,directions[2].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[4].first,directions[4].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[6].first,directions[6].second,coupsPossibles,matrice);
            CoupRecursif(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles,matrice);
            return coupsPossibles;
        }
};

class Roi : public Piece {
    public:
        Roi(int camp) : Piece(camp) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "r"; }

        virtual Piece* clone() const override {
            return new Roi(*this);
        }

        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine,Piece* matrice[12][12]){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupRoi(xOrigine,yOrigine,directions[0].first,directions[0].second,coupsPossibles,matrice);
            CoupRoi(xOrigine,yOrigine,directions[1].first,directions[1].second,coupsPossibles,matrice);
            CoupRoi(xOrigine,yOrigine,directions[2].first,directions[2].second,coupsPossibles,matrice);
            CoupRoi(xOrigine,yOrigine,directions[3].first,directions[3].second,coupsPossibles,matrice);
            CoupRoi(xOrigine,yOrigine,directions[4].first,directions[4].second,coupsPossibles,matrice);
            CoupRoi(xOrigine,yOrigine,directions[5].first,directions[5].second,coupsPossibles,matrice);
            CoupRoi(xOrigine,yOrigine,directions[6].first,directions[6].second,coupsPossibles,matrice);
            CoupRoi(xOrigine,yOrigine,directions[7].first,directions[7].second,coupsPossibles,matrice);
            return coupsPossibles;
        }
};

class Pion : public Piece {
    public:
        Pion(int camp) : Piece(camp) {}
        int GetCamp() { return Piece::GetCamp(); }
        void SetCamp(int camp) { Piece::SetCamp(camp); }
        std::string GetType() const override  { return "P"; }

        virtual Piece* clone() const override {
            return new Pion(*this);
        }

        std::vector<std::pair<int, int>> DeplacementCoup(int xOrigine, int yOrigine,Piece* matrice[12][12]){
            std::vector<std::pair<int, int>> coupsPossibles;
            CoupPion(xOrigine,yOrigine,coupsPossibles,0,matrice);
            return coupsPossibles;
        }
};

#endif