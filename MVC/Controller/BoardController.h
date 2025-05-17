#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Makeboard.h"
#include "DrawBoard.h"
#include "Jeu.h"

class BoardController {
public:
    BoardController(MakeBoard& makeBoard, DrawBoard& drawBoard, sf::RenderWindow& window,Jeu& jeu);
    void run();// Démarre la boucle principale de l'application

private:
    MakeBoard& makeBoard;
    DrawBoard& drawBoard;
    sf::RenderWindow& window;
    Jeu& jeu;

    /////////////////
    //
    std::vector<std::pair<int, int>> possibleMoves;

    std::array<std::vector<PieceImage>*, 3> listePieces;
    void initListePieces();

    int tour =0;
    bool endOfGame=false;

    int rookRight=7;


    int indexDernierePiecePrise;
    std::pair<int,int> coupEnAttentePromotion;
    bool promotion = false;
    int PromotionChoix(const sf::Vector2f& mousePos);

    void caslingChanges(int matrix,std::vector<PieceImage>& listePieces);
    void enPassantChanges();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Variables pour le drag & drop
    bool isDragging;
    int selectedPieceIndex;
    int couleurIndex;
    sf::Vector2f offsetImage;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Gestion du son
    sf::Sound sound;
    sf::SoundBuffer buffer;
    void handleSound();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Gestion des événements
    void handleMousePressed(const sf::Event& event);
    void handleMouseMoved(const sf::Event& event);
    void handleMouseReleased(const sf::Event& event);

    void finDeTour();
    bool TrouverPieceSelectioner(std::vector<PieceImage>& liste, int listeIndex, sf::Vector2f mousePos);
    bool PlacerPieceDansMatrice(const std::vector<sf::ConvexShape>& matrice, int indexMatrice, const sf::Vector2f& mousePos);
    void RemettreCouleurDefautCases();
    void TrouverPieceCapture(std::vector<int> positions);

    std::vector<std::vector<int>> tilesToChangeColor;
    void handleCoup(std::vector<int>& tilePositions);
    bool handleCoupJouer(std::vector<int>& tilePositionsOrigine,std::vector<int>& tilePositionsDestination);

};

#endif // BOARD_CONTROLLER_H
