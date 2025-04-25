#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Piece {
public:
Piece(int side) : side(side) {}
    virtual std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart, Piece* matrix[12][12]);
    int getSide();
    void setSide(int side);
    int getXPosition(){ return xPosition;};
    int getYPosition(){ return yPosition;};
    void setXPosition(int xPosition){this->xPosition=xPosition;};
    void setYPosition(int yPosition){this->yPosition=yPosition;};
    bool getHasAlreadyMoved(){ return hasAlreadyMoved;};
    void setHasAlreadyMoved(bool hasAlreadyMoved){this->hasAlreadyMoved=hasAlreadyMoved;}
    virtual std::string getType() const = 0;

    // Méthode pour cloner une pièce
    virtual Piece* clone() const = 0;
    // Destructeur pour éviter les fuites de mémoire 
    virtual ~Piece() {}

    bool inCheck = false;
    bool enPassant = false;

private:
    int side;
    int xPosition;
    int yPosition;
    bool hasAlreadyMoved=false;

protected:
    std::vector<std::pair<int, int>> directions = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};

    // Détermine la sous-matrix en fonction des coordonnées
    int determineSubMatrix(int x, int y) const;

    //Ajustement obligatoirement pour toutes les pièces pour que le plateau fonctionne comme un plateau normal
    void adjustCoordinates(int& xStart, int& yStart, int& xDestination, int& yDestination,int& xMove, int& yMove) const;

    //Différents types de coup des pièces 
    void recursiveMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves,Piece* matrix[12][12]);
    void knightMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves, int verification,bool methodTwo,Piece* matrix[12][12]);
    void kingMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves,Piece* matrix[12][12]);
    void castling(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]);
    void pawnMove(int xStart, int yStart,std::vector<std::pair<int, int>>& possibleMoves, int stop,Piece* matrix[12][12]);
    void pawnMove2(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]);
    void captureByPawn(int x, int y, int xMove, int yMove, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]);
    void captureOnBoardCenter(int x, int y, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]);
    void captureEnPassant(int x, int y, int xMove, int yMove, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]);
};


class Tour : public Piece {
    public:
        Tour(int side) : Piece(side) {}
        int getSide() { return Piece::getSide(); }
        void setSide(int side) { Piece::setSide(side); }
        std::string getType() const override  { return "T"; }

        virtual Piece* clone() const override {
            return new Tour(*this);
        }

        std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart, Piece* matrix[12][12]){
            std::vector<std::pair<int, int>> possibleMoves;
            recursiveMove(xStart,yStart,directions[5].first,directions[5].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[1].first,directions[1].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[3].first,directions[3].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[7].first,directions[7].second,possibleMoves,matrix);
            return possibleMoves;
        }
};

class Cavalier : public Piece {
    public:
        Cavalier(int side) : Piece(side) {}
        int getSide() { return Piece::getSide(); }
        void setSide(int side) { Piece::setSide(side); }
        std::string getType() const override  { return "C"; }

        virtual Piece* clone() const override {
            return new Cavalier(*this);
        }

        std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart,Piece* matrix[12][12]){
            std::vector<std::pair<int, int>> possibleMoves;
            knightMove(xStart,yStart,directions[1].first,directions[1].second,possibleMoves,0,false,matrix);
            knightMove(xStart,yStart,directions[3].first,directions[3].second,possibleMoves,0,false,matrix);
            knightMove(xStart,yStart,directions[5].first,directions[5].second,possibleMoves,0,false,matrix);
            knightMove(xStart,yStart,directions[7].first,directions[7].second,possibleMoves,0,false,matrix);

            knightMove(xStart,yStart,directions[1].first,directions[1].second,possibleMoves,0,true,matrix);
            knightMove(xStart,yStart,directions[3].first,directions[3].second,possibleMoves,0,true,matrix);
            knightMove(xStart,yStart,directions[5].first,directions[5].second,possibleMoves,0,true,matrix);
            knightMove(xStart,yStart,directions[7].first,directions[7].second,possibleMoves,0,true,matrix);

            ////////////////////////////////////////////////////
            //Trier les doublons
            std::sort(possibleMoves.begin(), possibleMoves.end());
            auto last = std::unique(possibleMoves.begin(), possibleMoves.end());
            possibleMoves.erase(last, possibleMoves.end());

            if(xStart==3 && yStart==3){
                possibleMoves.emplace_back(8, 8);
            }
            else if(xStart==3 && yStart==4){
                possibleMoves.emplace_back(4, 8);
            }
            else if(xStart==4 && yStart==3){
                possibleMoves.emplace_back(8, 4);
            }
            else if(xStart==8 && yStart==8){
                possibleMoves.emplace_back(3, 3);

            }
            else if(xStart==8 && yStart==4){
                possibleMoves.emplace_back(4, 3);
            }
            else if(xStart==4 && yStart==8){
                possibleMoves.emplace_back(3, 4);
            }

            return possibleMoves;
        }
};

