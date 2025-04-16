#include "Controller.hpp"
#include <iostream>

BoardController::BoardController(Board& board, BoardView& view, sf::RenderWindow& window,Jeu& jeu)
    : board(board), view(view), window(window),jeu(jeu) , isDragging(false), selectedPieceIndex(-1) {handleSound();}

void BoardController::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleMousePressed(event);
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
        
        // Regroupement de toutes les matrices
        std::vector<std::vector<sf::ConvexShape>> allMatrices;
        {
            const auto& m1 = board.getMatrice1();
            const auto& m2 = board.getMatrice2();
            const auto& m3 = board.getMatrice3();
            const auto& m4 = board.getMatrice4();
            const auto& m5 = board.getMatrice5();
            const auto& m6 = board.getMatrice6();
            allMatrices.push_back(m1);
            allMatrices.push_back(m2);
            allMatrices.push_back(m3);
            allMatrices.push_back(m4);
            allMatrices.push_back(m5);
            allMatrices.push_back(m6);
        }
        view.drawBoard(allMatrices);
        view.drawPieces(board.getWhitePieces(), board.getRedPieces(), board.getBlackPieces());
        view.display();
    }
}

void BoardController::handleMousePressed(const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Recherche de la pièce cliquée dans WhitePieces
    for (size_t i = 0; i < board.getWhitePieces().size(); ++i) {
        if (board.getWhitePieces()[i].getSprite().getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            selectedPieceIndex = static_cast<int>(i);  // index pour WhitePieces
            offsetImage = mousePos - board.getWhitePieces()[i].getSprite().getPosition();
            handleCoup(board.getWhitePieces()[i].getTilePositions());
            //view.changeColorTile(board.getMatrice1());
            return;
        }
    }
    // Recherche dans RedPieces
    for (size_t i = 0; i < board.getRedPieces().size(); ++i) {
        if (board.getRedPieces()[i].getSprite().getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            selectedPieceIndex = static_cast<int>(i + board.getWhitePieces().size());
            offsetImage = mousePos - board.getRedPieces()[i].getSprite().getPosition();
            handleCoup(board.getRedPieces()[i].getTilePositions());
            return;
        }
    }
    // Recherche dans BlackPieces
    for (size_t i = 0; i < board.getBlackPieces().size(); ++i) {
        if (board.getBlackPieces()[i].getSprite().getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            selectedPieceIndex = static_cast<int>(i + board.getWhitePieces().size() + board.getRedPieces().size());
            offsetImage = mousePos - board.getBlackPieces()[i].getSprite().getPosition();
            handleCoup(board.getBlackPieces()[i].getTilePositions());
            return;
        }
    }
}

void BoardController::handleMouseMoved(const sf::Event& event) {
    if (!isDragging) return;

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Déplacement des pièces en fonction de l'index sélectionné
    if (selectedPieceIndex < board.getWhitePieces().size()) {
        board.getWhitePieces()[selectedPieceIndex].getSprite().setPosition(mousePos - offsetImage);
    } else if (selectedPieceIndex < board.getWhitePieces().size() + board.getRedPieces().size()) {
        board.getRedPieces()[selectedPieceIndex - board.getWhitePieces().size()].getSprite().setPosition(mousePos - offsetImage);
    } else {
        board.getBlackPieces()[selectedPieceIndex - board.getWhitePieces().size() - board.getRedPieces().size()].getSprite().setPosition(mousePos - offsetImage);
    }
}


