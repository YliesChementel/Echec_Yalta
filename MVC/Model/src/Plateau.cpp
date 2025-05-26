/**
 * @file Plateau.cpp
 * @brief Implémentation de la classe Plateau qui gère le plateau de jeu d'échecs Yalta
 */

#include "include/Plateau.hpp"
#include <iostream>
#include <vector>
#include <climits>
#include <atomic>
#include <thread>

/**
 * @brief Constructeur de la classe Plateau
 * 
 * Initialise la matrice du plateau et les variables d'état du jeu :
 * - endOfGame : indique si la partie est terminée
 * - stalemate : indique si la partie est en pat
 * - castling : indique si un roque est en cours
 * - isEnPassant : indique si une prise en passant est possible
 * - whiteEnPassant, redEnPassant, blackEnPassant : indiquent si une prise en passant
 *   est possible pour chaque joueur
 */
Plateau::Plateau(){
    InitMatrix();
    endOfGame = false;
    stalemate = false;
    castling = false;
    isEnPassant = false;
    whiteEnPassant = false;
    redEnPassant = false;
    blackEnPassant = false;
}

/**
 * @brief Initialise la matrice du plateau
 * 
 * Place des pointeurs nuls dans toutes les cases de la matrice 12x12
 * pour indiquer qu'elles sont vides.
 */
void Plateau::InitMatrix(){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            matrix[i][j] = nullptr;
        }
    }
}

/**
 * @brief Place les pièces des joueurs sur le plateau
 * 
 * Place les pièces des trois joueurs (blanc, rouge, noir) dans leurs positions
 * initiales sur le plateau Yalta. Le plateau est divisé en trois zones :
 * - Joueur blanc : lignes 0-1
 * - Joueur rouge : lignes 6-7
 * - Joueur noir : lignes 10-11
 * 
 * @param whitePieces Liste des pièces du joueur blanc
 * @param redPieces Liste des pièces du joueur rouge
 * @param blackPieces Liste des pièces du joueur noir
 */
void Plateau::PlacePiece(Piece** whitePieces, Piece** redPieces, Piece** blackPieces) {
    int whiteIndex = 0, redIndex = 0, blackIndex = 0;

    // Placement des pièces du player 1
    for (int j = 0; j < 8; ++j) {
        whitePieces[whiteIndex]->setXPosition(1);
        whitePieces[whiteIndex]->setYPosition(j);
        matrix[1][j] = whitePieces[whiteIndex++];
    }
    for (int j = 0; j < 8; ++j) {
        whitePieces[whiteIndex]->setXPosition(0);
        whitePieces[whiteIndex]->setYPosition(j);
        matrix[0][j] = whitePieces[whiteIndex++];
    }

    // Placement des pièces du player 2
    for (int j = 0; j < 4; ++j) {
        redPieces[redIndex]->setXPosition(6);
        redPieces[redIndex]->setYPosition(j);
        matrix[6][j] = redPieces[redIndex++];
    }
    for (int j = 8; j < 12; ++j) {
        redPieces[redIndex]->setXPosition(6);
        redPieces[redIndex]->setYPosition(j);
        matrix[6][j] = redPieces[redIndex++];
    }
    for (int j = 0; j < 4; ++j) {
        redPieces[redIndex]->setXPosition(7);
        redPieces[redIndex]->setYPosition(j);
        matrix[7][j] = redPieces[redIndex++];
    }
    for (int j = 8; j < 12; ++j) {
        redPieces[redIndex]->setXPosition(7);
        redPieces[redIndex]->setYPosition(j);
        matrix[7][j] = redPieces[redIndex++];
    }

    // Placement des pièces du player 3
    for (int j = 4; j < 12; ++j) {
        if(j<8){
            blackPieces[blackIndex]->setXPosition(10);
            blackPieces[blackIndex]->setYPosition(11-j);
            matrix[10][11-j] = blackPieces[blackIndex++];
        }else{
            blackPieces[blackIndex]->setXPosition(10);
            blackPieces[blackIndex]->setYPosition(j);
            matrix[10][j] = blackPieces[blackIndex++];
        }
    }
    for (int j = 4; j < 12; ++j) {
        if(j<8){
            blackPieces[blackIndex]->setXPosition(11);
            blackPieces[blackIndex]->setYPosition(11-j);
            matrix[11][11-j] = blackPieces[blackIndex++];
        }else{
            blackPieces[blackIndex]->setXPosition(11);
            blackPieces[blackIndex]->setYPosition(j);
            matrix[11][j] = blackPieces[blackIndex++];
        }
    }

    // Les cases restantes sont vides 
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (matrix[i][j] == nullptr) {
                matrix[i][j] = nullptr;
            }
        }
    }
}

/**
 * @brief Affiche la matrice du plateau dans la console
 * 
 * Affiche une représentation textuelle du plateau où :
 * - Les pièces sont représentées par leur type
 * - Les cases vides sont représentées par 'X'
 * - Les cases non existantes du plateau Yalta sont représentées par des espaces
 * 
 * @param matrix Matrice du plateau à afficher
 */
