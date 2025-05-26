/**
 * @file Menu.cpp
 * @brief Implémentation de la classe Menu pour l'interface du jeu d'échecs Yalta
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "../include/Menu.hpp"
#include "../include/MakeBoard.hpp"
#include "../include/DrawBoard.hpp"
#include "../../Controller/include/BoardController.hpp"
#include <algorithm>

/**
 * @brief Constructeur de la classe Menu
 * 
 * Initialise tous les éléments de l'interface :
 * - Boutons (Jouer, Quitter, Mode Debug)
 * - Titre du jeu
 * - Cases à cocher pour la sélection des joueurs IA
 * - Animation des pièces tombantes
 */
Menu::Menu()
    : playButton(0, 0, "Jouer",24),       
      quitButton(0, 0, "Quitter",24), 
      frameCheckbox(0, 0, "Choix IA", 20),  
      frameDifficultyCheckbox(0, 0, "Difficulté IA", 20),
      title(0, 0, "Jeu d'echec Yalta",50),
      whiteAICheckbox(0, 0, "resources/images/WhiteKing.png", 20),
      redAICheckbox(0, 0, "resources/images/RedKing.png", 20),
      blackAICheckbox(0, 0, "resources/images/BlackKing.png", 20),
      easyAICheckbox(0, 0, "resources/images/WhitePawn.png", 20),
      hardAICheckbox(0, 0, "resources/images/BlackQueen.png", 20), 
      debugModeButton(1010, 940, "Debug Mode", 20)
{
    // Dimensions de la fenêtre et des éléments
    float windowWidth = 1150;
    float windowHeight = 1000;
    float buttonWidth = 200;
    float buttonHeight = 50;
    float verticalSpacing = 25;  

    // Calcul de la hauteur totale des boutons pour le centrage vertical
    float totalButtonsHeight = 4 * buttonHeight + 3 * verticalSpacing; // Augmenté pour tenir compte des nouvelles cases
    float startY = (windowHeight - totalButtonsHeight) / 2;

    // Positionnement des éléments
    title.setPosition((1150 - 410) / 2, 100);
    title.setSize(410,80);
    playButton.setPosition((1150 - buttonWidth) / 2, startY - verticalSpacing);
    
    // Positionnement des cases à cocher pour les IA
    float checkboxX = (1150 - buttonWidth) / 2 +15;
    float checkboxY = startY + buttonHeight + verticalSpacing;
    
    whiteAICheckbox.setPosition(checkboxX, checkboxY);
    redAICheckbox.setPosition(checkboxX + 75, checkboxY);
    blackAICheckbox.setPosition(checkboxX + 75*2, checkboxY);

    frameCheckbox.setPosition(checkboxX - 15, checkboxY - 40);
    frameCheckbox.setSize(200,100);

    // Positionnement des cases à cocher pour la difficulté
    float difficultyCheckboxY = checkboxY + 80; // Augmenté l'espacement
    easyAICheckbox.setPosition(checkboxX, difficultyCheckboxY+30);
    hardAICheckbox.setPosition(checkboxX + 75, difficultyCheckboxY+30);

    frameDifficultyCheckbox.setPosition(checkboxX - 15, difficultyCheckboxY-10);
    frameDifficultyCheckbox.setSize(200,100);

    easyAICheckbox.toggle();

    // Positionnement du bouton quitter plus bas
    quitButton.setPosition((1150 - buttonWidth) / 2, difficultyCheckboxY + 100);
    debugModeButton.setSize(135, 50);

    // Initialisation des pièces tombantes
    makePieces();
}

/**
 * @brief Met à jour l'état du menu
 * 
 * Met à jour l'animation des pièces tombantes et les trie
 * par ordre d'échelle pour un rendu correct
 * 
 * @param deltaTime Temps écoulé depuis la dernière mise à jour
 */
void Menu::update(float deltaTime) {
    // Mise à jour de l'animation des pièces
    for (auto& piece : fallingPieces) {
        piece.update(deltaTime);
    }

    // Tri des pièces par ordre d'échelle pour le rendu
    std::sort(fallingPieces.begin(), fallingPieces.end(), 
        [](const FallingPiece& a, const FallingPiece& b) {
            return a.getScale() < b.getScale();
        });
}

