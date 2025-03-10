#ifndef PIECE_H
#define PIECE_H

class Piece {
public:
    Piece(int camp = 0);
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup);
    int GetCamp();
    void SetCamp(int camp);

private:
    int camp;
};


class Roi : public Piece {
public:
    Roi(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup){
        if(xCoup == xOrigine+1 || xCoup == xOrigine-1 || yCoup == yOrigine+1 || yCoup == yOrigine-1){
            return true;
        }
        else if((xCoup==xOrigine+1 && yCoup==yOrigine+1)||
        (xCoup==xOrigine-1 && yCoup==yOrigine-1)||
        (xCoup==xOrigine-1 && yCoup==yOrigine+1)||
        (xCoup==xOrigine+1 && yCoup==yOrigine-1)){
            return true;
        }
        return false;
    };
};

class Fou : public Piece {
public:
    Fou(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup){
        if((xCoup==xOrigine+1 && yCoup==yOrigine+1) ||
        (xCoup==xOrigine-1 && yCoup==yOrigine-1) ||
        (xCoup==xOrigine-1 && yCoup==yOrigine+1) ||
        (xCoup==xOrigine+1 && yCoup==yOrigine-1)){
            return true;
        }
        return false;
    };
};


class Tour : public Piece {
public:
    Tour(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup){
        if((xCoup<xOrigine+8 && xCoup>xOrigine-8 && yCoup == yOrigine) || (yCoup<yOrigine+8 && yCoup>yOrigine-8 && yCoup == yOrigine)){
            return true;
        }
        return false;
    };
};


class Reine : public Piece {
public:
    Reine(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup){
        if((xCoup<xOrigine+8 && xCoup>xOrigine-8 && yCoup == yOrigine) || (yCoup<yOrigine+8 && yCoup>yOrigine-8 && yCoup == yOrigine)){
            return true;
        }
        else if((xCoup==xOrigine+1 && yCoup==yOrigine+1)||
        (xCoup==xOrigine-1 && yCoup==yOrigine-1)||
        (xCoup==xOrigine-1 && yCoup==yOrigine+1)||
        (xCoup==xOrigine+1 && yCoup==yOrigine-1)){
            return true;
        }
        return false;
    };
};

class Cavalier : public Piece {
public:
    Cavalier(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup){
        if( (xCoup==xOrigine+2 && (yCoup==yOrigine+1 || yCoup==yOrigine-1))  ||
        (xCoup==xOrigine-2 && (yCoup==yOrigine+1 || yCoup==yOrigine-1))  ||
        (yCoup==yOrigine+2 && (xCoup==xOrigine+1 || xCoup==xOrigine-1))  ||
        (yCoup==yOrigine-2 && (xCoup==xOrigine+1 || xCoup==xOrigine-1))){
            return true;
        }
        return false;
    };
};

class Pion : public Piece {
public:
    Pion(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup){
        return false;
    };
};

#endif