void Plateau::AffichageMatrice(Piece* matrix[12][12]){
    std::cout << "   ";
    for (int j = 0; j < 12; ++j) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 12; ++i) {
        if(i<10){
            std::cout << i << "  ";
        }else{
            std::cout << i << " ";
        }
        
        for (int j = 0; j < 12; ++j) {
            if (matrix[i][j] != nullptr) {
                std::cout << matrix[i][j]->getType() << " ";
            } else {
                if ((i < 4 && j > 7) || (i >7 && j < 4)) {// Case non existante du plateau yalta
                    std::cout << "  ";
                }
                else if((i >3 && i < 8) && (j > 3 && j < 8)){// Case non existante du plateau yalta (milieu)
                    std::cout << "  ";
                }
                else{
                    std::cout << "X ";
                }
                
            }
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Affiche les coups possibles sur le plateau
 * 
 * Affiche une représentation textuelle du plateau où :
 * - Les pièces sont représentées par leur type
 * - Les cases vides sont représentées par 'X'
 * - Les coups possibles sont représentés par 'O'
 * - Les cases non existantes du plateau Yalta sont représentées par des espaces
 * 
 * @param possibleMoves Liste des coups possibles à afficher
 */
void Plateau::AfficherCoupsPossibles(std::vector<std::pair<int, int>> possibleMoves) {
    std::cout << "   ";
    for (int j = 0; j < 12; ++j) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 12; ++i) {
        if (i < 10) {
            std::cout << i << "  ";
        } else {
            std::cout << i << " ";
        }

        for (int j = 0; j < 12; ++j) {
            bool estCoupPossible = false;
            for (const auto& move : possibleMoves) {
                if (move.first == i && move.second == j) {
                    estCoupPossible = true;
                    break;
                }
            }

            if (matrix[i][j] != nullptr) {
                std::cout << matrix[i][j]->getType() << " ";
            } else if (estCoupPossible) {
                std::cout << "O ";
            } else {
                if ((i < 4 && j > 7) || (i > 7 && j < 4)) { // Case non existante du plateau yalta
                    std::cout << "  ";
                } else if ((i > 3 && i < 8) && (j > 3 && j < 8)) { // Case non existante du plateau yalta (milieu)
                    std::cout << "  ";
                } else {
                    std::cout << "X ";
                }
            }
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Retourne les mouvements possibles pour une pièce
 * 
 * Si la pièce est un roi, vérifie d'abord si les mouvements ne mettent pas
 * le roi en échec. Sinon, retourne directement les mouvements possibles
 * calculés par la pièce.
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @return Liste des mouvements possibles
 */
std::vector<std::pair<int, int>> Plateau::MovePiece(int xStart, int yStart) {
    Piece* piece = matrix[xStart][yStart];
    if(piece->getType()=="r"){
        int side = piece->getSide();
        std::string playerName;
        if(side==1){playerName="blanc";}
        else if(side==2){playerName="rouge";}
        else{playerName="noir";}
        return RemoveKingInCheckMoves(playerName, piece);
    }else{
        return piece->possibleMove(xStart,yStart,this->matrix);
    }
}

/**
 * @brief Vérifie si un roque est possible
 * 
 * Vérifie les conditions pour effectuer un roque :
 * - Le roi et la tour n'ont pas encore bougé
 * - Aucune pièce ne se trouve entre eux
 * - Le roi n'est pas en échec
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Direction X du mouvement
 * @param yMove Direction Y du mouvement
 * @param matrix Matrice du plateau
 */
void Plateau::IsCastling(int xStart, int yStart,int xMove,int yMove, Piece* matrix[12][12]){
    if(matrix[xStart][yStart]->getSide()==1){
        if(xMove==0 && yMove==2){
            matrix[0][3] = matrix[0][0];
            matrix[0][0] = nullptr;
            matrix[0][3]->setXPosition(0);
            matrix[0][3]->setYPosition(3);
            setCastling(true);
        }
        else if(xMove==0 && yMove==6){
            matrix[0][5] = matrix[0][7];
            matrix[0][7] = nullptr;
            matrix[0][5]->setXPosition(0);
            matrix[0][5]->setYPosition(5);
            setCastling(true);
        }
    }
    else if(matrix[xStart][yStart]->getSide()==2){
        if(xMove==7 && yMove==1){
            matrix[7][2] = matrix[7][0];
            matrix[7][0] = nullptr;
            matrix[7][2]->setXPosition(7);
            matrix[7][2]->setYPosition(2);
            setCastling(true);
        }
        else if(xMove==7 && yMove==9){
            matrix[7][8] = matrix[7][11];
            matrix[7][11] = nullptr;
            matrix[7][8]->setXPosition(7);
            matrix[7][8]->setYPosition(8);
            setCastling(true);
        }
    }
    else{
        if(xMove==11 && yMove==10){
            matrix[11][9] = matrix[11][11];
            matrix[11][11] = nullptr;
            matrix[11][9]->setXPosition(11);
            matrix[11][9]->setYPosition(9);
            setCastling(true);
        }
        else if(xMove==11 && yMove==5){
            matrix[11][4] = matrix[11][7];
            matrix[11][7] = nullptr;
            matrix[11][4]->setXPosition(11);
            matrix[11][4]->setYPosition(4);
            setCastling(true);
        }
    }
}

/**
 * @brief Réinitialise les drapeaux de prise en passant pour toutes les pièces d'un joueur
 * 
 * Cette fonction est appelée après chaque coup pour réinitialiser les drapeaux
 * de prise en passant. La prise en passant n'est possible que pendant un tour
 * après qu'un pion a avancé de deux cases.
 * 
 * La fonction parcourt toutes les pièces du joueur et réinitialise leur drapeau
 * enPassant à false. Cela permet de s'assurer que la prise en passant n'est
 * possible que pendant le tour suivant le mouvement du pion.
 * 
 * @param pieceList Liste des pièces du joueur dont il faut réinitialiser les drapeaux
 * @param listSize Nombre de pièces dans la liste
 */
void RemoveEnPassantMove(Piece** pieceList,int listSize){
    for (int i = 0; i < listSize; i++) {
        if (pieceList[i]->enPassant){
            pieceList[i]->enPassant=false;
        }
    }
}

/**
 * @brief Réinitialise les drapeaux de prise en passant
 * 
 * Réinitialise les drapeaux de prise en passant pour un joueur spécifique
 * après son coup.
 * 
 * @param side Numéro du joueur (1: blanc, 2: rouge, 3: noir)
 * @param playerList Liste des joueurs
 */
void Plateau::resetEnPassant(int side, Joueur* playerList) {
    if(side==1 && whiteEnPassant){
        RemoveEnPassantMove(playerList[0].getListPiece(),playerList[0].getSize());
        setWhiteEnPassant(false);
    }
    if(side==2 && redEnPassant){
        RemoveEnPassantMove(playerList[1].getListPiece(),playerList[1].getSize());
        setRedEnPassant(false);
    }
    if(side==3 && blackEnPassant){
        RemoveEnPassantMove(playerList[2].getListPiece(),playerList[2].getSize());
        setBlackEnPassant(false);
    }
}

/**
 * @brief Effectue une capture de pièce
 * 
 * Supprime la pièce capturée de la liste des pièces du joueur
 * et la retire du plateau.
 * 
 * @param xMove Position X de la pièce capturée
 * @param yMove Position Y de la pièce capturée
 * @param playerSide Numéro du joueur qui capture
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 */
void Plateau::Capture(int xMove, int yMove, int playerSide, Joueur* playerList, Piece* matrix[12][12]) {
    if (matrix[xMove][yMove] != nullptr) {
        
        if(matrix[xMove][yMove]->getType()=="r"){
            this->setEndOfGame(true);
            if(playerSide==1){this->setWinner("Blanc");}
            else if(playerSide==2){this->setWinner("Rouge");}
            else{this->setWinner("Noir");}
            //std::cout << "Roi capturer, fin de partie" << std::endl;
        }

        if(matrix[xMove][yMove]->getSide()==1){
            playerList[0].removePiece(matrix[xMove][yMove]);
        }
        else if(matrix[xMove][yMove]->getSide()==2){
            playerList[1].removePiece(matrix[xMove][yMove]);
        }
        else{
            playerList[2].removePiece(matrix[xMove][yMove]);
        }
    }
}

/**
 * @brief Gère les mouvements spéciaux
 * 
 * Gère les mouvements spéciaux comme :
 * - La promotion des pions
 * - La prise en passant
 * - Le roque
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Position X d'arrivée
 * @param yMove Position Y d'arrivée
 * @param playerSide Numéro du joueur
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 */
void Plateau::SpecialMoves(int xStart, int yStart, int xMove, int yMove, int playerSide, Joueur* playerList, Piece* matrix[12][12]) {
     if(matrix[xStart][yStart]->getType()=="r" && !matrix[xStart][yStart]->getHasAlreadyMoved()){
        IsCastling(xStart, yStart, xMove, yMove, matrix);
    }
    else if(matrix[xStart][yStart]->getType()=="P"){
        if(!matrix[xStart][yStart]->getHasAlreadyMoved()){
            if(xMove==xStart-2 || xMove==xStart+2){
                matrix[xStart][yStart]->enPassant=true;
                if(playerSide==1){
                    setWhiteEnPassant(true);
                }
                else if(playerSide==2){
                    setRedEnPassant(true);
                }
                else if(playerSide==3){
                    setBlackEnPassant(true);
                }
            }
        }
        else if(yMove!=yStart && matrix[xStart][yMove] != nullptr && matrix[xStart][yMove]->enPassant && xMove!=0 && yMove!=0 ){ // xstart pour la même ligne que le pion déplacé et ymove pour la colone d'à côté
            std::cout << "Capture" << std::endl;
            if(matrix[xStart][yMove]->getSide()==1){
                playerList[0].removePiece(matrix[xStart][yMove]);
            }
            else if(matrix[xStart][yMove]->getSide()==2){
                playerList[1].removePiece(matrix[xStart][yMove]);
            }
            else{
                playerList[2].removePiece(matrix[xStart][yMove]);
            }
            matrix[xStart][yMove]=nullptr;
            setEnPassant(true);
        }
    }
}

/**
 * @brief Effectue un mouvement de pièce
 * 
 * Déplace une pièce d'une position à une autre en gérant :
 * - La capture éventuelle
 * - Les mouvements spéciaux
 * - La mise à jour des positions
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Position X d'arrivée
 * @param yMove Position Y d'arrivée
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 */
void Plateau::Move(int xStart, int yStart,int xMove,int yMove, Joueur* playerList, Piece* matrix[12][12]){
    int playerSide = matrix[xStart][yStart]->getSide();
    resetEnPassant(playerSide, playerList);

    Capture(xMove, yMove, playerSide, playerList, matrix);

    SpecialMoves(xStart, yStart, xMove, yMove, playerSide, playerList, matrix);

    matrix[xMove][yMove] = matrix[xStart][yStart];
    matrix[xStart][yStart] = nullptr;

    matrix[xMove][yMove]->setXPosition(xMove);
    matrix[xMove][yMove]->setYPosition(yMove);

    if(!matrix[xMove][yMove]->getHasAlreadyMoved()){
        matrix[xMove][yMove]->setHasAlreadyMoved(true);
    }
    AffichageMatrice(matrix);

    std::cout << "Pièce déplacée de (" << xStart << "," << yStart << ") vers (" << xMove << "," << yMove << ")" << std::endl;

    if(!isEndOfGame()){
        std::vector<std::string> sides = IsInCheck(playerList, matrix);
        if(!sides.empty()) {
            setSidesInCheck(sides);
            std::cout << "Rois en échec : ";
            for (const auto& side : sides){ std::cout << side << " "<< std::endl; }

            std::vector<std::pair<std::string, int>> checkList = {
                {"blanc", 0}, {"rouge", 1}, {"noir", 2}
            };
            for (const auto& [sideStr, idx] : checkList) {
                if (std::count(sides.begin(), sides.end(), sideStr)) {
                    if (IsCheckmate(idx, sideStr, playerList)) {
                        std::cout << sideStr << " en échec et mat" << std::endl;
                        setEndOfGame(true);
                        if(playerSide==1){setWinner("Blanc");}
                        else if(playerSide==2){setWinner("Rouge");}
                        else{setWinner("Noir");}
                        return;
                    } else {
                        std::cout << "Ya encore une chance !" << std::endl;
                    }
                }
            }
        }
        else{
            if(Stalemate(0, "blanc", playerList) || Stalemate(1, "rouge", playerList) || Stalemate(2, "noir", playerList)){
                std::cout << "StaleMate" << std::endl;
                setEndOfGame(true);
                setStalemate(true);
            }else{
                std::cout << "La partie continue" <<std::endl;
                sidesInCheck.clear();
            }

           
        }
    }
}

/**
 * @brief Effectue un mouvement pour l'IA
 * 
 * Version simplifiée de Move() pour l'IA qui ne gère pas :
 * - L'affichage
 * - La détection d'échec et mat
 * - La détection de pat
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Position X d'arrivée
 * @param yMove Position Y d'arrivée
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 */
void Plateau::moveForAi(int xStart, int yStart,int xMove,int yMove, Joueur* playerList, Piece* matrix[12][12]){
    int playerSide = matrix[xStart][yStart]->getSide();
    //this->resetEnPassant(playerSide, playerList);

    this->Capture(xMove, yMove, playerSide, playerList, matrix);

    //SpecialMoves(xStart, yStart, xMove, yMove, playerSide, playerList, matrix);

    matrix[xMove][yMove] = matrix[xStart][yStart];
    matrix[xStart][yStart] = nullptr;

    matrix[xMove][yMove]->setXPosition(xMove);
    matrix[xMove][yMove]->setYPosition(yMove);
    if(!matrix[xMove][yMove]->getHasAlreadyMoved()){
        matrix[xMove][yMove]->setHasAlreadyMoved(true);
    }
}

/**
 * @brief Effectue un mouvement pour un clone du plateau
 * 
 * Version simplifiée de Move() pour les clones du plateau utilisés
 * dans l'algorithme minmax.
 * 
 * @param xStart Position X de départ
 * @param yStart Position Y de départ
 * @param xMove Position X d'arrivée
 * @param yMove Position Y d'arrivée
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 */
void moveForClone(int xStart, int yStart,int xMove,int yMove, Joueur* playerList, Piece* matrix[12][12]){
    if (matrix[xMove][yMove] != nullptr) {
        if(matrix[xMove][yMove]->getSide()==1){
            playerList[0].removePiece(matrix[xMove][yMove]);
        }
        else if(matrix[xMove][yMove]->getSide()==2){
            playerList[1].removePiece(matrix[xMove][yMove]);
        }
        else{
            playerList[2].removePiece(matrix[xMove][yMove]);
        }
    }

    matrix[xMove][yMove] = matrix[xStart][yStart];
    matrix[xStart][yStart] = nullptr;

    matrix[xMove][yMove]->setXPosition(xMove);
    matrix[xMove][yMove]->setYPosition(yMove);
}

/**
 * @brief Clone la liste des pièces d'un joueur
 * 
 * Crée une copie profonde de la liste des pièces d'un joueur
 * pour l'utiliser dans l'algorithme minmax.
 * 
 * @param copy Matrice source
 * @param side Numéro du joueur
 * @param size Taille de la liste des pièces
 * @return Liste des pièces clonées
 */
Piece** clonePieceListe(Piece* copy[12][12], int side, int& size) {
    int count = 0;
    for (int i = 0; i < 12; ++i){
        for (int j = 0; j < 12; ++j){
            if (copy[i][j] && copy[i][j]->getSide() == side){
                count++;
            }
        }
    }

    Piece** list = new Piece*[count];
    int index = 0;
    for (int i = 0; i < 12; ++i){
        for (int j = 0; j < 12; ++j){
            if (copy[i][j] && copy[i][j]->getSide() == side){
                list[index] = copy[i][j];
                list[index]->setXPosition(i);
                list[index]->setYPosition(j);
                index++;
            }
        }
    }

    size = count;
    return list;
}

/**
 * @brief Clone la matrice du plateau
 * 
 * Crée une copie profonde de la matrice du plateau
 * pour l'utiliser dans l'algorithme minmax.
 * 
 * @param copy Matrice destination
 * @param original Matrice source
 */
void cloneMatrix(Piece* copy[12][12], Piece* original[12][12]) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (original[i][j]!=nullptr) {
                copy[i][j] = original[i][j]->clone();
            } else {
                copy[i][j] = nullptr;
            }
        }
    }
}

/**
 * @brief Libère la mémoire de la matrice
 * 
 * Supprime toutes les pièces de la matrice et libère leur mémoire.
 * 
 * @param matrix Matrice à libérer
 */
void freeMatrix(Piece* (*matrix)[12]) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (matrix[i][j] != nullptr) {
                delete matrix[i][j];  //  supprime chaque pièce allouée dynamiquement
                matrix[i][j] = nullptr;
            }
        }
    }
}

