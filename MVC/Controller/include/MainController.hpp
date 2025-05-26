/**
 * @file MainController.hpp
 * @brief Contrôleur principal gérant les états du jeu et la fenêtre principale
 */

#ifndef MAINC_CONTROLLER_HPP
#define MAINC_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../View/include/Menu.hpp"


class MainController {
    public:
        /**
         * @brief Énumération des états possibles du jeu
         */
        enum class GameState {
            MENU,   ///< État du menu principal
            GAME    ///< État de jeu actif
        };

        /**
         * @brief Constructeur initialisant la fenêtre et l'état du jeu
         */
        MainController() : currentState(GameState::MENU), menu(), settings() {
            settings.antialiasingLevel = 8;
            window.create(sf::VideoMode(1150, 1000), "Echec Yalta", sf::Style::Default, settings);
        }
        /**
         * @brief Lance la boucle principale du jeu
         */
        void run();
        /**
         * @brief Change l'état actuel du jeu
         * @param state Le nouvel état à définir
         */
        void setGameState(GameState state) { currentState = state; }
        /**
         * @brief Récupère l'état actuel du jeu
         * @return L'état actuel du jeu
         */
        GameState getGameState() const { return currentState; }
        /**
         * @brief Lance une partie de jeu
         * @param debugMode Indique si le mode debug est activé
         */
        void runGame(bool debugMode);
        
    private:
        GameState currentState;           ///< État actuel du jeu
        sf::ContextSettings settings;     ///< Paramètres de la fenêtre
        sf::RenderWindow window;          ///< Fenêtre principale du jeu
        Menu menu;                        ///< Menu principal
};
#endif