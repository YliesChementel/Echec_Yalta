#include "Controller.hpp"
#include <iostream>

BoardController::BoardController(Board& board, BoardView& view, sf::RenderWindow& window,Jeu& jeu)
    : board(board), view(view), window(window),jeu(jeu) , isDragging(false), selectedPieceIndex(-1) {handleSound(); initListePieces();}

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
                            piecesCamp[selectedPieceIndex].getSprite().setTexture(view.getPromotionTexture(choix,couleurIndex), true);
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
        view.clear();
        view.drawHexagons(board.getHexagon(), board.getHexagon2());
        view.drawLines(board.getLines());

        view.drawText(board.getCoordText());
        view.drawTextGame(board.getTextGame());
        view.drawTextGame(board.getTextEchec());

        view.drawBoard({board.getMatrice1(),board.getMatrice2(),board.getMatrice3(),board.getMatrice4(),board.getMatrice5(),board.getMatrice6()});
        view.drawPieces(board.getWhitePieces(), board.getRedPieces(), board.getBlackPieces());
        
        if(promotion){
            view.drawChoice(couleurIndex);
        }
        
        view.display();
    }
}

void BoardController::initListePieces() {
    listePieces = {
        &board.getWhitePieces(),
        &board.getRedPieces(),
        &board.getBlackPieces()
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
                break;
            }
        }
    }
}


bool BoardController::PlacerPieceDansMatrice(const std::vector<sf::ConvexShape>& matrix, int indexMatrice, const sf::Vector2f& mousePos) {
    if (board.PieceDansMatrice(mousePos, matrix)) {
        for (int i = 0; i < matrix.size(); ++i) {
            const sf::ConvexShape& losange = matrix[i];
            if (board.PieceDansLosange(losange, mousePos)) {
                std::vector<int> positions = {i, indexMatrice};
                if (handleCoupJouer((*listePieces[couleurIndex])[selectedPieceIndex].getTilePositions(), positions)) {
                    TrouverPieceCapture(positions);
                    board.PlacementPiece(selectedPieceIndex, losange, (*listePieces[couleurIndex]), indexMatrice, i);
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
        view.changeColorTileBright(board.getMatrice(tile[1])[tile[0]]);
    }
    tilesToChangeColor.clear();
}

void BoardController::handleMousePressed(const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    /*if (TrouverPieceSelectioner(*listePieces[0], 0, mousePos)) {// j'utilise la déréférences
        isDragging = true;
    }
    if (TrouverPieceSelectioner(*listePieces[1], 1, mousePos)) {
        isDragging = true;
    }
    if (TrouverPieceSelectioner(*listePieces[2], 2, mousePos)) {
        isDragging = true;
    }*/

    if (TrouverPieceSelectioner(*listePieces[tour], tour, mousePos)) {// j'utilise la déréférences
            isDragging = true;
    }
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
    if (PlacerPieceDansMatrice(board.getMatrice(1),1,mousePos) || PlacerPieceDansMatrice(board.getMatrice(2),2,mousePos) || PlacerPieceDansMatrice(board.getMatrice(3),3,mousePos) ||
        PlacerPieceDansMatrice(board.getMatrice(4),4,mousePos) || PlacerPieceDansMatrice(board.getMatrice(5),5,mousePos) || PlacerPieceDansMatrice(board.getMatrice(6),6,mousePos)) {
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
            board.setTextEchec(echec);
            if(jeu.getBoard().endOfGame){
                board.setTextGame("Partie Terminée");
                board.setTextEchec("Gagnant : "+jeu.getBoard().winner);
            }
            else{
                finDeTour();
            }
            
    }
    else{ // Replacement d'une pièce à sa position initial si le déplacement est hors du plateau
        int matrix;
        matrix = (*listePieces[couleurIndex])[selectedPieceIndex].getTilePositions()[1];
        board.ReplacementPiece(selectedPieceIndex, couleurIndex, matrix, (*listePieces[couleurIndex]));
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
    std::pair<int, int> coupOrigine = board.indexEnCoordonneDePlateau(tilePositions[0], tilePositions[1]);
    this->possibleMoves = jeu.getBoard().MovePiece(coupOrigine.first,coupOrigine.second);

    for (const auto& coup : this->possibleMoves) {
        int matrix = board.determineSubMatrix(coup.first,coup.second);
        int x = coup.first;
        int y = coup.second;
        if (matrix == 2) { y = coup.second - 4; }
        else if (matrix == 3) { x = coup.first - 4; }
        else if (matrix == 4) { x = coup.first - 4; y = coup.second - 8; }
        else if (matrix == 5) { x = coup.first - 8; y = coup.second - 4; }
        else if (matrix == 6) { x = coup.first - 8; y = coup.second - 8; }
        int index = board.coordonneEnIndexDeLosange(x, y, matrix);
        view.changeColorTileDark(board.getMatrice(matrix)[index]);
        tilesToChangeColor.push_back({index, matrix});
    }
}

bool BoardController::handleCoupJouer(std::vector<int>& tilePositionsOrigine,std::vector<int>& tilePositionsDestination){
    std::pair<int, int> coupOrigine = board.indexEnCoordonneDePlateau(tilePositionsOrigine[0], tilePositionsOrigine[1]);
    std::pair<int, int> coupDestination = board.indexEnCoordonneDePlateau(tilePositionsDestination[0], tilePositionsDestination[1]);
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
    for (auto& choix : view.promotionChoix) {
        if (choix.first.getGlobalBounds().contains(mousePos))
            return choix.second;
    }
    return -1;
}


void BoardController::finDeTour() {
    if(tour==0){ board.setTextGame("Au tour du joueur Rouge");tour++;}
    else if(tour==1){ board.setTextGame("Au tour du joueur Noir");tour++;}
    else{ board.setTextGame("Au tour du joueur Blanc");tour=0;}
}