/**
 * @brief Retourne les joueurs en échec
 * 
 * Détermine quels joueurs sont en échec après un mouvement
 * en vérifiant si leurs rois peuvent être capturés.
 * 
 * @param indexAttacker Index du joueur qui attaque
 * @param king1 Position du roi du joueur 1
 * @param king2 Position du roi du joueur 2
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 * @return Chaîne contenant les numéros des joueurs en échec
 */
std::string returnSidesInCheck(int indexAttacker, std::pair<int,int> king1, std::pair<int,int> king2, Joueur* playerList, Piece* matrix[12][12]) {
    std::vector<std::pair<int, int>> moves;
    Piece** attackerPieces = playerList[indexAttacker].getListPiece();
    bool checkKing1 = false; bool checkKing2 = false;

    for (int i = 0; i < playerList[indexAttacker].getSize(); ++i) {
        //if (attackerPieces[i]->getType() != "r") {
            moves = attackerPieces[i]->possibleMove(attackerPieces[i]->getXPosition(), attackerPieces[i]->getYPosition(), matrix);
            for (const auto& move : moves) {
                if (move == king1){
                    checkKing1 = true;
                } 
                if (move == king2){
                    checkKing2 = true;
                } 
            }
        //}
    }

    if (checkKing1 && checkKing2){
        return "deux";
    }
    if (checkKing1){
        return "king1";
    } 
    if (checkKing2){
        return "king2";
    } 
    return "aucun";
}

