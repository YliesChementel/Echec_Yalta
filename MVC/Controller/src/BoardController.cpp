#include "include/BoardController.hpp"
#include "include/PromotionState.hpp"
#include "include/AiState.hpp"
#include "include/VictoryState.hpp"
#include "include/DebugModeState.hpp"
#include <iostream>


BoardController::BoardController(MakeBoard& makeBoard, DrawBoard& drawBoard, sf::RenderWindow& window,Jeu& jeu, std::array<bool, 3> ia, bool debugMode)
    : makeBoard(makeBoard), drawBoard(drawBoard), window(window),jeu(jeu) , Dragging(false), selectedPieceIndex(-1),home(false) {
        handleSound(); 
        initListePieces();
        makeConfetto();
        this->ia = ia;
        if(debugMode){
            setState(std::make_unique<DebugModeState>());
            setDebugMode(debugMode);
            makeBoard.setTextGame("Debug Mode");
            makeBoard.setTextEchec("Déplacement des pièces dans l'ordre voulu");
        }
        else{
            setState(std::make_unique<PlayingState>());
            if(ia[tour]){
                setBaseText("L'IA Blanc réfléchit");
            }
            else makeBoard.setTextGame("Au tour du joueur Blanc");

        }
        
    }

void BoardController::run() {
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    currentState->handleMousePressed(*this, event);
                }
                else if (event.type == sf::Event::MouseMoved) {
                    currentState->handleMouseMoved(*this, event);
                }
                else if (event.type == sf::Event::MouseButtonReleased) {
                    currentState->handleMouseReleased(*this, event);
                }
            }

            float deltaTime = clock.restart().asSeconds();
            currentState->update(*this, deltaTime);
            currentState->render(*this);
            drawBoard.display();

            if (!jeu.getBoard().isEndOfGame() && ia[tour] && !promotion) {
                if (currentState->getStateName() != "Ai") {
                    setState(std::make_unique<AiState>());
                }

                if (!iaEnCours) {
                    makeBoard.setTextGame(baseText);
                    setLoadingDotsTimer(0);
                    setLoadingDotsCount(0);
                    startAiMove();
                    iaEnCours = true;
                }

                if (aiMoveReady) {
                    aiMove(); 
                    aiMoveReady = false;
                    iaEnCours = false;
                }
            }
            else if(!jeu.getBoard().isEndOfGame() && !ia[tour] && !promotion){
                if(isDebugMode()){
                    setState(std::make_unique<DebugModeState>());
                }
                else{
                    setState(std::make_unique<PlayingState>());

                }
            }

            if (home) {
                stopAiThread = true;
                if (aiThread.joinable()) {
                    aiThread.join(); // Attend la fin du thread
                }
                return;
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
                std::cout << "Piece capturee" << std::endl;
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

void BoardController::handleBackButtonClick(const sf::Vector2f& mousePos) {
    if (makeBoard.isMouseOverBackButton(mousePos)) {
        home = true;
    }
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

               if(jeu.getBoard().PawnOnEdge(coupOrigine.first,coupOrigine.second,coupDestination.first, jeu.getBoard().getMatrix())){
                    coupEnAttentePromotion = {coupDestination.first, coupDestination.second};
                    setState(std::make_unique<PromotionState>());
                    this->promotion = true;
                }

                jeu.getBoard().Move(coupOrigine.first,coupOrigine.second,coupDestination.first,coupDestination.second,jeu.getPlayerList(),jeu.getBoard().getMatrix());
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
    if(tour==0){
        tour++;
        if(ia[tour]){
            this->setBaseText("L'IA Rouge réfléchit");
            this->getMakeBoard().setTextGame(baseText);
        }else{
            makeBoard.setTextGame("Au tour du joueur Rouge");
        }
    }
    else if(tour==1){
        tour++;
        if(ia[tour]){
            this->setBaseText("L'IA Noir réfléchit");
            makeBoard.setTextGame(baseText); 
        }else{
            makeBoard.setTextGame("Au tour du joueur Noir");
        }
    }
    else{ 
        tour=0;
        if(ia[tour]){
            this->setBaseText("L'IA Blanc réfléchit");
            makeBoard.setTextGame(baseText);
        }else{
            makeBoard.setTextGame("Au tour du joueur Blanc");
        }
    }
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
    int IndexMatrixStart = makeBoard.determineSubMatrix(jeu.getBoard().getBestMoveStart().first, jeu.getBoard().getBestMoveStart().second);
    int IndexMatrixEnd = makeBoard.determineSubMatrix(jeu.getBoard().getBestMoveEnd().first, jeu.getBoard().getBestMoveEnd().second);
    int xStart = jeu.getBoard().getBestMoveStart().first;
    int yStart = jeu.getBoard().getBestMoveStart().second;
    if (IndexMatrixStart == 2) { yStart = jeu.getBoard().getBestMoveStart().second - 4; }
    else if (IndexMatrixStart == 3) { xStart = jeu.getBoard().getBestMoveStart().first - 4; }
    else if (IndexMatrixStart == 4) { xStart = jeu.getBoard().getBestMoveStart().first - 4; yStart = jeu.getBoard().getBestMoveStart().second - 8; }
    else if (IndexMatrixStart == 5) { xStart = jeu.getBoard().getBestMoveStart().first - 8; yStart = jeu.getBoard().getBestMoveStart().second - 4; }
    else if (IndexMatrixStart == 6) { xStart = jeu.getBoard().getBestMoveStart().first - 8; yStart = jeu.getBoard().getBestMoveStart().second - 8; }
    int IndexLosStart = makeBoard.coordonneEnIndexDeLosange(xStart, yStart, IndexMatrixStart);

    int xEnd = jeu.getBoard().getBestMoveEnd().first;
    int yEnd = jeu.getBoard().getBestMoveEnd().second;
    if (IndexMatrixEnd == 2) { yEnd = jeu.getBoard().getBestMoveEnd().second - 4; }
    else if (IndexMatrixEnd == 3) { xEnd = jeu.getBoard().getBestMoveEnd().first - 4; }
    else if (IndexMatrixEnd == 4) { xEnd = jeu.getBoard().getBestMoveEnd().first - 4; yEnd = jeu.getBoard().getBestMoveEnd().second - 8; }
    else if (IndexMatrixEnd == 5) { xEnd = jeu.getBoard().getBestMoveEnd().first - 8; yEnd = jeu.getBoard().getBestMoveEnd().second - 4; }
    else if (IndexMatrixEnd == 6) { xEnd = jeu.getBoard().getBestMoveEnd().first - 8; yEnd = jeu.getBoard().getBestMoveEnd().second - 8; }
    int IndexLosEnd = makeBoard.coordonneEnIndexDeLosange(xEnd, yEnd, IndexMatrixEnd);

    couleurIndex = tour;
    if(tour==0){
        makeBoard.PlacementPieceAI(makeBoard.getWhitePieces(), IndexMatrixStart, IndexLosStart, IndexMatrixEnd, IndexLosEnd, selectedPieceIndex);
    }
    else if(tour==1){
        makeBoard.PlacementPieceAI(makeBoard.getRedPieces(), IndexMatrixStart, IndexLosStart, IndexMatrixEnd, IndexLosEnd, selectedPieceIndex);
    }
    else{
        makeBoard.PlacementPieceAI(makeBoard.getBlackPieces(), IndexMatrixStart, IndexLosStart, IndexMatrixEnd, IndexLosEnd, selectedPieceIndex);
    }

    /*if (jeu.getBoard().isCastling()) {
        std::vector<PieceImage>& piecesCamp = *listePieces[couleurIndex];
        caslingChanges(piecesCamp[selectedPieceIndex].getTilePositions()[1],piecesCamp);
        jeu.getBoard().setCastling(false);
    }
    
    if (jeu.getBoard().isEnPassantMove()) {
        enPassantChanges();
    }*/

    finDeTour();
    jeu.getBoard().Move(jeu.getBoard().getBestMoveStart().first, jeu.getBoard().getBestMoveStart().second, jeu.getBoard().getBestMoveEnd().first, jeu.getBoard().getBestMoveEnd().second, jeu.getPlayerList(), jeu.getBoard().getMatrix());
    TrouverPieceCapture({IndexLosEnd, IndexMatrixEnd});
    PlaySound();       
    std::string echec =" ";
    if(!getJeu().getBoard().getSidesInCheck().empty()){
        echec+="Rois en echec : ";
        for (const auto& side : getJeu().getBoard().getSidesInCheck()){
            echec += side;
            echec += " ";
        }
    }
    getMakeBoard().setTextEchec(echec);
    if(jeu.getBoard().isEndOfGame()){
        makeBoard.setTextGame("Partie Terminée");
        if(jeu.getBoard().isStalemate()){ 
            makeBoard.setTextEchec("Stalemate");
        }
        else{
            makeBoard.setTextEchec("Gagnant : "+jeu.getBoard().getWinner());
        }
        setState(std::make_unique<VictoryState>());
    }
}


void BoardController::makeConfetto() {
    for (const auto& path : confettoPaths) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            confettoTextures.push_back(texture);
        } else {
            std::cout << "Erreur chargement texture : " << path << "\n";
        }
    }
    for (int j = 0; j < 8; ++j){
        for (int i = 0; i < 8; ++i) {
            float x = static_cast<float>(rand() % 1200);
            fallingConfetto.emplace_back(confettoTextures[i], x, 200.f); 
        }
    }
};

void BoardController::update(float deltaTime) {
    for (auto& confetto : fallingConfetto) {
        confetto.update(deltaTime);
    }
} 

void BoardController::PlaySound() {
    if (this->sound.getStatus() != sf::Sound::Playing) {
        this->sound.play();
    }
}


void BoardController::startAiMove() {
    if (aiThread.joinable()) {
        aiThread.join(); // Assure qu'on ne lance pas un second thread sans avoir terminé le premier
    }
    aiMoveReady = false;
    aiCalculating = true;
    stopAiThread = false;

    aiThread = std::thread([this]() {
         try {
            jeu.getBoard().minmax(jeu.getBoard(), tour, tour, 4, 4, -1000000, 1000000, jeu.getPlayerList(),stopAiThread);
            if (stopAiThread) return;
            aiMoveReady = true;
            aiCalculating = false;
        } catch (const std::exception& e) {
            std::cerr << "Exception dans le thread IA : " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Exception inconnue dans le thread IA" << std::endl;
        }
    });
   // aiThread.detach(); 
}