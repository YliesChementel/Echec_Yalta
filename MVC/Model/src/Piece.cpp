/**
 * @file Piece.cpp
 * @brief Implémentation des classes de pièces du jeu d'échecs
 */

#include "include/Piece.hpp"
#include <iostream>
#include <algorithm>
#include "include/Plateau.hpp"

/**
 * @brief Implémentation par défaut de possibleMove
 * Retourne une position invalide (-1,-1)
 */
std::vector<std::pair<int, int>> Piece::possibleMove(int xStart, int yStart, Piece* matrix[12][12]){
    return std::vector<std::pair<int, int>>{std::make_pair(-1, -1)};
}

/**
 * @brief Obtient le numéro du joueur propriétaire
 * @return Numéro du joueur (1: Blanc, 2: Rouge, 3: Noir)
 */
int Piece::getSide() {
    return side;
}

/**
 * @brief Modifie le numéro du joueur propriétaire
 * @param side Nouveau numéro de joueur
 */
void Piece::setSide(int side) {
    this->side=side;
}

/**
 * @brief Détermine la sous-matrice en fonction des coordonnées
 * 
 * Le plateau Yalta est divisé en 6 sous-matrices :
 * 1: haut gauche   2: haut milieu   3: milieu gauche
 * 4: milieu droite 5: bas milieu    6: bas droite
 * 
 * @param x Position X
 * @param y Position Y
 * @return Numéro de la sous-matrice (1-6)
 */
int Piece::determineSubMatrix(int x, int y) const {
    if (x < 4 && y < 4) return 1; // haut gauche
    if (x < 4 && y >= 4 && y < 8) return 2; // haut milieu
    if (y < 4 && x >= 4 && x < 8) return 3; // milieu gauche
    if (y >= 7 && x >= 4 && x < 8) return 4; // milieu droite
    if (x >= 7 && y >= 4 && y < 8) return 5; // bas milieu
    if (x >= 7 && y >= 7) return 6; // bas droite
    return 0;
}

/**
 * @brief Ajuste les coordonnées pour le plateau Yalta
 * 
 * Gère les cas particuliers de déplacement entre les sous-matrices :
 * - Passage par le centre
 * - Inversion des coordonnées pour certaines sous-matrices
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xDestination Position X d'arrivée
 * @param yDestination Position Y d'arrivée
 * @param xMove Déplacement en X
 * @param yMove Déplacement en Y
 */
void Piece::adjustCoordinates(int& xStart, int& yStart, int& xDestination, int& yDestination,int& xMove, int& yMove) const {
    int matrixStart = determineSubMatrix(xStart, yStart);
    int matrixDestination = determineSubMatrix(xDestination, yDestination);

    // Gestion du passage par le centre
    if((xDestination > 3 && xDestination < 8) && (yDestination > 3 && yDestination < 8)){
        // Ajustements pour les mouvements horizontaux et verticaux
        if(xMove==-1 && yMove==0){//va en haut
            xDestination-=4;
        }
        else if(xMove==0 && yMove==1){//va à droite
            yDestination+=4;
        }
        else if(xMove==1 && yMove==0){// va en bas
            xDestination+=4;
        }
        else if(xMove==0 && yMove==-1){//va à gauche
            yDestination-=4;
        }

        // Ajustements pour les mouvements diagonaux
        else if(xMove==-1 && yMove==-1){// va haut-gauche
            if(matrixStart==4){
                yDestination-=4;
            }
            else if(matrixStart==5){
                xDestination-=4;
            }
        }
        else if(xMove==-1 && yMove==1){// va haut-droite
            if(matrixStart==3){
                yDestination+=4;
            }
            else if(matrixStart==5){
                xDestination-=4;
            }
        }
        else if(xMove==1 && yMove==1){// va bas-droite
            if(matrixStart==2){
                xDestination+=4;
            }
            else if(matrixStart==3){
                yDestination+=4;
            }
        }
        else if(xMove==1 && yMove==-1){// va bas-gauche
            if(matrixStart==2){
                xDestination+=4;
            }
            else if(matrixStart==4){
                yDestination-=4;
            }
        }
    }

    // Gestion des inversions entre sous-matrices
    else if ((matrixStart == 6 && matrixDestination == 5) || (matrixStart == 5 && yDestination == 3)) {
        // Inversion horizontale de la matrix bas-milieu + (cas particulier 7-3)
        yDestination = 11 - yDestination;
        if ((xMove == 0 || xMove == 1 || xMove == -1) && yMove == -1) {
            yMove = 1;
        }
    }
    else if ((matrixStart == 6 && matrixDestination == 4) || (matrixStart == 4 && xDestination == 3 )) {
        // Inversion verticale de la matrix milieu-droite
        xDestination = 11 - xDestination;
        if (xMove == -1 && (yMove == 0 || yMove == -1 || yMove == 1)) {
            xMove = 1;
        }
    }
}

