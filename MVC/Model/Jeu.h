#ifndef JEU_H
#define JEU_H
#include "Joueur.h"
#include "Plateau.h"

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