/**
 * @brief Trouve la position du roi d'un joueur
 * 
 * @param player Joueur dont on cherche le roi
 * @return Position (x,y) du roi
 */
std::pair<int, int> findKingPosition(Joueur& player) {
    Piece** pieces = player.getListPiece();
    for (int i = 0; i < player.getSize(); ++i) {
        if (pieces[i]->getType() == "r") {
            return { pieces[i]->getXPosition(), pieces[i]->getYPosition() };
        }
    }
    return { -1, -1 };
}

/**
 * @brief Vérifier si les rois sont en echec, si oui alors sa couleur est retourner
 * 
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 * @return Liste des joueurs en échec
 */
std::vector<std::string> Plateau::IsInCheck(Joueur* playerList, Piece* matrix[12][12]) {
    std::pair<int, int> whiteKing, redKing, blackKing;

    whiteKing = findKingPosition(playerList[0]);
    redKing = findKingPosition(playerList[1]);
    blackKing = findKingPosition(playerList[2]);

    std::vector<std::string> sidesCheck;

    std::string byWhite = returnSidesInCheck(0, redKing, blackKing, playerList, matrix);
    if (byWhite == "king1" || byWhite == "deux"){
        sidesCheck.push_back("rouge");
    }
    if (byWhite == "king2" || byWhite == "deux"){
        sidesCheck.push_back("noir");
    }

    std::string byRed = returnSidesInCheck(1, whiteKing, blackKing, playerList, matrix);
    if (byRed == "king1" || byRed == "deux"){
        sidesCheck.push_back("blanc");
    }
    if (byRed == "king2" || byRed == "deux"){
        if (std::count(sidesCheck.begin(), sidesCheck.end(), "noir") == 0){
            sidesCheck.push_back("noir");
        }
    }

    std::string byBlack = returnSidesInCheck(2, whiteKing, redKing, playerList, matrix);
    if (byBlack == "king1" || byBlack == "deux"){
        if (std::count(sidesCheck.begin(), sidesCheck.end(), "blanc") == 0){
            sidesCheck.push_back("blanc");
        }
    }
    if (byBlack == "king2" || byBlack == "deux"){
        if (std::count(sidesCheck.begin(), sidesCheck.end(), "rouge") == 0){
            sidesCheck.push_back("rouge");
        }
    }

    if(std::count(sidesCheck.begin(), sidesCheck.end(), "blanc")== 0){
        matrix[whiteKing.first][whiteKing.second]->inCheck=false;
    }
    else{
        matrix[whiteKing.first][whiteKing.second]->inCheck=true;
    }

    if(std::count(sidesCheck.begin(), sidesCheck.end(), "rouge")== 0){
        matrix[redKing.first][redKing.second]->inCheck=false;
    }
    else{
        matrix[redKing.first][redKing.second]->inCheck=true;
    }

    if(std::count(sidesCheck.begin(), sidesCheck.end(), "noir")== 0){
        matrix[blackKing.first][blackKing.second]->inCheck=false;
    }
    else{
        matrix[blackKing.first][blackKing.second]->inCheck=true;
    }

    return sidesCheck;
}

