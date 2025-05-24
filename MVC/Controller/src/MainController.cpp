#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "../include/MainController.hpp"
#include "../include/BoardController.hpp"
#include "../View/include/MakeBoard.hpp"
#include "../View/include/DrawBoard.hpp"
#include "../include/BoardController.hpp"
#include "../Model/include/Jeu.hpp"
#include "../View/include/Menu.hpp"

void MainController::runGame(bool debugMode) {
    MakeBoard makeBoard;
    DrawBoard drawBoard(window);
    Jeu jeu;
    BoardController controller(makeBoard, drawBoard, window, jeu, {menu.isWhiteAI(),menu.isRedAI(),menu.isBlackAI()}, debugMode);
    controller.run();
}

void MainController::run(){
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if(currentState == GameState::GAME){
                runGame(menu.isDebugModeButtonClicked());
                menu.setDebugModeButtonClicked(false);
                setGameState(GameState::MENU);
            }
            else if (currentState == GameState::MENU) {
                if (menu.isPlayButtonClicked()) {
                    setGameState(GameState::GAME);
                    menu.setPlayButtonClicked(false);
                }
                if(menu.isDebugModeButtonClicked()){
                    setGameState(GameState::GAME);
                }
                menu.handleEvent(event, window);
            }
        }
        if (currentState == GameState::MENU) {
            float deltaTime = clock.restart().asSeconds();
            menu.update(deltaTime);
            menu.render(window);
        }
    }
}