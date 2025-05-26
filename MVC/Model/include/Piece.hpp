/**
 * @file Piece.hpp
 * @brief Classes représentant les différentes pièces du jeu d'échecs
 */

#ifndef PIECE_HPP
#define PIECE_HPP
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @class Piece
 * @brief Classe de base abstraite pour toutes les pièces du jeu
 * 
 * Cette classe définit l'interface commune à toutes les pièces :
 * - Calcul des mouvements possibles
 * - Gestion de la position
 * - Gestion de l'état (déjà déplacée, en échec, etc.)
 */
class Piece {
public:
    /**
     * @brief Constructeur initialisant une pièce
     * @param side Numéro du joueur propriétaire (1: Blanc, 2: Rouge, 3: Noir)
     */
    Piece(int side) : side(side) {}

    /**
     * @brief Calcule les mouvements possibles pour la pièce
     * @param xStart Position X de départ
     * @param yStart Position Y de départ
     * @param matrix Matrice du plateau
     * @return Liste des positions possibles
     */
    virtual std::vector<std::pair<int, int>> possibleMove(int xStart, int yStart, Piece* matrix[12][12]);

    /**
     * @brief Obtient le numéro du joueur propriétaire
     * @return Numéro du joueur
     */
    int getSide();

    /**
     * @brief Modifie le numéro du joueur propriétaire
     * @param side Nouveau numéro de joueur
     */
    void setSide(int side);

    /**
     * @brief Obtient la position X de la pièce
     * @return Position X
     */
    int getXPosition(){ return xPosition;};

    /**
     * @brief Obtient la position Y de la pièce
     * @return Position Y
     */
    int getYPosition(){ return yPosition;};

    /**
     * @brief Modifie la position X de la pièce
     * @param xPosition Nouvelle position X
     */
    void setXPosition(int xPosition){this->xPosition=xPosition;};

    /**
     * @brief Modifie la position Y de la pièce
     * @param yPosition Nouvelle position Y
     */
    void setYPosition(int yPosition){this->yPosition=yPosition;};

    /**
     * @brief Vérifie si la pièce a déjà été déplacée
     * @return true si la pièce a déjà bougé
     */
    bool getHasAlreadyMoved(){ return hasAlreadyMoved;};

    /**
     * @brief Modifie l'état de déplacement de la pièce
     * @param hasAlreadyMoved Nouvel état
     */
    void setHasAlreadyMoved(bool hasAlreadyMoved){this->hasAlreadyMoved=hasAlreadyMoved;}

    /**
     * @brief Obtient le type de la pièce
     * @return Type de la pièce (T: Tour, C: Cavalier, etc.)
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Clone la pièce
     * @return Pointeur vers une nouvelle pièce identique
     */
    virtual Piece* clone() const = 0;

    /**
     * @brief Destructeur virtuel
     */
    virtual ~Piece() {}

    bool inCheck = false;      ///< Indique si la pièce est en échec
    bool enPassant = false;    ///< Indique si la pièce peut être prise en passant

private:
    int side;                  ///< Numéro du joueur propriétaire
    int xPosition;             ///< Position X sur le plateau
    int yPosition;             ///< Position Y sur le plateau
    bool hasAlreadyMoved=false;///< Indique si la pièce a déjà été déplacée

protected:
    std::vector<std::pair<int, int>> directions = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};  ///< Directions de déplacement possibles

    /**
     * @brief Détermine la sous-matrice en fonction des coordonnées
     * @param x Position X
     * @param y Position Y
     * @return Numéro de la sous-matrice
     */
    int determineSubMatrix(int x, int y) const;

    /**
     * @brief Ajuste les coordonnées pour le plateau Yalta
     * @param xStart Position X de départ
     * @param yStart Position Y de départ
     * @param xDestination Position X d'arrivée
     * @param yDestination Position Y d'arrivée
     * @param xMove Déplacement en X
     * @param yMove Déplacement en Y
     */
    void adjustCoordinates(int& xStart, int& yStart, int& xDestination, int& yDestination,int& xMove, int& yMove) const;

    // Méthodes de calcul des mouvements
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

/**
 * @class Tour
 * @brief Classe représentant une tour
 */
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

/**
 * @class Cavalier
 * @brief Classe représentant un cavalier
 */
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

            // Élimination des doublons
            std::sort(possibleMoves.begin(), possibleMoves.end());
            auto last = std::unique(possibleMoves.begin(), possibleMoves.end());
            possibleMoves.erase(last, possibleMoves.end());

            // Gestion des cas particuliers du plateau Yalta
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

/**
 * @class Fou
 * @brief Classe représentant un fou
 */
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

/**
 * @class Reine
 * @brief Classe représentant une reine
 */
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

/**
 * @class Roi
 * @brief Classe représentant un roi
 */
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

/**
 * @class Pion
 * @brief Classe représentant un pion
 */
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