void BoardController::handleMouseReleased(const sf::Event& event) {
    if (!isDragging)
        return;

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool placed = false;

    // Lambda pour tester sur une matrice donnée
    auto tryPlaceInMatrix = [&](const std::vector<sf::ConvexShape>& matrice,int indexMatrice) -> bool {
        if (board.PieceDansMatrice(mousePos, matrice)) {
            for (size_t i = 0; i < matrice.size(); ++i) {
                const auto& losange = matrice[i];
                if (board.PieceDansLosange(losange, mousePos)) {
                    std::vector<int> positions = {static_cast<int>(i), indexMatrice};
                    std::cout << "Origine losange : " << i << " - matrice :" << indexMatrice<<std::endl;/////////////////////////////////////////////////////
                    if (selectedPieceIndex < board.getWhitePieces().size()) {
                        if(handleCoupJouer(board.getWhitePieces()[selectedPieceIndex].getTilePositions(),positions)){
                            board.PlacementPiece(selectedPieceIndex, losange, board.getWhitePieces(), board.getBlackPieces(), board.getRedPieces(),indexMatrice,i);
                            return true;
                        }
                        else{
                            return false;
                        }
                    } else if (selectedPieceIndex < board.getWhitePieces().size() + board.getRedPieces().size()) {
                        if(handleCoupJouer(board.getRedPieces()[selectedPieceIndex - board.getWhitePieces().size()].getTilePositions(),positions)){
                            board.PlacementPiece(selectedPieceIndex, losange, board.getWhitePieces(), board.getBlackPieces(), board.getRedPieces(),indexMatrice,i);
                            return true;
                        }
                        else{
                            return false;
                        }
                    } else {
                        if(handleCoupJouer(board.getBlackPieces()[selectedPieceIndex - board.getWhitePieces().size() - board.getRedPieces().size()].getTilePositions(),positions)){
                            board.PlacementPiece(selectedPieceIndex, losange, board.getWhitePieces(), board.getBlackPieces(), board.getRedPieces(),indexMatrice,i);
                            return true;
                        }
                        else{
                            return false;
                        }
                    }
                    //board.PlacementPiece(selectedPieceIndex, losange, board.getWhitePieces(), board.getBlackPieces(), board.getRedPieces(),indexMatrice,i);
                    //return true;
                }
            }
        }
        return false;
    };

    // Vérifier dans les 6 matrices
    if (tryPlaceInMatrix(board.getMatrice1(),1) ||
        tryPlaceInMatrix(board.getMatrice2(),2) ||
        tryPlaceInMatrix(board.getMatrice3(),3) ||
        tryPlaceInMatrix(board.getMatrice4(),4) ||
        tryPlaceInMatrix(board.getMatrice5(),5) ||
        tryPlaceInMatrix(board.getMatrice6(),6)) {
        placed = true;
    }
    else{
        int matrice;
        if (selectedPieceIndex < board.getWhitePieces().size()) {
            matrice = board.getWhitePieces()[selectedPieceIndex].getTilePositions()[1];
            board.ReplacementPiece(selectedPieceIndex, 0, matrice, board.getWhitePieces(), {board.getMatrice1(), board.getMatrice2(), board.getMatrice3(), board.getMatrice4(), board.getMatrice5(), board.getMatrice6()});
        } 
        else if (selectedPieceIndex < board.getWhitePieces().size() + board.getRedPieces().size()) {
            matrice = board.getRedPieces()[selectedPieceIndex - board.getWhitePieces().size()].getTilePositions()[1];
            selectedPieceIndex -= board.getWhitePieces().size(); // Ajuster l'index pour RedPieces
            board.ReplacementPiece(selectedPieceIndex, 1, matrice, board.getRedPieces(), {board.getMatrice1(), board.getMatrice2(), board.getMatrice3(), board.getMatrice4(), board.getMatrice5(), board.getMatrice6()});
        } 
        else {
            matrice = board.getBlackPieces()[selectedPieceIndex - board.getWhitePieces().size() - board.getRedPieces().size()].getTilePositions()[1];
            selectedPieceIndex -= (board.getWhitePieces().size() + board.getRedPieces().size()); // Ajuster l'index pour BlackPieces
            board.ReplacementPiece(selectedPieceIndex, 2, matrice, board.getBlackPieces(), {board.getMatrice1(), board.getMatrice2(), board.getMatrice3(), board.getMatrice4(), board.getMatrice5(), board.getMatrice6()});
        }
    }

    if (this->sound.getStatus() != sf::Sound::Playing) {
        this->sound.play();
    }
    isDragging = false;
    selectedPieceIndex = -1;
    for(const auto& tile : tilesToChangeColor) {
        if(tile[1]==1){
            view.changeColorTileBright(board.getMatrice1()[tile[0]]);
        }
        else if(tile[1]==2){
            view.changeColorTileBright(board.getMatrice2()[tile[0]]);
        }
        else if(tile[1]==3){
            view.changeColorTileBright(board.getMatrice3()[tile[0]]);
        }
        else if(tile[1]==4){
            view.changeColorTileBright(board.getMatrice4()[tile[0]]);
        }
        else if(tile[1]==5){
            view.changeColorTileBright(board.getMatrice5()[tile[0]]);
        }
        else if(tile[1]==6){
            view.changeColorTileBright(board.getMatrice6()[tile[0]]);
        }
    }
    tilesToChangeColor.clear();
}

void BoardController::handleSound() {
    this->buffer;
    if (!this->buffer.loadFromFile("resources/sound/coup.ogg")) {
        throw std::runtime_error("Error loading sound!");
    }
    this->sound.setBuffer(this->buffer);
}


int determineSousMatrice(int x, int y) {
    if (x < 4 && y < 4) return 1; // haut gauche
    if (x < 4 && y >= 4 && y < 8) return 2; // haut milieu
    if (y < 4 && x >= 4 && x < 8) return 3; // milieu gauche
    if (y >= 7 && x >= 4 && x < 8) return 4; // milieu droite
    if (x >= 7 && y >= 4 && y < 8) return 5; // bas milieu
    if (x >= 7 && y >= 7) return 6; // bas droite
    return 0;
}

int coordToIndex(int x, int y) {
    return (3 - x) * 4 + (3 - y);
}


