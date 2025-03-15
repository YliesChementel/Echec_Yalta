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
    int determineSousMatrice(int x, int y) const {// Déterminez la sous-matrice en fonction des coordonnées
        if (x < 4 && y < 4) return 1; // haut gauche
        if (x < 4 && y >= 4 && y < 8) return 2; // haut milieu
        if (y < 4 && x >= 4 && x < 8) return 3; // milieu gauche
        if (y >= 7 && x >= 4 && x < 8) return 4; // milieu droite
        if (x >= 7 && y >= 4 && y < 8) return 5; // bas milieu
        if (x >= 7 && y >= 7) return 6; // bas droite
        return 0;
    }

    bool estAuDessusDiagonal(int x, int y)const {
        return y > x;
    }
    
    bool estEnDessousDiagonal(int x, int y)const {
        return y < x;
    }
    
    bool EstSurDiagonal(int x, int y) const{
        return y == x;
    }

    
    bool estAuDessusDiagonaleMontante(int x, int y) {
        return y > x - 4;
    }
    
    bool estEnDessousDiagonaleMontante(int x, int y) {
        return y < x - 4;
    }
    
    bool estAuDessusDiagonaleMontante2(int x, int y) {
        return y > x + 4;
    }
    
    bool estEnDessousDiagonaleMontante2(int x, int y) {
        return y < x + 4;
    }
    
    
    bool estEnDessousDiagonaleDescendante(int x, int y) const{
        return y > 7 - x;
    }
    bool estAuDessusDiagonaleDescendante(int x, int y) const{
        return y < 7 - x;
    }
    bool estSurDiagonaleDescendante(int x, int y) const{
        return y == 7 - x;
    }
    
    

    void ajustementCoordonnees(int& xOrigine, int& yOrigine, int& xCoup, int& yCoup) const {
        int matriceOrigine = determineSousMatrice(xOrigine, yOrigine);
        int matriceDestination = determineSousMatrice(xCoup, yCoup);

        if (this->GetType() == "F" || this->GetType()=="R"){
            if(xOrigine == yOrigine){
                if  ((xOrigine == 0 || xOrigine == 1 || xOrigine == 2 || xOrigine == 3) && (matriceDestination == 4 || matriceDestination == 5)) {
                    if(matriceDestination == 4){
                        yCoup -= 4;
                    }
                    else{
                        xCoup -= 4;
                    }
                }
                else if((xOrigine == 11 || xOrigine == 10 || xOrigine == 9 || xOrigine == 8) && (matriceDestination == 2 || matriceDestination == 3)){
                    if(matriceDestination == 3){
                        xOrigine -= 4;
                        yOrigine -= 4;
                        xCoup = 7 - xCoup;
                    }
                    else{
                        xOrigine -= 4;
                        yOrigine -= 4;
                        yCoup = 7 - yCoup;
                    }
                }
            }

            else if (matriceOrigine == 6 && matriceDestination == 2 && estEnDessousDiagonal(xOrigine, yOrigine)) {//pour diagonales entre les sous-matrices 6, 2 et 3
                xOrigine -= 4;
                yOrigine -= 4;
                yCoup = 7 - yCoup;
            }
            else if (matriceOrigine == 2 && matriceDestination == 6) {
                xCoup -= 4;
                yCoup -= 4;
                yOrigine = 7 - yOrigine;
            }
            else if (matriceOrigine == 6 && matriceDestination == 3 && estAuDessusDiagonal(xOrigine, yOrigine)) {
                xOrigine -= 4;
                yOrigine -= 4; 
                xCoup = 7 - xCoup;
            }
            else if (matriceOrigine == 3 && matriceDestination == 6) {
                xCoup -= 4;
                yCoup -= 4;
                xOrigine = 7 - xOrigine;
            }
            else if (matriceOrigine == 1 && matriceDestination == 4 && estEnDessousDiagonal(xOrigine, yOrigine)) {//pour diagonales entre les sous-matrices 1, 4 et 5
                yCoup -= 4;
            }
            else if (matriceOrigine == 4 && matriceDestination == 1) {
                yOrigine -= 4;
            }
            else if (matriceOrigine == 1 && matriceDestination == 5 && estAuDessusDiagonal(xOrigine, yOrigine)) {
                xCoup -= 4;
            }
            else if (matriceOrigine == 5 && matriceDestination == 1) {
                xOrigine -= 4;
            }
            
        }


        

        if (matriceOrigine == 4 && matriceDestination == 6) { // matrice milieu-droite inversé verticalement
            xOrigine = 11 - xOrigine;
        } else if (matriceOrigine == 6 && matriceDestination == 4) { // matrice milieu-droite inversé verticalement
            xCoup = 11 - xCoup;
        } else if (matriceOrigine == 5 && matriceDestination == 6) { // matrice bas-milieu inversé horizontalement
            yOrigine = 11 - yOrigine;
        } else if (matriceOrigine == 6 && matriceDestination == 5) { // matrice bas-milieu inversé horizontalement
            yCoup = 11 - yCoup;
        } else if (matriceOrigine == 2 && matriceDestination == 5) { // chemin plus court entre haut-milieu et bas-milieu 
            xCoup -= 4;
        } else if (matriceOrigine == 5 && matriceDestination == 2) { // chemin plus court entre haut-milieu et bas-milieu 
            xOrigine -= 4;
        } else if (matriceOrigine == 3 && matriceDestination == 4) { // chemin plus court entre milieu-gauche et milieu-droite
            yCoup -= 4;
        } else if (matriceOrigine == 4 && matriceDestination == 3) { // chemin plus court entre haut-milieu et bas-milieu 
            yOrigine -= 4;
        }
        else if (matriceOrigine == 4 && matriceDestination == 5) {
            xOrigine = 11 - xOrigine;
            yCoup = 11 - yCoup;
        }
        else if (matriceOrigine == 5 && matriceDestination == 4) {
            yOrigine = 11 - yOrigine;
            xCoup = 11 - xCoup;
        }


        
    }
};