// Fonctions utilitaires pour la vérification des mouvements

/**
 * @brief Vérifie si les coordonnées sont en dehors du plateau
 * @param x Position X
 * @param y Position Y
 * @return true si les coordonnées sont invalides
 */
bool isOutOfBoard(int x, int y) {
    return x < 0 || x >= 12 || y < 0 || y >= 12;
}

/**
 * @brief Vérifie si la case ciblée n'existe pas
 * @param x Position X
 * @param y Position Y
 * @return true si la case n'existe pas
 */
bool isSquareExist(int x, int y) {
    return (x < 4 && y > 7) || (x > 7 && y < 4);
}

/**
 * @brief Vérifie si le déplacement rencontre le mur de la matrix 5
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Déplacement en X
 * @param yMove Déplacement en Y
 * @return true si le mur est rencontré
 */
bool isWallInMatrix5(int xStart, int yStart, int xMove, int yMove) {
    return (yStart == 7 && (yStart + yMove == 8)) && ((xMove == 0 && yMove == 1) || (xMove == -1 && yMove == 1) || (xMove == 1 && yMove == 1));
}

/**
 * @brief Vérifie si le déplacement rencontre le mur de la matrix 4
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Déplacement en X
 * @param yMove Déplacement en Y
 * @return true si le mur est rencontré
 */
bool isWallInMatrix4(int xStart, int yStart, int xMove, int yMove) {
    return (xStart == 7 && (xStart + xMove == 8)) && ((xMove == 1 && yMove == -1) || (xMove == 1 && yMove == 0) || (xMove == 1 && yMove == 1));
}

/**
 * @brief Calcule récursivement les mouvements possibles dans une direction
 * 
 * Utilisé par les pièces qui peuvent se déplacer sur plusieurs cases
 * (Tour, Fou, Reine). Gère les cas particuliers du plateau Yalta.
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Direction X
 * @param yMove Direction Y
 * @param possibleMoves Liste des mouvements possibles
 * @param matrix Matrice du plateau
 */
