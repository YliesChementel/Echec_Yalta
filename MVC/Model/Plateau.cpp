#include "Plateau.h"
#include <iostream>
#include <vector>

Plateau::Plateau(){
    InitMatrix();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour initialiser la matrix à null
void Plateau::InitMatrix(){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            matrix[i][j] = nullptr;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction qui place les pièces des joueurs dans la matrix
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour afficher la matrix dans le CLI
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour afficher les coupsPosibles dans le CLI
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction qui retourne les moves possibles à partir de coordonnées données
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


void Plateau::IsCastling(int xStart, int yStart,int xMove,int yMove, Piece* matrix[12][12]){
    if(matrix[xStart][yStart]->getSide()==1){
        if(xMove==0 && yMove==2){
            matrix[0][3] = matrix[0][0];
            matrix[0][0] = nullptr;
            matrix[0][3]->setXPosition(0);
            matrix[0][3]->setYPosition(3);
            castling=true;
        }
        else if(xMove==0 && yMove==6){
            matrix[0][5] = matrix[0][7];
            matrix[0][7] = nullptr;
            matrix[0][5]->setXPosition(0);
            matrix[0][5]->setYPosition(5);
            castling=true;
        }
    }
    else if(matrix[xStart][yStart]->getSide()==2){
        if(xMove==7 && yMove==1){
            matrix[7][2] = matrix[7][0];
            matrix[7][0] = nullptr;
            matrix[7][2]->setXPosition(7);
            matrix[7][2]->setYPosition(2);
            castling=true;
        }
        else if(xMove==7 && yMove==9){
            matrix[7][8] = matrix[7][11];
            matrix[7][11] = nullptr;
            matrix[7][8]->setXPosition(7);
            matrix[7][8]->setYPosition(8);
            castling=true;
        }
    }
    else{
        if(xMove==11 && yMove==10){
            matrix[11][9] = matrix[11][11];
            matrix[11][11] = nullptr;
            matrix[11][9]->setXPosition(11);
            matrix[11][9]->setYPosition(9);
            castling=true;
        }
        else if(xMove==11 && yMove==5){
            matrix[11][4] = matrix[11][7];
            matrix[11][7] = nullptr;
            matrix[11][4]->setXPosition(11);
            matrix[11][4]->setYPosition(4);
            castling=true;
        }
    }
}


void RemoveEnPassantMove(Piece** pieceList,int listSize){
    std::cout << "remove" <<std::endl;
    for (int i = 0; i < listSize; i++) {
        if (pieceList[i]->enPassant){
            pieceList[i]->enPassant=false;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction qui déplace une pièce via les coordonnées données et gère la capture d'une pièce, ainsi que la mise en echec et echec et mat
void Plateau::Move(int xStart, int yStart,int xMove,int yMove, Joueur* playerList, Piece* matrix[12][12]){
    int playerSide = matrix[xStart][yStart]->getSide();


    if(playerSide==1 && whiteEnPassant){
        RemoveEnPassantMove(playerList[0].getListPiece(),playerList[0].getSize());
        whiteEnPassant=false;
    }
    else if(playerSide==2 && redEnPassant){
        RemoveEnPassantMove(playerList[1].getListPiece(),playerList[1].getSize());
        redEnPassant=false;
    }
    else if(playerSide==3 && blackEnPassant){
        RemoveEnPassantMove(playerList[2].getListPiece(),playerList[2].getSize());
        blackEnPassant=false;
    }

    if (matrix[xMove][yMove] != nullptr) {
            std::cout << "Capture" << std::endl;
            if(matrix[xMove][yMove]->getType()=="r"){
                endOfGame=true;
                if(playerSide==1){winner="Blanc";}
                else if(playerSide==2){winner="Rouge";}
                else{winner="Noir";}
                std::cout << "Roi capturer, fin de partie" << std::endl;
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

    if(matrix[xStart][yStart]->getType()=="r" && !matrix[xStart][yStart]->getHasAlreadyMoved()){
        IsCastling(xStart, yStart, xMove, yMove, matrix);
    }
    else if(matrix[xStart][yStart]->getType()=="P"){
        if(!matrix[xStart][yStart]->getHasAlreadyMoved()){
            if(xMove==xStart-2 || xMove==xStart+2){
                matrix[xStart][yStart]->enPassant=true;
                if(playerSide==1){
                    whiteEnPassant=true;
                }
                else if(playerSide==2){
                    redEnPassant=true;
                }
                else if(playerSide==3){
                    blackEnPassant=true;
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
            isEnPassant=true;
        }
        
    }

    matrix[xMove][yMove] = matrix[xStart][yStart];
    matrix[xStart][yStart] = nullptr;


    matrix[xMove][yMove]->setXPosition(xMove);
    matrix[xMove][yMove]->setYPosition(yMove);

    if(!matrix[xMove][yMove]->getHasAlreadyMoved()){
        matrix[xMove][yMove]->setHasAlreadyMoved(true);
    }
    AffichageMatrice(matrix);
    std::cout << "Pièce déplacée de (" << xStart << "," << yStart << ") vers (" << xMove << "," << yMove << ")" << std::endl;
    if(!endOfGame){
        std::vector<std::string> sides = IsInCheck(playerList, matrix);
        if(!sides.empty()) {
            sidesInCheck=sides;
            std::cout << "Rois en échec : ";
            for (const auto& side : sides){
                std::cout << side << " ";
            }
            std::cout << std::endl;
            if (std::count(sides.begin(), sides.end(), "blanc") != 0) {
                if (IsCheckmate(0, "blanc", playerList)) {
                    std::cout << "blanc en echec et mat" << std::endl;
                    endOfGame=true;
                    if(playerSide==1){winner="Blanc";}
                    else if(playerSide==2){winner="Rouge";}
                    else{winner="Noir";}
                }
                else{
                    std::cout << "Ya encore une chance !" << std::endl;
                }
            }
            else if(std::count(sides.begin(), sides.end(), "rouge") != 0){
                if (IsCheckmate(1, "rouge", playerList)) {
                    std::cout << "rouge en echec et mat" << std::endl;
                    endOfGame=true;
                    if(playerSide==1){winner="Blanc";}
                    else if(playerSide==2){winner="Rouge";}
                    else{winner="Noir";}
                }
                else{
                    std::cout << "Ya encore une chance !" << std::endl;
                }
            }
            else{
                if (IsCheckmate(2, "noir", playerList)) {
                    std::cout << "noir en echec et mat" << std::endl;
                    endOfGame=true;
                    if(playerSide==1){winner="Blanc";}
                    else if(playerSide==2){winner="Rouge";}
                    else{winner="Noir";}
                }
                else{
                    std::cout << "Ya encore une chance !" << std::endl;
                }
            }
        }
        else{
            std::cout << "La partie continue" <<std::endl;
            this->sidesInCheck.clear();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction similaire à Move mais sera utiliser par la copy du plateau pour la détection des echec et mat
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour faire des copies des listes de pièces des joueurs, et prendre leurs tailles
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour faire une copy de la matrix via les méthode clone() des pièces
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour supprimer la copy de la matrix de pièce
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour vérifier si les pièces attaquantes mettent les autres joueurs en echec
std::string returnSidesInCheck(int indexAttacker, std::pair<int,int> king1, std::pair<int,int> king2, Joueur* playerList, Piece* matrix[12][12]) {
    std::vector<std::pair<int, int>> moves;
    Piece** attackerPieces = playerList[indexAttacker].getListPiece();
    bool checkKing1 = false; bool checkKing2 = false;

    for (int i = 0; i < playerList[indexAttacker].getSize(); ++i) {
        if (attackerPieces[i]->getType() != "r") {
            moves = attackerPieces[i]->possibleMove(attackerPieces[i]->getXPosition(), attackerPieces[i]->getYPosition(), matrix);
            for (const auto& move : moves) {
                if (move == king1){
                    checkKing1 = true;
                } 
                if (move == king2){
                    checkKing2 = true;
                } 
            }
        }
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour trouver la position du roi d’un player
std::pair<int, int> findKingPosition(Joueur& player) {
    Piece** pieces = player.getListPiece();
    for (int i = 0; i < player.getSize(); ++i) {
        if (pieces[i]->getType() == "r") {
            return { pieces[i]->getXPosition(), pieces[i]->getYPosition() };
        }
    }
    return { -1, -1 };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction pour vérifier si les rois sont en echec, si oui alors sa couleur est retourner
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

bool Plateau::PawnOnEdge(int xStart, int yStart,int xMove, Piece* matrix[12][12]){
    if(matrix[xStart][yStart]->getType()=="P"){
        if(xMove==0 || xMove==7 || xMove==11){
            return true;
        }
    }
    return false;
}

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


bool Plateau::Stalemate(int indexPlayer, const std::string& playerName, Joueur* playerList) {
    // vérif de si le roi est en echec
    std::vector<std::string> inCheck = IsInCheck(playerList, this->matrix);
    if (std::count(inCheck.begin(), inCheck.end(), playerName) != 0) {
        return false;
    }

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