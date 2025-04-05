#include "Controller.hpp"
#include <iostream>

BoardController::BoardController(Board& board, BoardView& view, sf::RenderWindow& window)
    : board(board), view(view), window(window), isDragging(false), selectedPieceIndex(-1) {handleSound();}

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
    const std::vector<sf::Sprite>& white = board.getWhitePieces();
    for (size_t i = 0; i < white.size(); ++i) {
        if (white[i].getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            selectedPieceIndex = static_cast<int>(i);  // index pour WhitePieces
            offsetImage = mousePos - white[i].getPosition();
            return;
        }
    }
    // Recherche dans RedPieces
    const std::vector<sf::Sprite>& red = board.getRedPieces();
    for (size_t i = 0; i < red.size(); ++i) {
        if (red[i].getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            // les indices de red commencent après celles de white
            selectedPieceIndex = static_cast<int>(i + white.size());
            offsetImage = mousePos - red[i].getPosition();
            return;
        }
    }
    // Recherche dans BlackPieces
    const std::vector<sf::Sprite>& black = board.getBlackPieces();
    for (size_t i = 0; i < black.size(); ++i) {
        if (black[i].getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            // les indices de black commencent après white et red
            selectedPieceIndex = static_cast<int>(i + white.size() + red.size());
            offsetImage = mousePos - black[i].getPosition();
            return;
        }
    }
}

void BoardController::handleMouseMoved(const sf::Event& event) {
    if (!isDragging)
        return;

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    std::vector<sf::Sprite>& white = board.getWhitePieces();
    std::vector<sf::Sprite>& black = board.getBlackPieces();
    std::vector<sf::Sprite>& red = board.getRedPieces();

    if (selectedPieceIndex < white.size()) {
        white[selectedPieceIndex].setPosition(mousePos - offsetImage);
    } else if (selectedPieceIndex < white.size() + red.size()) {
        red[selectedPieceIndex - white.size()].setPosition(mousePos - offsetImage);
    } else {
        black[selectedPieceIndex - white.size() - red.size()].setPosition(mousePos - offsetImage);
    }
}

void BoardController::handleMouseReleased(const sf::Event& event) {
    if (!isDragging)
        return;

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool placed = false;

    // Lambda pour tester sur une matrice donnée
    auto tryPlaceInMatrix = [&](const std::vector<sf::ConvexShape>& matrice) -> bool {
        if (board.PieceDansMatrice(mousePos, matrice)) {
            for (const auto& losange : matrice) {
                if (board.PieceDansLosange(losange, mousePos)) {
                    board.PlacementPiece(selectedPieceIndex, losange,board.getWhitePieces(),board.getBlackPieces(),board.getRedPieces());
                    return true;
                }
            }
        }
        return false;
    };

    // Vérifier dans les 6 matrices
    if (tryPlaceInMatrix(board.getMatrice1()) ||
        tryPlaceInMatrix(board.getMatrice2()) ||
        tryPlaceInMatrix(board.getMatrice3()) ||
        tryPlaceInMatrix(board.getMatrice4()) ||
        tryPlaceInMatrix(board.getMatrice5()) ||
        tryPlaceInMatrix(board.getMatrice6())) {
        placed = true;
    }

    if (this->sound.getStatus() != sf::Sound::Playing) {
        this->sound.play();
    }
    isDragging = false;
    selectedPieceIndex = -1;
}

void BoardController::handleSound() {
    this->buffer;
    if (!this->buffer.loadFromFile("resources/sound/coup.ogg")) {
        throw std::runtime_error("Error loading sound!");
    }
    this->sound.setBuffer(this->buffer);
}