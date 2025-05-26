/**
 * @file MainController.cpp
 * @brief Implémentation du contrôleur principal du jeu
 */

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

/**
 * @brief Lance une partie de jeu avec les paramètres spécifiés
 * @param debugMode Indique si le mode debug est activé
 */
void MainController::runGame(bool debugMode,bool isAiDifficult) {
    MakeBoard makeBoard;
    DrawBoard drawBoard(window);
    Jeu jeu;
    // Initialise le contrôleur du plateau avec les paramètres du menu
    BoardController controller(makeBoard, drawBoard, window, jeu, {menu.isWhiteAI(),menu.isRedAI(),menu.isBlackAI()}, debugMode, isAiDifficult);
    controller.run();
}

/**
 * @brief Boucle principale du jeu gérant les événements et les états
 */
void MainController::run(){
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Gestion de la fermeture de la fenêtre
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Gestion de l'état de jeu
            else if(currentState == GameState::GAME){
                runGame(menu.isDebugModeButtonClicked(),menu.isHardAI());
                menu.setDebugModeButtonClicked(false);
                setGameState(GameState::MENU);
            }
            // Gestion de l'état du menu
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
        // Mise à jour et rendu du menu si on est dans l'état menu
        if (currentState == GameState::MENU) {
            float deltaTime = clock.restart().asSeconds();
            menu.update(deltaTime);
            menu.render(window);
        }
    }
}