/**
 * @brief Vérifie si un joueur est en échec et mat
 * 
 * Un joueur est en échec et mat si :
 * - Son roi est en échec
 * - Aucun mouvement ne peut le sortir de l'échec
 * 
 * @param indexPlayer Index du joueur à vérifier
 * @param playerName Nom du joueur
 * @param playerList Liste des joueurs
 * @return true si le joueur est en échec et mat, false sinon
 */
bool Plateau::IsCheckmate(int indexPlayer, std::string playerName, Joueur* playerList) {

    Piece** listPieces = playerList[indexPlayer].getListPiece();
    int size = playerList[indexPlayer].getSize();

    for (int i = 0; i < size; ++i) {
        Piece* piece = listPieces[i];
        std::vector<std::pair<int, int>> possibleMoves = piece->possibleMove(piece->getXPosition(), piece->getYPosition(), this->matrix);

        for (const auto& move : possibleMoves) {
            Piece* copy[12][12];
            cloneMatrix(copy, this->matrix);

            int whiteCopySize, redCopySize ,blackCopySize;
            Piece** whiteListCopy = clonePieceListe(copy, 1, whiteCopySize);
            Piece** redListCopy = clonePieceListe(copy, 2, redCopySize);
            Piece** blackListCopy  = clonePieceListe(copy, 3, blackCopySize);

            Joueur* playerListCopy = new Joueur[3];
            playerListCopy[0].setListPiece(whiteListCopy); playerListCopy[0].setSize(whiteCopySize);
            playerListCopy[1].setListPiece(redListCopy); playerListCopy[1].setSize(redCopySize);
            playerListCopy[2].setListPiece(blackListCopy);  playerListCopy[2].setSize(blackCopySize);

            moveForClone(piece->getXPosition(), piece->getYPosition(), move.first, move.second, playerListCopy, copy);

            std::vector<std::string> sidesInCheckVerif = IsInCheck(playerListCopy, copy);

            if (std::count(sidesInCheckVerif.begin(), sidesInCheckVerif.end(), playerName) == 0) {
                freeMatrix(copy);
                return false;
            }

            freeMatrix(copy);
        }
    }

    std::cout << "Les " << playerName << "s sont en ÉCHEC ET MAT !" << std::endl;
    return true;
}

