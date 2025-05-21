#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Makeboard.h"
#include "DrawBoard.h"
#include "Jeu.h"
#include "FallingPiece.h"

class BoardController {
public:
    BoardController(MakeBoard& makeBoard, DrawBoard& drawBoard, sf::RenderWindow& window, Jeu& jeu, std::array<bool, 3> ia, bool debugMode);
    void run();
    void setState(std::unique_ptr<State> newState){
        currentState = std::move(newState);
    }

    void initListePieces();
    void handleSound();
    void PlaySound();
    bool TrouverPieceSelectioner(std::vector<PieceImage>& liste, int listeIndex, sf::Vector2f mousePos);
    bool PlacerPieceDansMatrice(const std::vector<sf::ConvexShape>& matrix, int indexMatrice, const sf::Vector2f& mousePos);
    void RemettreCouleurDefautCases();
    void TrouverPieceCapture(std::vector<int> positions);

    int PromotionChoix(const sf::Vector2f& mousePos);
    void handleBackButtonClick(const sf::Vector2f& mousePos);
    void handleCoup(std::vector<int>& tilePositions);
    bool handleCoupJouer(std::vector<int>& tilePositionsOrigine, std::vector<int>& tilePositionsDestination);
    void finDeTour();
    void aiMove();
    void caslingChanges(int matrix, std::vector<PieceImage>& listePieces);
    void enPassantChanges();
    void makeConfetto();
    void update(float deltaTime);

    MakeBoard& getMakeBoard() { return makeBoard; }
    DrawBoard& getDrawBoard() { return drawBoard; }
    sf::RenderWindow& getWindow() { return window; }
    Jeu& getJeu() { return jeu; }
    bool isDebugMode() const { return debugMode; }
    std::array<std::vector<PieceImage>*, 3>& getListePieces() { return listePieces; }
    int getCouleurIndex() const { return couleurIndex; }
    int getSelectedPieceIndex() const { return selectedPieceIndex; }
    const std::pair<int, int>& getCoupEnAttentePromotion() const { return coupEnAttentePromotion; }
    bool isHome() const { return home; }
    bool isPromotion() const { return promotion; }
    int getTour() const { return tour; }
    bool isEndOfGame() const { return endOfGame; }
    int getRookRight() const { return rookRight; }
    bool isDragging() const { return Dragging; }
    const std::vector<std::pair<int, int>>& getPossibleMoves() const { return possibleMoves; }
    int getIndexDernierePiecePrise() const { return indexDernierePiecePrise; }
    const std::vector<std::vector<int>>& getTilesToChangeColor() const { return tilesToChangeColor; }
    sf::Vector2f getOffsetImage() const { return offsetImage; }
    std::vector<FallingPiece>& getFallingConfetto() { return fallingConfetto; }

    void setDebugMode(bool debugMode) { this->debugMode = debugMode; }
    void setCouleurIndex(int couleurIndex) { this->couleurIndex = couleurIndex; }
    void setSelectedPieceIndex(int selectedPieceIndex) { this->selectedPieceIndex = selectedPieceIndex; }
    void setCoupEnAttentePromotion(const std::pair<int, int>& coupEnAttentePromotion) { this->coupEnAttentePromotion = coupEnAttentePromotion; }
    void setHome(bool home) { this->home = home; }
    void setPromotion(bool promotion) { this->promotion = promotion; }
    void setTour(int tour) { this->tour = tour; }
    void setEndOfGame(bool endOfGame) { this->endOfGame = endOfGame; }
    void setRookRight(int rookRight) { this->   rookRight = rookRight; }
    void setDragging(bool isDragging) { this->Dragging = isDragging; }
    void setIndexDernierePiecePrise(int indexDernierePiecePrise) { this->indexDernierePiecePrise = indexDernierePiecePrise; }
    void addTileToChangeColor(const std::vector<int>& tile) { tilesToChangeColor.push_back(tile); }
    void clearTilesToChangeColor() { tilesToChangeColor.clear(); }
    void setOffsetImage(const sf::Vector2f& offsetImage) { this->offsetImage = offsetImage; }
    void setFallingConfetto(const std::vector<FallingPiece>& fallingConfetto) { this->fallingConfetto = fallingConfetto; }

private:
    MakeBoard& makeBoard;
    DrawBoard& drawBoard;
    sf::RenderWindow& window;
    Jeu& jeu;
    std::array<bool, 3> ia;
    bool debugMode;

    std::unique_ptr<State> currentState;
    int tour = 0;
    bool endOfGame = false;
    int rookRight = 7;
    bool home = false;
    bool promotion = false;

    std::array<std::vector<PieceImage>*, 3> listePieces;
    int indexDernierePiecePrise;
    std::pair<int, int> coupEnAttentePromotion;
    std::vector<std::pair<int, int>> possibleMoves;

    bool Dragging;
    int selectedPieceIndex;
    int couleurIndex;
    sf::Vector2f offsetImage;

    std::vector<sf::Texture> confettoTextures;
    std::vector<FallingPiece> fallingConfetto;
    std::vector<std::string> confettoPaths = {
        "resources/images/confetti/Confetto_blanc.png",
        "resources/images/confetti/Confetto_bleu.png",
        "resources/images/confetti/Confetto_jaune.png",
        "resources/images/confetti/Confetto_orange.png",
        "resources/images/confetti/Confetto_rose.png",
        "resources/images/confetti/Confetto_rouge.png",
        "resources/images/confetti/Confetto_vert.png",
        "resources/images/confetti/Confetto_violet.png"
    };

    sf::Sound sound;
    sf::SoundBuffer buffer;

    std::vector<std::vector<int>> tilesToChangeColor;
};

#endif
