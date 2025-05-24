#ifndef JEU_HPP
#define JEU_HPP
#include "Joueur.hpp"
#include "Plateau.hpp"

class Jeu {
public:
    Jeu();
    ~Jeu() { delete[] playerList; }
    void InitPieceList(Joueur& joueur, int side);
    Plateau& getBoard() { return board; }
    Joueur* getPlayerList() { return playerList; }

private:
    Joueur* playerList;
    Plateau board;
};


#endif
