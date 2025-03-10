#ifndef PIECE_H
#define PIECE_H
#include <string>

class Piece {
public:
    Piece(int camp = 0);
    virtual bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup);
    int GetCamp();
    void SetCamp(int camp);
    virtual std::string GetType() const = 0;

private:
    int camp;
};


class Roi : public Piece {
public:
    Roi(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override {
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
    std::string GetType() const override { return "Roi"; }
};

class Fou : public Piece {
public:
    Fou(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        if((xCoup==xOrigine+1 && yCoup==yOrigine+1) ||
        (xCoup==xOrigine-1 && yCoup==yOrigine-1) ||
        (xCoup==xOrigine-1 && yCoup==yOrigine+1) ||
        (xCoup==xOrigine+1 && yCoup==yOrigine-1)){
            return true;
        }
        return false;
    };
    std::string GetType() const override { return "Fou"; }
};


class Tour : public Piece {
public:
    Tour(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        if((xCoup<xOrigine+8 && xCoup>xOrigine-8 && yCoup == yOrigine) || (yCoup<yOrigine+8 && yCoup>yOrigine-8 && yCoup == yOrigine)){
            return true;
        }
        return false;
    };
    std::string GetType() const override  { return "Tour"; }
};


class Reine : public Piece {
public:
    Reine(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
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
    std::string GetType() const override  { return "Reine"; }
};

class Cavalier : public Piece {
public:
    Cavalier(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        if( (xCoup==xOrigine+2 && (yCoup==yOrigine+1 || yCoup==yOrigine-1))  ||
        (xCoup==xOrigine-2 && (yCoup==yOrigine+1 || yCoup==yOrigine-1))  ||
        (yCoup==yOrigine+2 && (xCoup==xOrigine+1 || xCoup==xOrigine-1))  ||
        (yCoup==yOrigine-2 && (xCoup==xOrigine+1 || xCoup==xOrigine-1))){
            return true;
        }
        return false;
    };
    std::string GetType() const override  { return "Cavalier"; }
};

class Pion : public Piece {
public:
    Pion(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        return false;
    };
    std::string GetType() const override  { return "Pion"; }
};

#endif
