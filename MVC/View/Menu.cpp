#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "Menu.h"
#include "MakeBoard.h"
#include "DrawBoard.h"
#include "BoardController.h"


Menu::Menu()
    : playButton(0, 0, "Jouer",24),       
      quitButton(0, 0, "Quitter",24), 
      frameCheckbox(0, 0, "Choix IA", 20),  
      title(0, 0, "Jeu d'echec Yalta",50),
      whiteAICheckbox(0, 0, "resources/images/WhiteKing.png", 20),
      redAICheckbox(0, 0, "resources/images/RedKing.png", 20),
      blackAICheckbox(0, 0, "resources/images/BlackKing.png", 20)     
{

    float windowWidth = 1150;
    float windowHeight = 1000;
    float buttonWidth = 200;
    float buttonHeight = 50;
    float verticalSpacing = 25;  

    float totalButtonsHeight = 3 * buttonHeight + 2 * verticalSpacing;

    float startY = (windowHeight - totalButtonsHeight) / 2;

    title.setPosition((1150 - 410) / 2, 100);
    title.setSize(410,80);
    playButton.setPosition((1150 - buttonWidth) / 2, startY - verticalSpacing);
    
    float checkboxX = (1150 - buttonWidth) / 2 +15;
    float checkboxY = startY + buttonHeight + verticalSpacing;
    
    whiteAICheckbox.setPosition(checkboxX, checkboxY);
    redAICheckbox.setPosition(checkboxX + 75, checkboxY);
    blackAICheckbox.setPosition(checkboxX + 75*2, checkboxY);

    frameCheckbox.setPosition(checkboxX - 15, checkboxY - 40);
    frameCheckbox.setSize(200,100);

    quitButton.setPosition((1150 - buttonWidth) / 2, startY + 2 * (buttonHeight + verticalSpacing));

    makePieces();
}

void Menu::update(float deltaTime) {
    for (auto& piece : fallingPieces) {
        piece.update(deltaTime);
    }
}


void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (playButton.isClicked(mousePos)) { 
            playButtonClicked = true;
        }

        if (quitButton.isClicked(mousePos)) {
            window.close();
        }

        if (whiteAICheckbox.isClicked(mousePos)) {
            whiteAICheckbox.toggle();
        }
        if (redAICheckbox.isClicked(mousePos)) {
            redAICheckbox.toggle();
        }
        if (blackAICheckbox.isClicked(mousePos)) {
            blackAICheckbox.toggle();
        }
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.clear(sf::Color(48, 46, 43));
    for (auto& piece : fallingPieces) {
        piece.draw(window);
    }
    title.draw(window);
    playButton.draw(window);
    quitButton.draw(window);
    frameCheckbox.draw(window);
    whiteAICheckbox.draw(window);
    redAICheckbox.draw(window);
    blackAICheckbox.draw(window);
    window.display();
}

bool Menu::isPlayButtonClicked() {
    return playButtonClicked;
}

void Menu::makePieces() {
    for (const auto& path : piecePaths) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            pieceTextures.push_back(texture);
        } else {
            std::cout << "Erreur chargement texture : " << path << "\n";
        }
    }

    for (int i = 0; i < 27; ++i) {
        float x = static_cast<float>(rand() % 1200);
        fallingPieces.emplace_back(pieceTextures[i], x, 100.f);  
    }
}