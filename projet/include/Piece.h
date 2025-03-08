#ifndef PIECE_H
#define PIECE_H

class Piece {
public:
    Piece(int camp = 0);
    void Deplacement();
    int GetCamp();
    void SetCamp(int camp);

private:
    int camp;
};


#endif
