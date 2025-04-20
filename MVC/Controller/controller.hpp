#ifndef BOARD_CONTROLLER_HPP
#define BOARD_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "model.hpp"
#include "view.hpp"
#include "Jeu.h"

class BoardController {
public:
    BoardController(Board& board, BoardView& view, sf::RenderWindow& window,Jeu& jeu);
    void run();// Démarre la boucle principale de l'application

private:
    Board& board;
    BoardView& view;
    sf::RenderWindow& window;
    Jeu& jeu;

    /////////////////
    //
    std::vector<std::pair<int, int>> coupsPossibles;

    std::array<std::vector<PieceImage>*, 3> listePieces;
    void initListePieces();

    int tour =0;


    int indexDernierePiecePrise;
    std::pair<int,int> coupEnAttentePromotion;
    bool promotion = false;
    int PromotionChoix(const sf::Vector2f& mousePos);

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

#endif // BOARD_CONTROLLER_HPP
