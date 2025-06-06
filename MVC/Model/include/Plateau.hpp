#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include "Piece.hpp"
#include "Joueur.hpp"
#include <vector>
#include <atomic>
#include <thread>

class Piece;

class Plateau {
    public:
        Plateau();

        // Méthodes de gestion du plateau
        void InitMatrix();
        void PlacePiece(Piece** whitePieces, Piece** redPieces, Piece** blackPieces);
        void AffichageMatrice(Piece* matrix[12][12]);
        std::vector<std::pair<int, int>> MovePiece(int xStart, int yStart);
        void AfficherCoupsPossibles(std::vector<std::pair<int, int>> possibleMoves);
        void resetEnPassant(int side, Joueur* playerList);
        void Capture(int xMove, int yMove, int playerSide, Joueur* playerList, Piece* matrix[12][12]);
        void SpecialMoves(int xStart, int yStart, int xMove, int yMove, int playerSide, Joueur* playerList, Piece* matrix[12][12]);
        void Move(int xStart, int yStart,int xMove,int yMove,Joueur* playerList, Piece* matrix[12][12]);
        std::vector<std::string> IsInCheck(Joueur* playerList, Piece* matrix[12][12]);
        bool IsCheckmate(int indexPlayer, std::string playerName, Joueur* playerList);
        std::vector<std::pair<int, int>> RemoveKingInCheckMoves(std::string playerName, Piece* piece);
        bool Stalemate(int indexPlayer, const std::string& playerName, Joueur* playerList);
        bool PawnOnEdge(int xStart, int yStart,int xMove, Piece* matrix[12][12]);
        void PawnPromotion(int xStart, int yStart, int promotionChoice, Joueur* playerList,Piece* matrix[12][12]);
        void IsCastling(int xStart, int yStart,int xMove,int yMove, Piece* matrix[12][12]);
        void moveForAi(int xStart, int yStart,int xMove,int yMove, Joueur* playerList, Piece* matrix[12][12]);
        int evaluation(Joueur* players, int sideAi);
        int minmax(Plateau plateau, int sideMove, int sideAi, int depth, int OrignialDepth, int alpha, int beta, Joueur* players, std::atomic<bool>& stopFlag);
        Plateau* clone();

        // Getters
        Piece* getMatrix(int x, int y) const { return matrix[x][y]; }
        Piece* (*getMatrix())[12] { return matrix; }
        const std::vector<std::string>& getSidesInCheck() const { return sidesInCheck; }
        const std::string& getWinner() const { return winner; }
        bool isEndOfGame() const { return endOfGame; }
        bool isStalemate() const { return stalemate; }
        bool isCastling() const { return castling; }
        bool isEnPassantMove() const { return isEnPassant; }
        bool isWhiteEnPassant() const { return whiteEnPassant; }
        bool isRedEnPassant() const { return redEnPassant; }
        bool isBlackEnPassant() const { return blackEnPassant; }
        const std::pair<int, int>& getBestMoveStart() const { return bestMoveStart; }
        const std::pair<int, int>& getBestMoveEnd() const { return bestMoveEnd; }

        // Setters
        void setMatrix(int x, int y, Piece* piece) { matrix[x][y] = piece; }
        void setSidesInCheck(const std::vector<std::string>& sidesInCheck) { this->sidesInCheck = sidesInCheck; }
        void setWinner(const std::string& winner) { this->winner = winner; }
        void setEndOfGame(bool endOfGame) { this->endOfGame = endOfGame; }
        void setStalemate(bool stalemate) { this->stalemate = stalemate; }
        void setCastling(bool castling) { this->castling = castling; }
        void setEnPassant(bool isEnPassant) { this->isEnPassant = isEnPassant; }
        void setWhiteEnPassant(bool whiteEnPassant) { this->whiteEnPassant = whiteEnPassant; }
        void setRedEnPassant(bool redEnPassant) { this->redEnPassant = redEnPassant; }
        void setBlackEnPassant(bool blackEnPassant) { this->blackEnPassant = blackEnPassant; }
        void setBestMoveStart(const std::pair<int, int>& bestMoveStart) { this->bestMoveStart = bestMoveStart; }
        void setBestMoveEnd(const std::pair<int, int>& bestMoveEnd) { this->bestMoveEnd = bestMoveEnd; }

    private:
        Piece* matrix[12][12]; // Matrice 12x12 représentant le plateau de jeu, chaque case contient un pointeur vers une pièce ou nullptr
        std::vector<std::string> sidesInCheck; // Liste des couleurs (joueurs) actuellement en échec
        std::string winner; // Nom du joueur gagnant à la fin de la partie
        bool endOfGame; // Indique si la partie est terminée (échec et mat ou pat)
        bool stalemate; // Indique si la partie s'est terminée par un pat (aucun coup légal mais pas d'échec)
        bool castling; // Indique si un roque (castling) est en cours
        bool isEnPassant; // Indique si une prise en passant est possible pour le prochain coup
        bool whiteEnPassant; // Indique si une prise en passant est possible pour le joueur blanc
        bool redEnPassant; // Indique si une prise en passant est possible pour le joueur rouge
        bool blackEnPassant; // Indique si une prise en passant est possible pour le joueur noir
        std::pair<int, int> bestMoveStart; // Coordonnées du meilleur coup de départ trouvé par l'IA (minmax)
        std::pair<int, int> bestMoveEnd; // Coordonnées du meilleur coup d'arrivée trouvé par l'IA (minmax)
};

#endif