void Piece::recursiveMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves,Piece* matrix[12][12]) {
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;
    if (!isWallInMatrix5(xStart, yStart, xMove, yMove)) {
        if (!isWallInMatrix4(xStart, yStart, xMove, yMove)) {
            // Gestion des cas particuliers du centre du plateau
            if((xStart==3 && yStart==3) && (xMove==1 && yMove==1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                    recursiveMove(4,8, xMove, yMove, possibleMoves,matrix);
                }
                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                    recursiveMove(8,4, xMove, yMove, possibleMoves,matrix);
                }
            }

            else if((xStart==3 && yStart==4) && (xMove==1 && yMove==-1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                    recursiveMove(8,8, 1, 1, possibleMoves,matrix);
                }
                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                    recursiveMove(4,3, 1, -1, possibleMoves,matrix);
                }
            }

            else if((xStart==4 && yStart==3) && (xMove==-1 && yMove==1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                    recursiveMove(8,8, 1, 1, possibleMoves,matrix);
                }
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                    recursiveMove(3,4, -1, 1, possibleMoves,matrix);
                }
            }

            else if((xStart==8 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                    recursiveMove(3,4, -1, 1, possibleMoves,matrix);
                }

                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                    recursiveMove(4,3, 1, -1, possibleMoves,matrix);
                }
            }

            else if((xStart==8 && yStart==4) && (xMove==-1 && yMove==-1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4,8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                    recursiveMove(4,8, 1, 1, possibleMoves,matrix);
                }

                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                    recursiveMove(3,3, -1, -1, possibleMoves,matrix);
                }

            }

            else if((xStart==4 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8,4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                    recursiveMove(8,4, 1, 1, possibleMoves,matrix);
                }
                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3,3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                    recursiveMove(3,3, -1, -1, possibleMoves,matrix);
                }
                
            }
            
            else{
                adjustCoordinates(xStart,yStart,xDestination,yDestination,xMove,yMove);
                if (!isOutOfBoard(xDestination, yDestination)) {
                    if (!isSquareExist(xDestination, yDestination)) {
                        if (matrix[xDestination][yDestination] == nullptr){
                            possibleMoves.emplace_back(xDestination, yDestination);
                            recursiveMove(xDestination, yDestination, xMove, yMove, possibleMoves,matrix);
                        }
                        else if(matrix[xDestination][yDestination] != nullptr && matrix[xDestination][yDestination]->getSide()!=this->getSide()){
                            possibleMoves.emplace_back(xDestination, yDestination);
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Calcule les mouvements possibles pour un cavalier
 * 
 * Le cavalier se déplace en L : 2 cases dans une direction puis 1 case perpendiculairement.
 * Gère les cas particuliers du plateau Yalta.
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Direction X
 * @param yMove Direction Y
 * @param possibleMoves Liste des mouvements possibles
 * @param verification Étape de vérification (0: premier mouvement, 1: second mouvement)
 * @param methodTwo Méthode alternative de calcul
 * @param matrix Matrice du plateau
 */
void Piece::knightMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves,int verification,bool methodTwo, Piece* matrix[12][12]) {
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;
    if (!isWallInMatrix5(xStart, yStart, xMove, yMove)) {
        if (!isWallInMatrix4(xStart, yStart, xMove, yMove)) {
            adjustCoordinates(xStart,yStart,xDestination,yDestination,xMove,yMove);
            if (!isOutOfBoard(xDestination, yDestination)) {
                if (!isSquareExist(xDestination, yDestination)) {
                    if(verification==0){
                        if(methodTwo){
                            knightMove(xDestination,yDestination,xMove,yMove,possibleMoves,1,true,matrix);
                        }
                        else{
                            if(xMove==0){
                                knightMove(xDestination,yDestination,-1,0,possibleMoves,1,false,matrix);
                                knightMove(xDestination,yDestination,1,0,possibleMoves,1,false,matrix);
                            }
                            else{
                                knightMove(xDestination,yDestination,0,-1,possibleMoves,1,false,matrix);
                                knightMove(xDestination,yDestination,0,1,possibleMoves,1,false,matrix);
                            }
                        }
                        
                    }
                    else if(verification==1){
                        if(methodTwo){
                            if(xMove==0){
                                knightMove(xDestination,yDestination,-1,0,possibleMoves,2,true,matrix);
                                knightMove(xDestination,yDestination,1,0,possibleMoves,2,true,matrix);
                            }
                            else{
                                knightMove(xDestination,yDestination,0,-1,possibleMoves,2,true,matrix);
                                knightMove(xDestination,yDestination,0,1,possibleMoves,2,true,matrix);
                            }
                        }
                        else{
                            knightMove(xDestination,yDestination,xMove,yMove,possibleMoves,2,false,matrix);
                        }
                    }
                    else if (matrix[xDestination][yDestination] == nullptr){
                        possibleMoves.emplace_back(xDestination, yDestination);
                    }
                    else if(matrix[xDestination][yDestination] != nullptr && matrix[xDestination][yDestination]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(xDestination, yDestination);
                    }
                }
            }
        }
    }
}

/**
 * @brief Calcule les mouvements possibles pour un roi
 * 
 * Le roi peut se déplacer d'une case dans toutes les directions.
 * Gère également le roque si le roi n'a pas encore bougé.
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Direction X
 * @param yMove Direction Y
 * @param possibleMoves Liste des mouvements possibles
 * @param matrix Matrice du plateau
 */
void Piece::kingMove(int xStart, int yStart, int xMove, int yMove,std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]) {
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;
    if (!isWallInMatrix5(xStart, yStart, xMove, yMove)) {
        if (!isWallInMatrix4(xStart, yStart, xMove, yMove)) {
            if((xStart==3 && yStart==3) && (xMove==1 && yMove==1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                }

                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                }
                
                
            }
            else if((xStart==3 && yStart==4) && (xMove==1 && yMove==-1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                }
                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                }
            }
            else if((xStart==4 && yStart==3) && (xMove==-1 && yMove==1)){
                if(matrix[8][8] != nullptr){
                    if(matrix[8][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 8);
                }
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                }
            }
            else if((xStart==8 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[3][4] != nullptr){
                    if(matrix[3][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 4);
                }
                if(matrix[4][3] != nullptr){
                    if(matrix[4][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 3);
                }
            }
            else if((xStart==8 && yStart==4) && (xMove==-1 && yMove==-1)){
                if(matrix[4][8] != nullptr){
                    if(matrix[4][8]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(4, 8);
                    }
                }
                else{
                    possibleMoves.emplace_back(4, 8);
                }
                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                }
            }
            else if((xStart==4 && yStart==8) && (xMove==-1 && yMove==-1)){
                if(matrix[8][4] != nullptr){
                    if(matrix[8][4]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(8, 4);
                    }
                }
                else{
                    possibleMoves.emplace_back(8, 4);
                }

                if(matrix[3][3] != nullptr){
                    if(matrix[3][3]->getSide()!=this->getSide()){
                        possibleMoves.emplace_back(3, 3);
                    }
                }
                else{
                    possibleMoves.emplace_back(3, 3);
                }
            }
            else{
                adjustCoordinates(xStart,yStart,xDestination,yDestination,xMove,yMove);
                if (!isOutOfBoard(xDestination, yDestination)) {
                    if (!isSquareExist(xDestination, yDestination)) {
                        if (matrix[xDestination][yDestination] == nullptr){
                            possibleMoves.emplace_back(xDestination, yDestination);
                        }
                        else if(matrix[xDestination][yDestination] != nullptr && matrix[xDestination][yDestination]->getSide()!=this->getSide()){
                            possibleMoves.emplace_back(xDestination, yDestination);
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Vérifie et ajoute les mouvements de roque possibles
 * 
 * Le roque est possible si :
 * - Le roi et la tour n'ont pas encore bougé
 * - Aucune pièce ne se trouve entre eux
 * - Le roi n'est pas en échec
 * 
 * @param xStart Position X du roi
 * @param yStart Position Y du roi
 * @param possibleMoves Liste des mouvements possibles
 * @param matrix Matrice du plateau
 */
void Piece::castling(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]){
    Piece* piece = matrix[xStart][yStart];
    if(piece->side==1){
        if(matrix[0][0]!=nullptr && !matrix[0][0]->getHasAlreadyMoved()){
            if(matrix[0][1]==nullptr && matrix[0][2]==nullptr && matrix[0][3]==nullptr){
                possibleMoves.emplace_back(0, 2);
            }
        }
        if(matrix[0][7]!=nullptr && !matrix[0][7]->getHasAlreadyMoved()){
            if(matrix[0][5]==nullptr && matrix[0][6]==nullptr){
                possibleMoves.emplace_back(0, 6);
            }
        }
    }
    else if(piece->side==2){
        if(matrix[7][0]!=nullptr && !matrix[7][0]->getHasAlreadyMoved()){
            if(matrix[7][1]==nullptr && matrix[7][2]==nullptr){
                possibleMoves.emplace_back(7, 1);
            }
        }
        if(matrix[7][11]!=nullptr && !matrix[7][11]->getHasAlreadyMoved()){
            if(matrix[7][8]==nullptr && matrix[7][9]==nullptr && matrix[7][10]==nullptr){
                possibleMoves.emplace_back(7, 9);
            }
        }
    }
    else{
        if(matrix[11][11]!=nullptr && !matrix[11][11]->getHasAlreadyMoved()){
            if(matrix[11][10]==nullptr && matrix[11][9]==nullptr){
                possibleMoves.emplace_back(11, 10);
            }
        }
        if(matrix[11][7]!=nullptr && !matrix[11][7]->getHasAlreadyMoved()){
            if(matrix[11][6]==nullptr && matrix[11][5]==nullptr && matrix[11][4]==nullptr){
                possibleMoves.emplace_back(11, 5);
            }
        }
    }
}

/**
 * @brief Calcule les mouvements possibles pour un pion
 * 
 * Le pion peut :
 * - Avancer d'une ou deux cases au premier coup
 * - Capturer en diagonale
 * - Se promouvoir en atteignant le bord
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param possibleMoves Liste des mouvements possibles
 * @param stop Compteur pour le double pas initial
 * @param matrix Matrice du plateau
 */
void Piece::pawnMove(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, int stop, Piece* matrix[12][12]) {
    if (stop == 2) return; 

    int xMove;
    int matrixStart = determineSubMatrix(xStart, yStart);

    if (side == 1 || (side == 2 && (matrixStart == 5 || matrixStart == 6)) || (side == 3 && (matrixStart == 3 || matrixStart == 4))) {
        xMove = 1;
    } else {
        xMove = -1;
    }

    int yMove = 0;
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;

    if (isWallInMatrix4(xStart, yStart, xMove, yMove)) return;

    if (stop == 0) {
        // Capture diagonale à droite
        captureByPawn(xStart, yStart, xMove, 1, possibleMoves, matrix);

        // Capture diagonale à gauche
        captureByPawn(xStart, yStart, xMove, -1, possibleMoves, matrix);

        // Gérer les cas particuliers de captures de la rosaces
        captureOnBoardCenter(xStart, yStart, possibleMoves, matrix);
    }

    // Coup en avant
    adjustCoordinates(xStart, yStart, xDestination, yDestination, xMove, yMove);
    if (!isOutOfBoard(xDestination, yDestination) && !isSquareExist(xDestination, yDestination)) {
        if (matrix[xDestination][yDestination] == nullptr) {
            possibleMoves.emplace_back(xDestination, yDestination);
            pawnMove(xDestination, yDestination, possibleMoves, stop + 1, matrix);
        }
    }
}

/**
 * @brief Calcule les mouvements possibles pour un pion après son premier coup
 * 
 * Version simplifiée de pawnMove qui ne permet que le déplacement d'une case
 * et les captures.
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param possibleMoves Liste des mouvements possibles
 * @param matrix Matrice du plateau
 */
void Piece::pawnMove2(int xStart, int yStart, std::vector<std::pair<int, int>>& possibleMoves, Piece* matrix[12][12]) {
    int xMove;
    int matrixStart = determineSubMatrix(xStart, yStart);

    if (side == 1 || (side == 2 && (matrixStart == 5 || matrixStart == 6)) || (side == 3 && (matrixStart == 3 || matrixStart == 4))) {
        xMove = 1;
    } else {
        xMove = -1;
    }

    int yMove = 0;
    int xDestination = xStart + xMove;
    int yDestination = yStart + yMove;

    if (isWallInMatrix4(xStart, yStart, xMove, yMove)) return;

    // Capture diagonale à droite
    captureByPawn(xStart, yStart, xMove, 1, possibleMoves, matrix);

    // Capture diagonale à gauche
    captureByPawn(xStart, yStart, xMove, -1, possibleMoves, matrix);

    // Gérer les cas particuliers de captures de la rosaces
    captureOnBoardCenter(xStart, yStart, possibleMoves, matrix);

    captureEnPassant(xStart, yStart, xMove, -1, possibleMoves, matrix);
    captureEnPassant(xStart, yStart, xMove, 1, possibleMoves, matrix);

    // Coup en avant
    adjustCoordinates(xStart, yStart, xDestination, yDestination, xMove, yMove);
    if (!isOutOfBoard(xDestination, yDestination) && !isSquareExist(xDestination, yDestination)) {
        if (matrix[xDestination][yDestination] == nullptr) {
            possibleMoves.emplace_back(xDestination, yDestination);
        }
    }
}

/**
 * @brief Vérifie et ajoute les captures en passant possibles
 * 
 * La prise en passant est possible si :
 * - Le pion adverse vient d'avancer de deux cases
 * - Le pion est adjacent au pion qui capture
 * 
 * @param x Position X du pion
 * @param y Position Y du pion
 * @param xMove Direction X
 * @param yMove Direction Y
 * @param moves Liste des mouvements possibles
 * @param matrix Matrice du plateau
 */
void Piece::captureEnPassant(int x, int y, int xMove, int yMove, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]){
    int xCapture = x + xMove;
    int yCapture = y + yMove;
    adjustCoordinates(x, y, xCapture, yCapture, xMove, yMove);
    if (isWallInMatrix5(x, y, xMove, yMove)) return;
    if (!isOutOfBoard(xCapture, yCapture)) {
        Piece* piece;
        if(xMove==1) {piece = matrix[xCapture-1][yCapture];}
        else{piece = matrix[xCapture+1][yCapture];}
        if (piece != nullptr && piece->getSide() != this->getSide() && piece->enPassant) {
            moves.emplace_back(xCapture, yCapture);
        }
    }
}

/**
 * @brief Vérifie et ajoute les captures diagonales possibles pour un pion
 * 
 * @param x Position X du pion
 * @param y Position Y du pion
 * @param xMove Direction X
 * @param yMove Direction Y
 * @param moves Liste des mouvements possibles
 * @param matrix Matrice du plateau
 */
void Piece::captureByPawn(int x, int y, int xMove, int yMove, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]) {
    int xCapture = x + xMove;
    int yCapture = y + yMove;
    adjustCoordinates(x, y, xCapture, yCapture, xMove, yMove);
    if (isWallInMatrix5(x, y, xMove, yMove)) return;
    if (!isOutOfBoard(xCapture, yCapture)) {
        Piece* piece = matrix[xCapture][yCapture];
        if (piece != nullptr && piece->getSide() != this->getSide()) {
            moves.emplace_back(xCapture, yCapture);
        }
    }
}

/**
 * @brief Gère les captures spéciales au centre du plateau
 * 
 * Le plateau Yalta a des règles spéciales pour les captures
 * au centre du plateau (rosace).
 * 
 * @param x Position X de la pièce
 * @param y Position Y de la pièce
 * @param moves Liste des mouvements possibles
 * @param matrix Matrice du plateau
 */
void Piece::captureOnBoardCenter(int x, int y, std::vector<std::pair<int, int>>& moves, Piece* matrix[12][12]) {
    std::vector<std::pair<int, int>> centerMoves;

    if (x == 3 && y == 3) {
        centerMoves = {{4, 8}, {8, 4}};
    } else if ((x == 3 && y == 4) || (x == 4 && y == 3)) {
        centerMoves = {{8, 8}};
    } else if (x == 8 && y == 8) {
        centerMoves = {{3, 4}, {4, 3}};
    } else if (x == 8 && y == 4) {
        centerMoves = {{4, 8}, {3, 3}};
        auto it = std::find(moves.begin(), moves.end(), std::make_pair(7, 8));// cas de bug particulier pour le pion 
        if (it != moves.end()) {
            moves.erase(it);
        } 
    } else if (x == 4 && y == 8) {
        centerMoves = {{8, 4}, {3, 3}};
        auto it = std::find(moves.begin(), moves.end(), std::make_pair(8, 7));// cas de bug particulier pour le pion 
        if (it != moves.end()) {
            moves.erase(it);
        } 
    }

    for (const auto& move : centerMoves) {
        Piece* piece = matrix[move.first][move.second];
        if (piece != nullptr && piece->getSide() != this->getSide()) {
            moves.emplace_back(move);
        }
    }
}
