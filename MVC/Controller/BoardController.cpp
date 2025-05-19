#include "BoardController.h"
#include <iostream>

BoardController::BoardController(MakeBoard& makeBoard, DrawBoard& drawBoard, sf::RenderWindow& window,Jeu& jeu)
    : makeBoard(makeBoard), drawBoard(drawBoard), window(window),jeu(jeu) , isDragging(false), selectedPieceIndex(-1) {handleSound(); initListePieces();}

void BoardController::run() {



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if(!jeu.getBoard().endOfGame){
                    if(promotion){
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        int choix = PromotionChoix(mousePos);
                        if (choix != -1) {
                            jeu.getBoard().PawnPromotion(coupEnAttentePromotion.first,coupEnAttentePromotion.second, choix, jeu.getPlayerList(), jeu.getBoard().matrix);
                            
                            std::vector<PieceImage>& piecesCamp = *listePieces[couleurIndex];
                            piecesCamp[selectedPieceIndex].getSprite().setTexture(drawBoard.getPromotionTexture(choix,couleurIndex), true);
                            promotion = false; 
                        }
                    }else{
                        handleMousePressed(event);
                    }
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                handleMouseMoved(event);
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                handleMouseReleased(event);
            }
        }
        
        // Rendu de la scène via la vue
        drawBoard.clear();
        drawBoard.drawHexagons(makeBoard.getHexagon(), makeBoard.getHexagon2());
        drawBoard.drawLines(makeBoard.getLines());

        drawBoard.drawText(makeBoard.getCoordText());
        drawBoard.drawTextGame(makeBoard.getTextGame());
        drawBoard.drawTextGame(makeBoard.getTextEchec());

        drawBoard.drawBoard({makeBoard.getMatrice1(),makeBoard.getMatrice2(),makeBoard.getMatrice3(),makeBoard.getMatrice4(),makeBoard.getMatrice5(),makeBoard.getMatrice6()});
        drawBoard.drawPieces(makeBoard.getWhitePieces(), makeBoard.getRedPieces(), makeBoard.getBlackPieces());
        
        if(promotion){
            drawBoard.drawChoice(couleurIndex);
        }
        
        drawBoard.display();

        if(!jeu.getBoard().endOfGame){
            aiMove();
        }
        
        
    }
}

void BoardController::initListePieces() {
    listePieces = {
        &makeBoard.getWhitePieces(),
        &makeBoard.getRedPieces(),
        &makeBoard.getBlackPieces()
    };
}

bool BoardController::TrouverPieceSelectioner(std::vector<PieceImage>& liste, int listeIndex, sf::Vector2f mousePos) {
    for (int i = 0; i < liste.size(); ++i) {
        if (liste[i].getSprite().getGlobalBounds().contains(mousePos)) {
            couleurIndex = listeIndex;
            selectedPieceIndex = i;
            offsetImage = mousePos - liste[i].getSprite().getPosition();
            handleCoup(liste[i].getTilePositions());
            return true;
        }
    }
    return false;
}

void BoardController::TrouverPieceCapture(std::vector<int> positions){
    for (int j = 0; j < listePieces.size(); ++j) {
        if (j == couleurIndex) continue; // Ignore les pièces de la même couleur
        std::vector<PieceImage>& piecesAdverses = *listePieces[j];
        for (int k = 0; k < piecesAdverses.size(); ++k) {
            std::vector<int> pos = piecesAdverses[k].getTilePositions();
            if (pos[0] == positions[0] && pos[1] == positions[1]) {
                piecesAdverses.erase(piecesAdverses.begin() + k); // Supprimer la pièce adverse
                if(k<rookRight){
                    rookRight--;
                }
                break;
            }
        }
    }
}