class Fou : public Piece {
    public:
        Fou(int side) : Piece(side) {}
        int getSide() { return Piece::getSide(); }
        void setSide(int side) { Piece::setSide(side); }
        std::string getType() const override  { return "F"; }

        virtual Piece* clone() const override {
            return new Fou(*this);
        }

        std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart, Piece* matrix[12][12]){
            std::vector<std::pair<int, int>> possibleMoves;
            recursiveMove(xStart,yStart,directions[0].first,directions[0].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[2].first,directions[2].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[4].first,directions[4].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[6].first,directions[6].second,possibleMoves,matrix);
            return possibleMoves;
        }
};

class Reine : public Piece {
    public:
        Reine(int side) : Piece(side) {}
        int getSide() { return Piece::getSide(); }
        void setSide(int side) { Piece::setSide(side); }
        std::string getType() const override  { return "R"; }

        virtual Piece* clone() const override {
            return new Reine(*this);
        }

        std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart, Piece* matrix[12][12]){
            std::vector<std::pair<int, int>> possibleMoves;
            recursiveMove(xStart,yStart,directions[0].first,directions[0].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[1].first,directions[1].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[2].first,directions[2].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[3].first,directions[3].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[4].first,directions[4].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[5].first,directions[5].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[6].first,directions[6].second,possibleMoves,matrix);
            recursiveMove(xStart,yStart,directions[7].first,directions[7].second,possibleMoves,matrix);
            return possibleMoves;
        }
};

class Roi : public Piece {
    public:
        Roi(int side) : Piece(side) {}
        int getSide() { return Piece::getSide(); }
        void setSide(int side) { Piece::setSide(side); }
        std::string getType() const override  { return "r"; }

        virtual Piece* clone() const override {
            return new Roi(*this);
        }

        std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart,Piece* matrix[12][12]){
            std::vector<std::pair<int, int>> possibleMoves;
            kingMove(xStart,yStart,directions[0].first,directions[0].second,possibleMoves,matrix);
            kingMove(xStart,yStart,directions[1].first,directions[1].second,possibleMoves,matrix);
            kingMove(xStart,yStart,directions[2].first,directions[2].second,possibleMoves,matrix);
            kingMove(xStart,yStart,directions[3].first,directions[3].second,possibleMoves,matrix);
            kingMove(xStart,yStart,directions[4].first,directions[4].second,possibleMoves,matrix);
            kingMove(xStart,yStart,directions[5].first,directions[5].second,possibleMoves,matrix);
            kingMove(xStart,yStart,directions[6].first,directions[6].second,possibleMoves,matrix);
            kingMove(xStart,yStart,directions[7].first,directions[7].second,possibleMoves,matrix);
            if(!this->getHasAlreadyMoved() && !inCheck){
                castling(xStart, yStart, possibleMoves, matrix);
            }
            return possibleMoves;
        }
};

class Pion : public Piece {
    public:
        Pion(int side) : Piece(side) {}
        int getSide() { return Piece::getSide(); }
        void setSide(int side) { Piece::setSide(side); }
        std::string getType() const override  { return "P"; }

        virtual Piece* clone() const override {
            return new Pion(*this);
        }

        std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart,Piece* matrix[12][12]){
            std::vector<std::pair<int, int>> possibleMoves;
            if(this->getHasAlreadyMoved()){
                pawnMove2(xStart,yStart,possibleMoves,matrix);
            }else{
                pawnMove(xStart,yStart,possibleMoves,0,matrix);
            } 
            return possibleMoves;
        }
};

#endif