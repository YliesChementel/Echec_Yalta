#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Menu.h"
#include "MakeBoard.h"
#include "DrawBoard.h"
#include "BoardController.h"


Menu::Menu()
    : playButton(0, 0, "Jouer"),       
      playAIButton(0, 0, "AI"),         
      quitButton(0, 0, "Quitter")        
{
    if (!font.loadFromFile("resources/font/arial.ttf")) {
        std::cout << "Erreur de chargement de la police\n"; 
    }

    title.setFont(font);
    title.setString("Jeu d'echec Yalta");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition((1150 - title.getLocalBounds().width) / 2, 100);  

    float windowWidth = 1150;
    float windowHeight = 1000;
    float buttonWidth = 200;
    float buttonHeight = 50;
    float verticalSpacing = 25;  

    float totalButtonsHeight = 3 * buttonHeight + 2 * verticalSpacing;

    float startY = (windowHeight - totalButtonsHeight) / 2;

    playButton.setPosition((1150 - buttonWidth) / 2, startY);
    playAIButton.setPosition((1150 - buttonWidth) / 2, startY + buttonHeight + verticalSpacing);
    quitButton.setPosition((1150 - buttonWidth) / 2, startY + 2 * (buttonHeight + verticalSpacing));
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
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.clear(sf::Color(48, 46, 43));
    window.draw(title);
    playButton.draw(window);
    playAIButton.draw(window);
    quitButton.draw(window);
    window.display();
}

bool Menu::isPlayButtonClicked(const sf::Event& event, sf::RenderWindow& window) {
    return playButtonClicked;
}