/**
 * @brief Gère les événements de l'interface
 * 
 * Traite les clics de souris sur les différents éléments :
 * - Bouton Jouer : démarre la partie
 * - Bouton Quitter : ferme la fenêtre
 * - Cases à cocher : active/désactive les IA
 * - Bouton Mode Debug : active le mode debug
 * 
 * @param event Événement SFML à traiter
 * @param window Fenêtre de rendu SFML
 */
void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Gestion des clics sur les boutons
        if (playButton.isClicked(mousePos)) { 
            playButtonClicked = true;
        }

        if (quitButton.isClicked(mousePos)) {
            window.close();
        }

        // Gestion des clics sur les cases à cocher
        if (whiteAICheckbox.isClicked(mousePos)) {
            whiteAICheckbox.toggle();
        }
        if (redAICheckbox.isClicked(mousePos)) {
            redAICheckbox.toggle();
        }
        if (blackAICheckbox.isClicked(mousePos)) {
            blackAICheckbox.toggle();
        }
        if (easyAICheckbox.isClicked(mousePos)) {
            if(!easyAICheckbox.getState()){
                easyAICheckbox.toggle();
                if (hardAICheckbox.getState()) {
                    hardAICheckbox.toggle(); // Désactive l'autre option
                }
            }
        }
        if (hardAICheckbox.isClicked(mousePos)) {
            if(!hardAICheckbox.getState()){
                hardAICheckbox.toggle();
                if (easyAICheckbox.getState()) {
                    easyAICheckbox.toggle(); // Désactive l'autre option
                }
            }
        }
        if(debugModeButton.isClicked(mousePos)){
            debugModeButtonClicked = true;
        }
    }
}

/**
 * @brief Dessine le menu dans la fenêtre
 * 
 * Affiche tous les éléments de l'interface :
 * - Fond de la fenêtre
 * - Pièces tombantes
 * - Titre
 * - Boutons
 * - Cases à cocher
 * 
 * @param window Fenêtre de rendu SFML
 */
void Menu::render(sf::RenderWindow& window) {
    // Effacement de l'écran avec une couleur de fond
    window.clear(sf::Color(48, 46, 43));

    // Affichage des pièces tombantes
    for (auto& piece : fallingPieces) {
        piece.draw(window);
    }

    // Affichage des éléments de l'interface
    title.draw(window);
    playButton.draw(window);
    quitButton.draw(window);
    frameCheckbox.draw(window);
    frameDifficultyCheckbox.draw(window);
    whiteAICheckbox.draw(window);
    redAICheckbox.draw(window);
    blackAICheckbox.draw(window);
    easyAICheckbox.draw(window);
    hardAICheckbox.draw(window);
    debugModeButton.draw(window); 

    // Mise à jour de l'affichage
    window.display();
}

/**
 * @brief Vérifie si le bouton Jouer a été cliqué
 * @return true si le bouton a été cliqué, false sinon
 */
bool Menu::isPlayButtonClicked() {
    return playButtonClicked;
}

/**
 * @brief Vérifie si le bouton Mode Debug a été cliqué
 * @return true si le bouton a été cliqué, false sinon
 */
bool Menu::isDebugModeButtonClicked() {
    return debugModeButtonClicked;
}

/**
 * @brief Initialise les pièces tombantes
 * 
 * Charge les textures des pièces et crée les pièces
 * pour l'animation de fond du menu
 */
void Menu::makePieces() {
    // Chargement des textures
    for (const auto& path : piecePaths) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            pieceTextures.push_back(texture);
        } else {
            std::cout << "Erreur chargement texture : " << path << "\n";
        }
    }

    // Création des pièces tombantes avec des positions aléatoires
    for (int i = 0; i < 27; ++i) {
        float x = static_cast<float>(rand() % 1200);
        fallingPieces.emplace_back(pieceTextures[i], x, 100.f);  
    }
}