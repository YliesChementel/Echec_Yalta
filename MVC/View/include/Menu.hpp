/**
 * @file Menu.hpp
 * @brief Définition des classes pour l'interface du menu principal du jeu d'échecs Yalta
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "FallingPiece.hpp"

/**
 * @class Button
 * @brief Classe représentant un bouton interactif dans l'interface
 * 
 * Cette classe gère l'affichage et l'interaction avec un bouton rectangulaire
 * contenant du texte. Elle utilise SFML pour le rendu graphique.
 */
class Button {
public:
    /**
     * @brief Constructeur du bouton
     * @param x Position X du bouton
     * @param y Position Y du bouton
     * @param label Texte affiché sur le bouton
     * @param fontSize Taille de la police du texte
     */
    Button(float x, float y, const std::string& label, int fontSize) {
        button.setSize(sf::Vector2f(200.f, 50.f));
        button.setPosition(x, y);
        sf::Color beige(0xEE, 0xCF, 0xA1);
        button.setFillColor(beige);
        button.setOutlineThickness(3);
        button.setOutlineColor(sf::Color::Black);

        font.loadFromFile("resources/font/arial.ttf"); 
        text.setFont(font);
        //text.setStyle(sf::Text::Bold);
        text.setString(label);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + 10);
    }

    /**
     * @brief Modifie la position du bouton
     * @param x Nouvelle position X
     * @param y Nouvelle position Y
     */
    void setPosition(float x, float y) {
        button.setPosition(x, y);
        text.setPosition(x + 10, y + 10);
    }

    /**
     * @brief Modifie la taille du bouton
     * @param size1 Largeur du bouton
     * @param size2 Hauteur du bouton
     */
    void setSize(float size1, float size2) {
        button.setSize(sf::Vector2f(size1, size2));
    }

    /**
     * @brief Modifie la couleur de remplissage du bouton
     * @param color Nouvelle couleur
     */
    void setColor(sf::Color color) {
        button.setFillColor(color);
    }

    /**
     * @brief Dessine le bouton dans la fenêtre
     * @param window Fenêtre de rendu SFML
     */
    void draw(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }

    /**
     * @brief Vérifie si le bouton a été cliqué
     * @param mousePos Position de la souris
     * @return true si le bouton a été cliqué, false sinon
     */
    bool isClicked(sf::Vector2i mousePos) {
        return button.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

private:
    sf::RectangleShape button;  ///< Forme rectangulaire du bouton
    sf::Text text;             ///< Texte affiché sur le bouton
    sf::Font font;             ///< Police utilisée pour le texte
};

/**
 * @class Checkbox
 * @brief Classe représentant une case à cocher avec une icône
 * 
 * Cette classe gère l'affichage et l'interaction avec une case à cocher
 * accompagnée d'une icône. Elle utilise SFML pour le rendu graphique.
 */
class Checkbox {
public:
    /**
     * @brief Constructeur de la case à cocher
     * @param x Position X de la case
     * @param y Position Y de la case
     * @param texturePath Chemin vers l'image de l'icône
     * @param fontSize Taille de la police (non utilisée)
     */
    Checkbox(float x, float y, const std::string& texturePath, int fontSize) {
        box.setSize(sf::Vector2f(20.f, 20.f));
        box.setPosition(x, y);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Black);

        if (!texture.loadFromFile(texturePath)) {
            std::cout << "Erreur chargement texture : " << texturePath << "\n";
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y + 25);
        sprite.setScale(0.09f, 0.09f);
    }

    /**
     * @brief Modifie la position de la case à cocher
     * @param x Nouvelle position X
     * @param y Nouvelle position Y
     */
    void setPosition(float x, float y) {
        box.setPosition(x, y);
        sprite.setPosition(x, y + 25);
    }

    /**
     * @brief Dessine la case à cocher dans la fenêtre
     * @param window Fenêtre de rendu SFML
     */
    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(sprite);
    }

    /**
     * @brief Vérifie si la case a été cliquée
     * @param mousePos Position de la souris
     * @return true si la case a été cliquée, false sinon
     */
    bool isClicked(sf::Vector2i mousePos) {
        return box.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    /**
     * @brief Bascule l'état de la case à cocher
     */
    void toggle() {
        isChecked = !isChecked;
        box.setFillColor(isChecked ? sf::Color::Black : sf::Color::White);
        box.setOutlineColor(isChecked ? sf::Color::White : sf::Color::Black);
    }

    /**
     * @brief Obtient l'état actuel de la case à cocher
     * @return true si la case est cochée, false sinon
     */
    bool getState() const {
        return isChecked;
    }

private:
    sf::RectangleShape box;    ///< Forme rectangulaire de la case
    sf::Sprite sprite;         ///< Sprite de l'icône
    sf::Texture texture;       ///< Texture de l'icône
    bool isChecked = false;    ///< État de la case à cocher
};