int coordToIndexForSubmatrix(int x, int y, int matrice) {
    if (matrice == 1) {
        return 15 - (x + 4 * y); //bon
    }
    else if (matrice == 2) {
        return (3 - x) * 4 + y; //bon
    }
    else if (matrice == 3) { //bon
        return 4 * x + (3 - y);
    }
    else if (matrice == 4) { //bon
        return 4 * y + x;
    }
    else if (matrice == 5) { //bon
        return 4 * y + x;
    }
    else if (matrice == 6) { //bon
        return  x * 4 + y;
    }
    return -1;

}

std::pair<int, int> indexToCoord(int index) {
    int y = 3 - (index / 4);  // division entière pour obtenir la ligne
    int x = 3 - (index % 4);  // reste pour obtenir la colonne
    return {x, y};
}


std::pair<int, int> indexToCoordForSubmatrix(int index, int sousMatrice) {
    int x, y;
    
    if(sousMatrice == 1) {
        y = 3 - (index / 4);  
        x = 3 - (index % 4);
    }
    else if(sousMatrice == 2) {
        x = 3 - index / 4;
        y = (index % 4) + 4;
    }
    else if(sousMatrice == 3) {
        x =  index / 4 + 4 ;
        y = 3 - index % 4 ;
    }
    else if(sousMatrice == 4) {
        y = index / 4 + 8;
        x = index % 4 + 4;
    }
    else if(sousMatrice == 5) {
        y = index / 4 + 4;
        x = index % 4 + 8;
    }
    else if(sousMatrice == 6) {
        x = index / 4 + 8;
        y = index % 4 + 8;
    }
    else {
        throw std::invalid_argument("Invalid submatrix number");
    }
    
    return {x, y};
}

void BoardController::handleCoup(std::vector<int>& tilePositions) {
    std::vector<std::pair<int, int>> coupEnLosange = {
        {3, 3}, {3, 2}, {3, 1}, {3, 0},
        {2, 3}, {2, 2}, {2, 1}, {2, 0},
        {1, 3}, {1, 2}, {1, 1}, {1, 0},
        {0, 3}, {0, 2}, {0, 1}, {0, 0}
    };
    std::pair<int, int> coupOrigine = indexToCoordForSubmatrix(tilePositions[0], tilePositions[1]);
    this->coupsPossibles = jeu.GetPlateau().DeplacerPiece(coupOrigine.first,coupOrigine.second);

    for (const auto& coup : this->coupsPossibles) {
        int matrice = determineSousMatrice(coup.first,coup.second);
        if(matrice == 1) {
            int index = coordToIndexForSubmatrix(coup.first,coup.second, matrice);
            view.changeColorTileDark(board.getMatrice1()[index]);
            tilesToChangeColor.push_back({index, matrice});
        }
        else if(matrice == 2) {
            int index = coordToIndexForSubmatrix(coup.first, coup.second-4, matrice);
            view.changeColorTileDark(board.getMatrice2()[index]);
            tilesToChangeColor.push_back({index, matrice});
        }
        else if(matrice == 3) {
            int index = coordToIndexForSubmatrix(coup.first-4, coup.second,matrice);
            view.changeColorTileDark(board.getMatrice3()[index]);
            tilesToChangeColor.push_back({index, matrice});
        }
        else if(matrice == 4) {
            int index = coordToIndexForSubmatrix(coup.first-4, coup.second-8, matrice);
            view.changeColorTileDark(board.getMatrice4()[index]);
            tilesToChangeColor.push_back({index, matrice});
        }
        else if(matrice == 5) {
            int index = coordToIndexForSubmatrix(coup.first-8, coup.second-4, matrice);
            view.changeColorTileDark(board.getMatrice5()[index]);
            tilesToChangeColor.push_back({index, matrice});
        }
        else if(matrice == 6) {
            int index = coordToIndexForSubmatrix(coup.first-8, coup.second-8, matrice);
            view.changeColorTileDark(board.getMatrice6()[index]);
            tilesToChangeColor.push_back({index, matrice});
        }
    }

}

bool BoardController::handleCoupJouer(std::vector<int>& tilePositionsOrigine,std::vector<int>& tilePositionsDestination){
    std::cout<< "coup origine " << tilePositionsOrigine[0] << " " << tilePositionsOrigine[1]<< std::endl;
    std::cout<< "coup destination " << tilePositionsDestination[0] << " " << tilePositionsDestination[1]<< std::endl;
    std::pair<int, int> coupOrigine = indexToCoordForSubmatrix(tilePositionsOrigine[0], tilePositionsOrigine[1]);
    std::pair<int, int> coupDestination = indexToCoordForSubmatrix(tilePositionsDestination[0], tilePositionsDestination[1]);
    bool coupAutoriser = false;
    if(coupOrigine!=coupDestination){
        for (const auto& coup : this->coupsPossibles) {
            if(coupDestination==coup){
                jeu.GetPlateau().Deplacement(coupOrigine.first,coupOrigine.second,coupDestination.first,coupDestination.second,jeu.GetListeJoueur(),jeu.GetPlateau().matrice);
                coupAutoriser = true;
                return true;
            }
        }
        std::cout<<"coup non autoriser"<<std::endl;
    }
    return false;
}