bool BoardController::PlacerPieceDansMatrice(const std::vector<sf::ConvexShape>& matrix, int indexMatrice, const sf::Vector2f& mousePos) {
    if (makeBoard.PieceDansMatrice(mousePos, matrix)) {
        for (int i = 0; i < matrix.size(); ++i) {
            const sf::ConvexShape& losange = matrix[i];
            if (makeBoard.PieceDansLosange(losange, mousePos)) {
                std::vector<int> positions = {i, indexMatrice};
                if (handleCoupJouer((*listePieces[couleurIndex])[selectedPieceIndex].getTilePositions(), positions)) {
                    TrouverPieceCapture(positions);
                    makeBoard.PlacementPiece(selectedPieceIndex, losange, (*listePieces[couleurIndex]), indexMatrice, i);
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

void BoardController::RemettreCouleurDefautCases(){
    for(const auto& tile : tilesToChangeColor) {
        drawBoard.changeColorTileBright(makeBoard.getMatrice(tile[1])[tile[0]]);
    }
    tilesToChangeColor.clear();
}

void BoardController::handleMousePressed(const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (TrouverPieceSelectioner(*listePieces[0], 0, mousePos)) {// j'utilise la déréférences
        isDragging = true;
    }
    if (TrouverPieceSelectioner(*listePieces[1], 1, mousePos)) {
        isDragging = true;
    }
    if (TrouverPieceSelectioner(*listePieces[2], 2, mousePos)) {
        isDragging = true;
    }
/*
    if (TrouverPieceSelectioner(*listePieces[tour], tour, mousePos)) {// j'utilise la déréférences
            isDragging = true;
    }*/
}

void BoardController::handleMouseMoved(const sf::Event& event) {
    if (!isDragging) return;
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    (*listePieces[couleurIndex])[selectedPieceIndex].getSprite().setPosition(mousePos - offsetImage); // Déplacement des pièces en fonction de l'index de la pièce et de l'index de la couleur
}

void BoardController::handleMouseReleased(const sf::Event& event) {
    if (!isDragging)
        return;

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Vérifier si la pièce est dans l'une des 6 matrices
    if (PlacerPieceDansMatrice(makeBoard.getMatrice(1),1,mousePos) || PlacerPieceDansMatrice(makeBoard.getMatrice(2),2,mousePos) || PlacerPieceDansMatrice(makeBoard.getMatrice(3),3,mousePos) ||
        PlacerPieceDansMatrice(makeBoard.getMatrice(4),4,mousePos) || PlacerPieceDansMatrice(makeBoard.getMatrice(5),5,mousePos) || PlacerPieceDansMatrice(makeBoard.getMatrice(6),6,mousePos)) {

            if(jeu.getBoard().castling){
                std::vector<PieceImage>& piecesCamp = *listePieces[couleurIndex];
                caslingChanges(piecesCamp[selectedPieceIndex].getTilePositions()[1],piecesCamp);
                jeu.getBoard().castling=false;
            }
            
            if(jeu.getBoard().isEnPassant){
                enPassantChanges();
                jeu.getBoard().isEnPassant=false;
            }

            if (this->sound.getStatus() != sf::Sound::Playing) {
                this->sound.play();
            }
            
            std::string echec =" ";
            if(!jeu.getBoard().sidesInCheck.empty()){
                echec+="Rois en echec : ";
                for (const auto& side : jeu.getBoard().sidesInCheck){
                    echec += side;
                    echec += " ";
                }
            }
            makeBoard.setTextEchec(echec);
            if(jeu.getBoard().endOfGame){
                makeBoard.setTextGame("Partie Terminee");
                makeBoard.setTextEchec("Gagnant : "+jeu.getBoard().winner);
            }
            else{
                finDeTour();
            }
            
    }
    else{ // Replacement d'une pièce à sa position initial si le déplacement est hors du plateau
        int matrix;
        matrix = (*listePieces[couleurIndex])[selectedPieceIndex].getTilePositions()[1];
        makeBoard.ReplacementPiece(selectedPieceIndex, couleurIndex, matrix, (*listePieces[couleurIndex]));
    }

    isDragging = false;
    
    RemettreCouleurDefautCases();
}

void BoardController::handleSound() {
    if (!this->buffer.loadFromFile("resources/sound/coup.ogg")) {
        throw std::runtime_error("Erreur de chargement du son!");
    }
    this->sound.setBuffer(this->buffer);
}


void BoardController::handleCoup(std::vector<int>& tilePositions) {
    std::pair<int, int> coupOrigine = makeBoard.indexEnCoordonneDePlateau(tilePositions[0], tilePositions[1]);
    this->possibleMoves = jeu.getBoard().MovePiece(coupOrigine.first,coupOrigine.second);

    for (const auto& coup : this->possibleMoves) {
        int matrix = makeBoard.determineSubMatrix(coup.first,coup.second);
        int x = coup.first;
        int y = coup.second;
        if (matrix == 2) { y = coup.second - 4; }
        else if (matrix == 3) { x = coup.first - 4; }
        else if (matrix == 4) { x = coup.first - 4; y = coup.second - 8; }
        else if (matrix == 5) { x = coup.first - 8; y = coup.second - 4; }
        else if (matrix == 6) { x = coup.first - 8; y = coup.second - 8; }
        int index = makeBoard.coordonneEnIndexDeLosange(x, y, matrix);
        drawBoard.changeColorTileDark(makeBoard.getMatrice(matrix)[index]);
        tilesToChangeColor.push_back({index, matrix});
    }
}

bool BoardController::handleCoupJouer(std::vector<int>& tilePositionsOrigine,std::vector<int>& tilePositionsDestination){
    std::pair<int, int> coupOrigine = makeBoard.indexEnCoordonneDePlateau(tilePositionsOrigine[0], tilePositionsOrigine[1]);
    std::pair<int, int> coupDestination = makeBoard.indexEnCoordonneDePlateau(tilePositionsDestination[0], tilePositionsDestination[1]);
    bool coupAutoriser = false;
    if(coupOrigine!=coupDestination){
        for (const auto& coup : this->possibleMoves) {
            if(coupDestination==coup){

               if(jeu.getBoard().PawnOnEdge(coupOrigine.first,coupOrigine.second,coupDestination.first, jeu.getBoard().matrix)){
                    coupEnAttentePromotion = {coupDestination.first, coupDestination.second};
                    this->promotion = true;
                }

                jeu.getBoard().Move(coupOrigine.first,coupOrigine.second,coupDestination.first,coupDestination.second,jeu.getPlayerList(),jeu.getBoard().matrix);
                coupAutoriser = true;
                return true;
            }
        }
        std::cout<<"coup non autoriser"<<std::endl;
    }
    return false;
}


int BoardController::PromotionChoix(const sf::Vector2f& mousePos) {
    for (auto& choix : drawBoard.promotionChoix) {
        if (choix.first.getGlobalBounds().contains(mousePos))
            return choix.second;
    }
    return -1;
}


void BoardController::finDeTour() {
    if(tour==0){ makeBoard.setTextGame("Au tour du joueur Rouge");tour++;}
    else if(tour==1){ makeBoard.setTextGame("Au tour du joueur Noir");tour++;}
    else{ makeBoard.setTextGame("Au tour du joueur Blanc");tour=0;}
}


void BoardController::caslingChanges(int matrix,std::vector<PieceImage>& listePieces){
    if(matrix==1){
        int tour = 0;
        makeBoard.PlacementPiece(tour, makeBoard.getMatrice(1)[3], listePieces, 1,3);
    }
    else if(matrix==2){
        makeBoard.PlacementPiece(rookRight, makeBoard.getMatrice(2)[13], listePieces, 2,13);
    }
    else if(matrix==3){
        makeBoard.PlacementPiece(rookRight, makeBoard.getMatrice(3)[13], listePieces, 3,13);
    }
    else if(matrix==4){
        int tour = 0;
        makeBoard.PlacementPiece(tour, makeBoard.getMatrice(4)[3], listePieces, 4,3);
    }
    else if(matrix==5){
        int tour = 0;
        makeBoard.PlacementPiece(tour, makeBoard.getMatrice(5)[3], listePieces, 5,3);
    }
    else{
        makeBoard.PlacementPiece(rookRight, makeBoard.getMatrice(6)[13], listePieces, 6,13);
    }
}

void BoardController::enPassantChanges(){
    std::vector<PieceImage>& piecesCamp = *listePieces[couleurIndex];
    int matrix = piecesCamp[selectedPieceIndex].getTilePositions()[1];
    int losange = piecesCamp[selectedPieceIndex].getTilePositions()[0];

    if(matrix==1){ losange -= 1; }
    else if(matrix==2){ losange -=4; }
    else if(matrix==3){ losange -=4; }
    else if(matrix==4){ losange -=1; }
    else if(matrix==5){ losange -=1; }
    else{ losange -=4; }

    for (int j = 0; j < listePieces.size(); ++j) {
        if (j == couleurIndex) continue; // Ignore les pièces de la même couleur
        std::vector<PieceImage>& ennemyPieces = *listePieces[j];
        for (int k = 0; k < ennemyPieces.size(); ++k) {
            std::vector<int> pos = ennemyPieces[k].getTilePositions();
            if (pos[0] == losange && pos[1] == matrix) {
                ennemyPieces.erase(ennemyPieces.begin() + k); // Supprimer le pion arrière
                break;
            }
        }
    }
}


void BoardController::aiMove(){
    jeu.getBoard().minmax(jeu.getBoard(), tour, tour, 3, -1000000, 1000000, jeu.getPlayerList());
        
        std::cout<<"moveStart "<< jeu.getBoard().bestMoveStart.first << " " << jeu.getBoard().bestMoveStart.second<<std::endl;
        std::cout<<"moveEnd "<< jeu.getBoard().bestMoveEnd.first << " " << jeu.getBoard().bestMoveEnd.second<<std::endl;
        int IndexMatrixStart = makeBoard.determineSubMatrix(jeu.getBoard().bestMoveStart.first, jeu.getBoard().bestMoveStart.second);
        int IndexMatrixEnd = makeBoard.determineSubMatrix(jeu.getBoard().bestMoveEnd.first, jeu.getBoard().bestMoveEnd.second);
        int xStart = jeu.getBoard().bestMoveStart.first;
        int yStart = jeu.getBoard().bestMoveStart.second;
        if (IndexMatrixStart == 2) { yStart = jeu.getBoard().bestMoveStart.second - 4; }
        else if (IndexMatrixStart == 3) { xStart = jeu.getBoard().bestMoveStart.first - 4; }
        else if (IndexMatrixStart == 4) { xStart = jeu.getBoard().bestMoveStart.first - 4; yStart = jeu.getBoard().bestMoveStart.second - 8; }
        else if (IndexMatrixStart == 5) { xStart = jeu.getBoard().bestMoveStart.first - 8; yStart = jeu.getBoard().bestMoveStart.second - 4; }
        else if (IndexMatrixStart == 6) { xStart = jeu.getBoard().bestMoveStart.first - 8; yStart = jeu.getBoard().bestMoveStart.second - 8; }
        int IndexLosStart = makeBoard.coordonneEnIndexDeLosange(xStart, yStart, IndexMatrixStart);

        int xEnd = jeu.getBoard().bestMoveEnd.first;
        int yEnd = jeu.getBoard().bestMoveEnd.second;
        if (IndexMatrixEnd == 2) { yEnd = jeu.getBoard().bestMoveEnd.second - 4; }
        else if (IndexMatrixEnd == 3) { xEnd = jeu.getBoard().bestMoveEnd.first - 4; }
        else if (IndexMatrixEnd == 4) { xEnd = jeu.getBoard().bestMoveEnd.first - 4; yEnd = jeu.getBoard().bestMoveEnd.second - 8; }
        else if (IndexMatrixEnd == 5) { xEnd = jeu.getBoard().bestMoveEnd.first - 8; yEnd = jeu.getBoard().bestMoveEnd.second - 4; }
        else if (IndexMatrixEnd == 6) { xEnd = jeu.getBoard().bestMoveEnd.first - 8; yEnd = jeu.getBoard().bestMoveEnd.second - 8; }
        int IndexLosEnd = makeBoard.coordonneEnIndexDeLosange(xEnd, yEnd, IndexMatrixEnd);

        std::cout << "AI move: " << IndexMatrixStart << " " << IndexLosStart << std::endl;
        std::cout << "AI move: " << IndexMatrixEnd << " " << IndexLosEnd << std::endl;
        if(tour==0){
            TrouverPieceCapture({IndexLosEnd, IndexMatrixEnd});
            makeBoard.PlacementPieceAI(makeBoard.getWhitePieces(), IndexMatrixStart, IndexLosStart, IndexMatrixEnd, IndexLosEnd);
        }
        else if(tour==1){
            TrouverPieceCapture({IndexLosEnd, IndexMatrixEnd});
            makeBoard.PlacementPieceAI(makeBoard.getRedPieces(), IndexMatrixStart, IndexLosStart, IndexMatrixEnd, IndexLosEnd);
        }
        else{
            TrouverPieceCapture({IndexLosEnd, IndexMatrixEnd});
            makeBoard.PlacementPieceAI(makeBoard.getBlackPieces(), IndexMatrixStart, IndexLosStart, IndexMatrixEnd, IndexLosEnd);
        }
        finDeTour();
        jeu.getBoard().Move(jeu.getBoard().bestMoveStart.first, jeu.getBoard().bestMoveStart.second, jeu.getBoard().bestMoveEnd.first, jeu.getBoard().bestMoveEnd.second, jeu.getPlayerList(), jeu.getBoard().matrix);
        if(jeu.getBoard().endOfGame){
            makeBoard.setTextGame("Partie Terminee");
            makeBoard.setTextEchec("Gagnant : "+jeu.getBoard().winner);
        }
    }
