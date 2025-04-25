#ifndef PLATEAU_H
#define PLATEAU_H
#include "Piece.h"
#include "Joueur.h"
#include <vector>

class Piece;

class Plateau {
public:
    Plateau();
    void InitMatrix();
    void PlacePiece(Piece** whitePieces, Piece** redPieces, Piece** blackPieces);
    void AffichageMatrice(Piece* matrix[12][12]);
    std::vector<std::pair<int, int>> MovePiece(int xStart, int yStart);
    void AfficherCoupsPossibles(std::vector<std::pair<int, int>> possibleMoves);
    Piece* matrix[12][12];
    
    void Move(int xStart, int yStart,int xMove,int yMove,Joueur* playerList, Piece* matrix[12][12]);
    std::vector<std::string> IsInCheck(Joueur* playerList, Piece* matrix[12][12]);
    bool IsCheckmate(int indexPlayer, std::string playerName, Joueur* playerList);
    std::vector<std::pair<int, int>> RemoveKingInCheckMoves(std::string playerName, Piece* piece);
    bool Stalemate(int indexPlayer, const std::string& playerName, Joueur* playerList);


    bool PawnOnEdge(int xStart, int yStart,int xMove, Piece* matrix[12][12]);
    void PawnPromotion(int xStart, int yStart, int promotionChoice, Joueur* playerList,Piece* matrix[12][12]);


    std::vector<std::string> sidesInCheck;
    std::string winner;
    bool endOfGame=false;

    void IsCastling(int xStart, int yStart,int xMove,int yMove, Piece* matrix[12][12]);
    bool castling=false;

    bool isEnPassant=false;

    bool whiteEnPassant=false;
    bool redEnPassant=false;
    bool blackEnPassant=false;
};


#endif