/**
 * @brief Vérifie si un pion est sur le bord du plateau
 * 
 * @param xStart Position X du pion
 * @param yStart Position Y du pion
 * @param xMove Position X d'arrivée
 * @param matrix Matrice du plateau
 * @return true si le pion est sur le bord, false sinon
 */
bool Plateau::PawnOnEdge(int xStart, int yStart,int xMove, Piece* matrix[12][12]){
    if(matrix[xStart][yStart]->getType()=="P"){
        if(xMove==0 || xMove==7 || xMove==11){
            return true;
        }
    }
    return false;
}

/**
 * @brief Gère la promotion d'un pion
 * 
 * Remplace un pion qui atteint le bord du plateau par une nouvelle pièce
 * choisie par le joueur (dame, tour, fou ou cavalier).
 * 
 * @param xStart Position X du pion
 * @param yStart Position Y du pion
 * @param promotionChoice Type de pièce choisie pour la promotion
 * @param playerList Liste des joueurs
 * @param matrix Matrice du plateau
 */
void Plateau::PawnPromotion(int xStart, int yStart, int promotionChoice, Joueur* playerList,Piece* matrix[12][12]){
    Piece* piecePromotion;
    int pieceSide = matrix[xStart][yStart]->getSide();
    if(promotionChoice==0){
        piecePromotion = new Reine(pieceSide);
    }
    else if(promotionChoice==1){
        piecePromotion = new Fou(pieceSide);
    }
    else if(promotionChoice==2){
        piecePromotion = new Cavalier(pieceSide);
    }
    else if(promotionChoice==3){
        piecePromotion = new Tour(pieceSide);
    }

    if(pieceSide==1){
        playerList[0].replacePiece(matrix[xStart][yStart],piecePromotion);
    }
    else if(pieceSide==2){
        playerList[1].replacePiece(matrix[xStart][yStart],piecePromotion);
    }
    else{
        playerList[2].replacePiece(matrix[xStart][yStart],piecePromotion);
    }
    matrix[xStart][yStart]=piecePromotion;
}

/**
 * @brief Retire les mouvements qui mettent le roi en échec
 * 
 * Filtre la liste des mouvements possibles pour ne garder que ceux
 * qui ne mettent pas le roi en échec.
 * 
 * @param playerName Nom du joueur
 * @param piece Pièce qui se déplace
 * @return Liste des mouvements valides
 */
std::vector<std::pair<int, int>> Plateau::RemoveKingInCheckMoves(std::string playerName, Piece* piece) {
    std::vector<std::pair<int, int>> possibleMoves = piece->possibleMove(piece->getXPosition(), piece->getYPosition(), this->matrix);
    std::vector<std::pair<int, int>> validMoves;

    for (const auto& move : possibleMoves) {
        Piece* copy[12][12];
        cloneMatrix(copy, this->matrix);

        int whiteCopySize, redCopySize ,blackCopySize;
        Piece** whiteListCopy = clonePieceListe(copy, 1, whiteCopySize);
        Piece** redListCopy = clonePieceListe(copy, 2, redCopySize);
        Piece** blackListCopy  = clonePieceListe(copy, 3, blackCopySize);

        Joueur* playerListCopy = new Joueur[3];
        playerListCopy[0].setListPiece(whiteListCopy); playerListCopy[0].setSize(whiteCopySize);
        playerListCopy[1].setListPiece(redListCopy); playerListCopy[1].setSize(redCopySize);
        playerListCopy[2].setListPiece(blackListCopy);  playerListCopy[2].setSize(blackCopySize);

        moveForClone(piece->getXPosition(), piece->getYPosition(), move.first, move.second, playerListCopy, copy);

        std::vector<std::string> sidesInCheckVerif = IsInCheck(playerListCopy, copy);

        if (std::count(sidesInCheckVerif.begin(), sidesInCheckVerif.end(), playerName) == 0) {
            validMoves.push_back(move);
        }

        freeMatrix(copy);
    }

    return validMoves;
}

