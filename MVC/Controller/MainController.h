#ifndef MAINC_CONTROLLER_H
#define MAINC_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"


class MainController {
    public:
        enum class GameState {
            MENU,
            GAME
        };

        MainController() : currentState(GameState::MENU), menu(), settings() {
            settings.antialiasingLevel = 8;
            window.create(sf::VideoMode(1150, 1000), "Echec Yalta", sf::Style::Default, settings);
        }
        void run();
        void setGameState(GameState state) { currentState = state; }
        GameState getGameState() const { return currentState; }
        void runGame();
        
    private:
        GameState currentState;
        sf::ContextSettings settings;
        sf::RenderWindow window;
        Menu menu;
};
#endif