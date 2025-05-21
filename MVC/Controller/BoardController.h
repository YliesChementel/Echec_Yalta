#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Makeboard.h"
#include "DrawBoard.h"
#include "Jeu.h"
#include "FallingPiece.h"

class BoardController {
public:
    BoardController(MakeBoard& makeBoard, DrawBoard& drawBoard, sf::RenderWindow& window,Jeu& jeu, std::array<bool, 3> ia);
    void run();

private:
    MakeBoard& makeBoard;
    DrawBoard& drawBoard;
    sf::RenderWindow& window;
    Jeu& jeu;

    int tour = 0;
    bool endOfGame = false;
    int rookRight = 7;
    bool home = false;
    std::array<bool, 3> ia;

    std::vector<std::pair<int, int>> possibleMoves;
    std::array<std::vector<PieceImage>*, 3> listePieces;
    int indexDernierePiecePrise;
    std::pair<int, int> coupEnAttentePromotion;
    bool promotion = false;

    bool isDragging;
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

    void initListePieces();

    void handleMousePressed(const sf::Event& event);
    void handleMouseMoved(const sf::Event& event);
    void handleMouseReleased(const sf::Event& event);
    void handleBackButtonClick(const sf::Vector2f& mousePos);
    void handleSound();

    void finDeTour();
    void aiMove();
    void caslingChanges(int matrix, std::vector<PieceImage>& listePieces);
    void enPassantChanges();
    int PromotionChoix(const sf::Vector2f& mousePos);

    bool TrouverPieceSelectioner(std::vector<PieceImage>& liste, int listeIndex, sf::Vector2f mousePos);
    bool PlacerPieceDansMatrice(const std::vector<sf::ConvexShape>& matrice, int indexMatrice, const sf::Vector2f& mousePos);
    void RemettreCouleurDefautCases();
    void TrouverPieceCapture(std::vector<int> positions);

    std::vector<std::vector<int>> tilesToChangeColor;
    void handleCoup(std::vector<int>& tilePositions);
    bool handleCoupJouer(std::vector<int>& tilePositionsOrigine, std::vector<int>& tilePositionsDestination);

    void makeConfetto();
    void update(float deltaTime);
};

#endif