/**
 * @brief Vérifie si un joueur est en pat
 * 
 * Un joueur est en pat si :
 * - Son roi n'est pas en échec
 * - Aucun mouvement n'est possible
 * 
 * @param indexPlayer Index du joueur à vérifier
 * @param playerName Nom du joueur
 * @param playerList Liste des joueurs
 * @return true si le joueur est en pat, false sinon
 */
bool Plateau::Stalemate(int indexPlayer, const std::string& playerName, Joueur* playerList) {
    // vérif de si le roi est en echec
    //std::vector<std::string> inCheck = IsInCheck(playerList, this->matrix);
    //if (std::count(inCheck.begin(), inCheck.end(), playerName) != 0) {
        //return false;
    //}

    //vérif des moves légaux des autres pièces
    Piece** listPieces = playerList[indexPlayer].getListPiece();
    int size = playerList[indexPlayer].getSize();
    for (int i = 0; i < size; ++i) {
        Piece* piece = listPieces[i];
        std::vector<std::pair<int,int>> legalMoves;
        if (piece->getType() == "r") {
            legalMoves = RemoveKingInCheckMoves(playerName, piece);
        } else {
            std::vector<std::pair<int,int>> moves = piece->possibleMove(piece->getXPosition(), piece->getYPosition(), this->matrix);
            legalMoves.insert(legalMoves.end(), moves.begin(), moves.end());
        }
        if (!legalMoves.empty()) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Évalue la position d'un joueur
 * 
 * Calcule un score pour la position d'un joueur en fonction de :
 * - La valeur matérielle des pièces
 * - La position des pièces sur le plateau
 * - La sécurité du roi
 * 
 * @param players Liste des joueurs
 * @param sideAi Numéro du joueur IA
 * @return Score de la position
 */
int Plateau::evaluation(Joueur* players, int sideAi) {
  int evalValue = 0;
  int valuePiece = 0;
  for(int side=0; side<3; ++side){
    int signe = (side == sideAi ? +1 : -1);
    Piece** listPiece = players[side].getListPiece();
    for(int i = 0; i < players[side].getSize(); ++i){
        Piece* piece = listPiece[i];
        int x = piece->getXPosition();
        int y = piece->getYPosition();
        
        if(piece->getType() == "P"){
            valuePiece = 10;

            if(piece->getSide() == 1) {
                valuePiece += x; 
            }
            else if(piece->getSide() == 2) {
                if(x>6){
                    valuePiece += 11-x; 
                }
                else{
                    valuePiece += x; 
                }
            }
            else if(piece->getSide() == 3) {
                if(x>3 && x<8){
                     valuePiece += x;
                }
                else{
                   valuePiece += 11-x; 
                } 
            }

            if(piece->getHasAlreadyMoved()){
                valuePiece += 2;
            }
        }
        else if(piece->getType() == "C"){
            valuePiece = 30;
            if(piece->getHasAlreadyMoved()){
                valuePiece += 3;
            }
        }
        else if(piece->getType() == "T"){
            valuePiece = 40;
            if(!piece->getHasAlreadyMoved()){
                valuePiece += 5;
            }
            
        }
        else if(piece->getType() == "F"){
            valuePiece = 30;
        }
        else if(piece->getType() == "R"){
            valuePiece = 90;
        }
        else if(piece->getType() == "r"){
            if(!piece->getHasAlreadyMoved()){
                valuePiece += 20;
            }
            valuePiece += 10000;
        }

        if(((x > 2 && x < 5) || x == 8) && piece->getType() != "r") { // Bonus pour contrôle du centre
            valuePiece += 3;
        }

        evalValue += signe * valuePiece;        
        valuePiece = 0;
    }
  }
  return evalValue;
}

/**
 * @brief Implémente l'algorithme minmax avec élagage alpha-beta
 * 
 * Recherche le meilleur coup possible pour l'IA en explorant
 * l'arbre des coups possibles jusqu'à une profondeur donnée.
 * 
 * @param plateau Plateau de jeu
 * @param sideMove Joueur qui doit jouer
 * @param sideAi Numéro du joueur IA
 * @param depth Profondeur restante de recherche
 * @param OrignialDepth Profondeur initiale de recherche
 * @param alpha Valeur alpha pour l'élagage
 * @param beta Valeur beta pour l'élagage
 * @param players Liste des joueurs
 * @param stopFlag Drapeau pour arrêter la recherche
 * @return Meilleur score trouvé
 */
int Plateau::minmax(Plateau plateau, int sideMove, int sideAi, int depth, int OrignialDepth, int alpha, int beta, Joueur* players, std::atomic<bool>& stopFlag){
    if(depth==0 || plateau.endOfGame){
        return this->evaluation(players, sideAi);
    }

    if(sideMove==sideAi){
        int maxEval = INT_MIN;
        if(players[sideMove].getSize() > 0){
            for(int j = 0; j < players[sideMove].getSize(); ++j){
                if (stopFlag) return 0;
                Piece* piece = players[sideMove].getListPiece()[j];
                std::vector<std::pair<int,int>> moves = piece->possibleMove(piece->getXPosition(), piece->getYPosition(), plateau.matrix);
                for(const auto& move : moves){
                    if (stopFlag) return 0;
                    Plateau* newPlateau = plateau.clone();
                    newPlateau->moveForAi(piece->getXPosition(), piece->getYPosition(), move.first, move.second, players, newPlateau->matrix);
                    int nextSide;
                    if(sideMove==0){
                        nextSide = 1;
                    }
                    else if(sideMove==1){
                        nextSide = 2;
                    }
                    else{
                        nextSide = 0;
                    }
                    int whiteCopySize, redCopySize, blackCopySize;
                    Piece** whiteListCopy = clonePieceListe(newPlateau->matrix, 1, whiteCopySize);
                    Piece** redListCopy = clonePieceListe(newPlateau->matrix, 2, redCopySize);
                    Piece** blackListCopy = clonePieceListe(newPlateau->matrix, 3, blackCopySize);

                    Joueur* playerListCopy = new Joueur[3];
                    playerListCopy[0].setListPiece(whiteListCopy); playerListCopy[0].setSize(whiteCopySize);
                    playerListCopy[1].setListPiece(redListCopy); playerListCopy[1].setSize(redCopySize);
                    playerListCopy[2].setListPiece(blackListCopy); playerListCopy[2].setSize(blackCopySize);

                    int eval = minmax(*newPlateau, nextSide, sideAi, depth-1, OrignialDepth, alpha, beta, playerListCopy, stopFlag);
                    maxEval = std::max(maxEval, eval);
                    if(maxEval == eval && depth == OrignialDepth){
                        bestMoveStart = {piece->getXPosition(), piece->getYPosition()};
                        bestMoveEnd = move;
                    }
                    alpha = std::max(alpha, eval);
                    
                    freeMatrix(newPlateau->matrix);
                    delete newPlateau;
                    
                    if(beta <= alpha){
                        break;
                    }
                }
            }
        }
        return maxEval;
    }
    else{
        int minEval = INT_MAX;
        for(int i = 0; i < 3; ++i){
            if(players[i].getSize() > 0 && i != sideAi){
                for(int j = 0; j < players[i].getSize(); ++j){
                    if (stopFlag) return 0;
                    Piece* piece = players[i].getListPiece()[j];
                    std::vector<std::pair<int,int>> moves = piece->possibleMove(piece->getXPosition(), piece->getYPosition(), plateau.matrix);
                    for(const auto& move : moves){
                        if (stopFlag) return 0;
                        Plateau* newPlateau = plateau.clone();
                        newPlateau->moveForAi(piece->getXPosition(), piece->getYPosition(), move.first, move.second, players, newPlateau->matrix);

                        int nextSide;
                        if(sideMove==0){
                            nextSide = 1;
                        }
                        else if(sideMove==1){
                            nextSide = 2;
                        }
                        else{
                            nextSide = 0;
                        }
                        int whiteCopySize, redCopySize, blackCopySize;
                        Piece** whiteListCopy = clonePieceListe(newPlateau->matrix, 1, whiteCopySize);
                        Piece** redListCopy = clonePieceListe(newPlateau->matrix, 2, redCopySize);
                        Piece** blackListCopy = clonePieceListe(newPlateau->matrix, 3, blackCopySize);

                        Joueur* playerListCopy = new Joueur[3];
                        playerListCopy[0].setListPiece(whiteListCopy); playerListCopy[0].setSize(whiteCopySize);
                        playerListCopy[1].setListPiece(redListCopy); playerListCopy[1].setSize(redCopySize);
                        playerListCopy[2].setListPiece(blackListCopy); playerListCopy[2].setSize(blackCopySize);

                        int eval = minmax(*newPlateau, nextSide, sideAi, depth-1, OrignialDepth, alpha, beta, playerListCopy, stopFlag);
                        minEval = std::min(minEval, eval);
                        beta = std::min(beta, eval);
                        
                        freeMatrix(newPlateau->matrix);
                        delete newPlateau;

                        
                        if(beta <= alpha){
                            break;
                        }
                    }
                }
            }
        }
        return minEval;
    }   
}

/**
 * @brief Crée une copie profonde du plateau
 * 
 * Clone le plateau en copiant :
 * - La matrice des pièces
 * - L'état du jeu (échec, fin de partie, etc.)
 * - Les drapeaux de prise en passant
 * 
 * @return Pointeur vers le nouveau plateau
 */
Plateau* Plateau::clone() {
    Plateau* newPlateau = new Plateau();
    cloneMatrix(newPlateau->matrix, this->matrix);

    newPlateau->setSidesInCheck(sidesInCheck);
    newPlateau->setWinner(winner);
    newPlateau->setEndOfGame(endOfGame);
    newPlateau->setCastling(castling);
    newPlateau->setEnPassant(isEnPassant);
    newPlateau->setWhiteEnPassant(whiteEnPassant);
    newPlateau->setRedEnPassant(redEnPassant);
    newPlateau->setBlackEnPassant(blackEnPassant);
    
    return newPlateau;
}