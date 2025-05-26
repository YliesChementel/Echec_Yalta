/**
 * @file State.hpp
 * @brief Classe de base abstraite définissant l'interface pour tous les états du jeu
 */

#ifndef STATE_HPP
#define STATE_HPP

#include "BoardController.hpp"

class BoardController;

class State {
public:
    virtual ~State() = default;

    /**
     * @brief Gère les événements de clic de souris
     * @param controller Le contrôleur du plateau
     * @param event L'événement SFML
     */
    virtual void handleMousePressed(BoardController& controller, const sf::Event& event) = 0;

    /**
     * @brief Gère les événements de mouvement de souris
     * @param controller Le contrôleur du plateau
     * @param event L'événement SFML
     */
    virtual void handleMouseMoved(BoardController& controller, const sf::Event& event) = 0;

    /**
     * @brief Gère les événements de relâchement de souris
     * @param controller Le contrôleur du plateau
     * @param event L'événement SFML
     */
    virtual void handleMouseReleased(BoardController& controller, const sf::Event& event) = 0;

    /**
     * @brief Met à jour la logique de l'état
     * @param controller Le contrôleur du plateau
     * @param deltaTime Le temps écoulé depuis la dernière mise à jour
     */
    virtual void update(BoardController& controller, float deltaTime) = 0;

    /**
     * @brief Dessine l'état actuel
     * @param controller Le contrôleur du plateau
     */
    virtual void render(BoardController& controller) = 0;

    /**
     * @brief Retourne le nom de l'état
     * @return Le nom de l'état sous forme de chaîne de caractères
     */
    virtual std::string getStateName() const = 0;
};

#endif