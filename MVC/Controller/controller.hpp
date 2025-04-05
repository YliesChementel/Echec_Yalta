#ifndef BOARD_CONTROLLER_HPP
#define BOARD_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "model.hpp"
#include "view.hpp"

class BoardController {
public:
    BoardController(Board& board, BoardView& view, sf::RenderWindow& window);
    void run();// Démarre la boucle principale de l'application

private:
    Board& board;
    BoardView& view;
    sf::RenderWindow& window;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Variables pour le drag & drop
    bool isDragging;
    int selectedPieceIndex;
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
};

#endif // BOARD_CONTROLLER_HPP