class Roi : public Piece {
public:
    Roi(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override {
        ajustementCoordonnees(xOrigine, yOrigine, xCoup, yCoup);
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
        int matriceOrigine = determineSousMatrice(xOrigine, yOrigine);//le fou ne peut pas aller à la matrice opposé
        int matriceDestination = determineSousMatrice(xCoup, yCoup);
        if((estAuDessusDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==3 && matriceDestination==6)||

        (estEnDessousDiagonaleMontante(xOrigine, yOrigine) && matriceOrigine==5 && matriceDestination==1) ||
        (estAuDessusDiagonaleMontante(xOrigine, yOrigine) && matriceOrigine==5 && matriceDestination==4) || 
        (estAuDessusDiagonaleMontante2(xOrigine, yOrigine) && matriceOrigine==4 && matriceDestination==1) ||
        (estEnDessousDiagonaleMontante2(xOrigine, yOrigine) && matriceOrigine==4 && matriceDestination==5)){//vérif avant car il ne faut que les ajustement soit fait
            return false;
        }
        ajustementCoordonnees(xOrigine, yOrigine, xCoup, yCoup);
        if (std::abs(xCoup - xOrigine) == std::abs(yCoup - yOrigine)) {
            if ((matriceOrigine == 1 && matriceDestination == 6) ||//le fou ne peut pas aller à la matrice opposé
                (matriceOrigine == 6 && matriceDestination == 1) ||
                (matriceOrigine == 5 && matriceDestination == 3) ||
                (matriceOrigine == 3 && matriceDestination == 5) ||
                (matriceOrigine == 4 && matriceDestination == 2) ||
                (matriceOrigine == 2 && matriceDestination == 4) || 
                (estAuDessusDiagonal(xOrigine, yOrigine) && matriceOrigine==6 && matriceDestination==2) ||
                (estEnDessousDiagonal(xOrigine, yOrigine) && matriceOrigine==6 && matriceDestination==3)||

                (estEnDessousDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==2 && matriceDestination==3) ||
                (estAuDessusDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==2 && matriceDestination==6) ||
                (estEnDessousDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==3 && matriceDestination==2) ||

                (estEnDessousDiagonal(xOrigine, yOrigine) && matriceOrigine==1 && matriceDestination==5) 
            ){

                return false;
            }
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
        ajustementCoordonnees(xOrigine, yOrigine, xCoup, yCoup);
        if((xCoup<xOrigine+8 && xCoup>xOrigine-8 && yCoup == yOrigine) || (yCoup<yOrigine+8 && yCoup>yOrigine-8 && xCoup == xOrigine)){
            return true;
        }
        return false;
    };
    std::string GetType() const override  { return "T"; }

};


class Reine : public Piece {
public:
    Reine(int camp = 0) : Piece(camp) {}
    int GetCamp() { return Piece::GetCamp(); }
    void SetCamp(int camp) { Piece::SetCamp(camp); }
    bool Deplacement(int xOrigine, int yOrigine, int xCoup, int yCoup) override{
        int matriceOrigine = determineSousMatrice(xOrigine, yOrigine);//la reine ne peut pas aller à la matrice opposé
        int matriceDestination = determineSousMatrice(xCoup, yCoup);
        if((estAuDessusDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==3 && matriceDestination==6)||

        (estEnDessousDiagonaleMontante(xOrigine, yOrigine) && matriceOrigine==5 && matriceDestination==1) ||
        (estAuDessusDiagonaleMontante(xOrigine, yOrigine) && matriceOrigine==5 && matriceDestination==4) || 
        (estAuDessusDiagonaleMontante2(xOrigine, yOrigine) && matriceOrigine==4 && matriceDestination==1) ||
        (estEnDessousDiagonaleMontante2(xOrigine, yOrigine) && matriceOrigine==4 && matriceDestination==5)){//vérif avant car il ne faut que les ajustement soit fait
            return false;
        }
        ajustementCoordonnees(xOrigine, yOrigine, xCoup, yCoup);

        if((xCoup<xOrigine+8 && xCoup>xOrigine-8 && yCoup == yOrigine) || (yCoup<yOrigine+8 && yCoup>yOrigine-8 && yCoup == yOrigine)){
            return true;
        }

        if (std::abs(xCoup - xOrigine) == std::abs(yCoup - yOrigine)) {
            if ((matriceOrigine == 1 && matriceDestination == 6) ||//la reine ne peut pas aller à la matrice opposé
                (matriceOrigine == 6 && matriceDestination == 1) ||
                (matriceOrigine == 5 && matriceDestination == 3) ||
                (matriceOrigine == 3 && matriceDestination == 5) ||
                (matriceOrigine == 4 && matriceDestination == 2) ||
                (matriceOrigine == 2 && matriceDestination == 4) || 
                (estAuDessusDiagonal(xOrigine, yOrigine) && matriceOrigine==6 && matriceDestination==2) ||
                (estEnDessousDiagonal(xOrigine, yOrigine) && matriceOrigine==6 && matriceDestination==3)||

                (estEnDessousDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==2 && matriceDestination==3) ||
                (estAuDessusDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==2 && matriceDestination==6) ||
                (estEnDessousDiagonaleDescendante(xOrigine, yOrigine) && matriceOrigine==3 && matriceDestination==2) ||

                (estEnDessousDiagonal(xOrigine, yOrigine) && matriceOrigine==1 && matriceDestination==5) 
            ){

                return false;
            }
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
        ajustementCoordonnees(xOrigine, yOrigine, xCoup, yCoup);
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
        ajustementCoordonnees(xOrigine, yOrigine, xCoup, yCoup);
        return false;
    };
    std::string GetType() const override  { return "P"; }
};

#endif
