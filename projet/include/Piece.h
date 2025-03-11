#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>

class Piece {
public:
    Piece(int camp = 0);
    virtual bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup);
    int GetCamp();
    void SetCamp(int camp);
    virtual std::string GetType() const = 0;

private:
    int camp;

protected:
    int determineSousMatrice(int x, int y) {// Déterminez la sous-matrice en fonction des coordonnées
        if (x < 4 && y < 4) {// haut gauche
            return 1;
        } else if (x < 4 && y < 8 && y > 3) {// haut milieu
            return 2;
        } else if (y < 4 && x < 8 && x > 3) {// milieu gauche
            return 3;
        } else if ( y > 7 && x < 8 && x > 3) {// milieu droite
            return 4;
        } else if (x > 7 && y < 8 && y > 3) {// bas milieu
            return 5;
        } else if(x > 7 && y > 7){// bas droite
            return 6;
        }
        return 0;
    }
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
    std::string GetType() const override { return "r"; }
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
    std::string GetType() const override { return "F"; }
};


class Tour : public Piece {
public:
    Tour(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        if(this->determineSousMatrice(xOrigine,yOrigine)==4 && this->determineSousMatrice(xCoup,yCoup)==6){// matrice milieu-droite inversé verticalement
            xOrigine = 11 - xOrigine;
            std::cout << "test1" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==6 && this->determineSousMatrice(xCoup,yCoup)==4){// matrice milieu-droite inversé verticalement
            xCoup = 11 - xCoup;
            std::cout << "test2" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==5 && this->determineSousMatrice(xCoup,yCoup)==6){// matrice bas-milieu inversé horizontalement
            yOrigine = 11 - yOrigine;
            std::cout << "test3" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==6 && this->determineSousMatrice(xCoup,yCoup)==5){// matrice bas-milieu inversé horizontalement
            yCoup = 11 - yCoup;
            std::cout << "test4" << std::endl;
        }
        
        if((xCoup<xOrigine+8 && xCoup>xOrigine-8 && yCoup == yOrigine) || (yCoup<yOrigine+8 && yCoup>yOrigine-8 && xCoup == xOrigine)){
            return true;
        }
        return false;
    };
    std::string GetType() const override  { return "T"; }
    /*void ajusteCoordonnees(int& x, int& y) {
        int sousMatrice = determineSousMatrice(x, y);

        // Appliquez l'inversion en fonction de la sous-matrice
        switch (sousMatrice) {
            case 4:
                if (x >= 4 && x < 8) {// Inverser verticalement pour la sous-matrice 4
                    x = 11 - x; 
                }
                break;
            case 5:
                // Inverser horizontalement pour la sous-matrice 5
                if (y >= 4 && y < 8) {
                    y = 7 - y; // Inversion horizontale
                }
                break;
        }
    }*/

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
    std::string GetType() const override  { return "R"; }
};

class Cavalier : public Piece {
public:
    Cavalier(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        if(this->determineSousMatrice(xOrigine,yOrigine)==4 && this->determineSousMatrice(xCoup,yCoup)==6){// matrice milieu-droite inversé verticalement
            xOrigine = 11 - xOrigine;
            std::cout << "test1" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==6 && this->determineSousMatrice(xCoup,yCoup)==4){// matrice milieu-droite inversé verticalement
            xCoup = 11 - xCoup;
            std::cout << "test2" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==5 && this->determineSousMatrice(xCoup,yCoup)==6){// matrice bas-milieu inversé horizontalement
            yOrigine = 11 - yOrigine;
            std::cout << "test3" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==6 && this->determineSousMatrice(xCoup,yCoup)==5){// matrice bas-milieu inversé horizontalement
            yCoup = 11 - yCoup;
            std::cout << "test4" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==2 && this->determineSousMatrice(xCoup,yCoup)==5){// chemin plus court entre haut-milieu et bas-milieu 
            xCoup = xCoup - 4;
            std::cout << "test5" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==5 && this->determineSousMatrice(xCoup,yCoup)==2){// chemin plus court entre haut-milieu et bas-milieu 
            xOrigine = xOrigine - 4;
            std::cout << "test6" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==3 && this->determineSousMatrice(xCoup,yCoup)==4){// chemin plus court entre milieu-gauche et milieu-droite
            yCoup = yCoup - 4;
            std::cout << "test7" << std::endl;
        }
        else if(this->determineSousMatrice(xOrigine,yOrigine)==4 && this->determineSousMatrice(xCoup,yCoup)==3){// chemin plus court entre haut-milieu et bas-milieu 
            yOrigine = yOrigine - 4;
            std::cout << "test8" << std::endl;
        }
        if( (xCoup==xOrigine+2 && (yCoup==yOrigine+1 || yCoup==yOrigine-1))  ||
        (xCoup==xOrigine-2 && (yCoup==yOrigine+1 || yCoup==yOrigine-1))  ||
        (yCoup==yOrigine+2 && (xCoup==xOrigine+1 || xCoup==xOrigine-1))  ||
        (yCoup==yOrigine-2 && (xCoup==xOrigine+1 || xCoup==xOrigine-1))){
            return true;
        }
        return false;
    };
    std::string GetType() const override  { return "C"; }
};

class Pion : public Piece {
public:
    Pion(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        return false;
    };
    std::string GetType() const override  { return "P"; }
};

#endif