/**
 * @class Menu
 * @brief Classe principale gérant l'interface du menu
 * 
 * Cette classe gère l'ensemble des éléments de l'interface du menu principal,
 * incluant les boutons, les cases à cocher pour la sélection des joueurs IA,
 * et l'animation des pièces tombantes.
 */
class Menu {
    public:
        /**
         * @brief Constructeur du menu
         * Initialise tous les éléments de l'interface et charge les textures
         */
        Menu();

        /**
         * @brief Gère les événements de l'interface
         * @param event Événement SFML à traiter
         * @param window Fenêtre de rendu SFML
         */
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);

        /**
         * @brief Met à jour l'état du menu
         * @param deltaTime Temps écoulé depuis la dernière mise à jour
         */
        void update(float deltaTime);

        /**
         * @brief Dessine le menu dans la fenêtre
         * @param window Fenêtre de rendu SFML
         */
        void render(sf::RenderWindow& window);

        /**
         * @brief Vérifie si le bouton Jouer a été cliqué
         * @return true si le bouton a été cliqué, false sinon
         */
        bool isPlayButtonClicked();

        /**
         * @brief Vérifie si le bouton Mode Debug a été cliqué
         * @return true si le bouton a été cliqué, false sinon
         */
        bool isDebugModeButtonClicked();

        /**
         * @brief Modifie l'état du bouton Jouer
         * @param clicked Nouvel état du bouton
         */
        void setPlayButtonClicked(bool clicked) { playButtonClicked = clicked; }

        /**
         * @brief Modifie l'état du bouton Mode Debug
         * @param clicked Nouvel état du bouton
         */
        void setDebugModeButtonClicked(bool clicked) { debugModeButtonClicked = clicked; }

        /**
         * @brief Initialise les pièces tombantes
         * Charge les textures et crée les pièces pour l'animation
         */
        void makePieces();

        /**
         * @brief Vérifie si le joueur blanc est contrôlé par l'IA
         * @return true si le joueur blanc est une IA, false sinon
         */
        bool isWhiteAI() const { return whiteAICheckbox.getState(); }

        /**
         * @brief Vérifie si le joueur rouge est contrôlé par l'IA
         * @return true si le joueur rouge est une IA, false sinon
         */
        bool isRedAI() const { return redAICheckbox.getState(); }

        /**
         * @brief Vérifie si le joueur noir est contrôlé par l'IA
         * @return true si le joueur noir est une IA, false sinon
         */
        bool isBlackAI() const { return blackAICheckbox.getState(); }

    private:
        sf::Font font;                     ///< Police utilisée pour le texte
        Button title;                      ///< Titre du jeu
        Button playButton;                 ///< Bouton pour démarrer la partie
        Button quitButton;                 ///< Bouton pour quitter
        Button frameCheckbox;              ///< Cadre pour les cases à cocher IA
        Button debugModeButton;            ///< Bouton pour activer le mode debug
        Checkbox whiteAICheckbox;          ///< Case à cocher pour l'IA blanche
        Checkbox redAICheckbox;            ///< Case à cocher pour l'IA rouge
        Checkbox blackAICheckbox;          ///< Case à cocher pour l'IA noire
        bool playButtonClicked = false;    ///< État du bouton Jouer
        bool debugModeButtonClicked = false; ///< État du bouton Mode Debug

        std::vector<sf::Texture> pieceTextures;     ///< Textures des pièces
        std::vector<FallingPiece> fallingPieces;    ///< Pièces pour l'animation
        std::vector<std::string> piecePaths = {     ///< Chemins vers les textures
        "resources/images/WhiteRook.png",
        "resources/images/WhiteRook.png",
        "resources/images/WhiteKnight.png",
        "resources/images/WhiteKnight.png",
        "resources/images/WhiteBishop.png",
        "resources/images/WhiteBishop.png",
        "resources/images/WhiteQueen.png",
        "resources/images/WhiteKing.png",
        "resources/images/WhitePawn.png",
        "resources/images/BlackRook.png",
        "resources/images/BlackRook.png",
        "resources/images/BlackKnight.png",
        "resources/images/BlackKnight.png",
        "resources/images/BlackBishop.png",
        "resources/images/BlackBishop.png",
        "resources/images/BlackQueen.png",
        "resources/images/BlackKing.png",
        "resources/images/BlackPawn.png",
        "resources/images/RedRook.png",
        "resources/images/RedRook.png",
        "resources/images/RedKnight.png",
        "resources/images/RedKnight.png",
        "resources/images/RedBishop.png",
        "resources/images/RedBishop.png",
        "resources/images/RedQueen.png",
        "resources/images/RedKing.png",
        "resources/images/RedPawn.png"
    };
};

#endif
