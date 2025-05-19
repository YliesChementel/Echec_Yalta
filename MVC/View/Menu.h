#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

class Button {
public:
    Button(float x, float y, const std::string& label) {
        button.setSize(sf::Vector2f(200.f, 50.f));
        button.setPosition(x, y);
        button.setFillColor(sf::Color::Blue);

        font.loadFromFile("resources/font/arial.ttf"); 
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(x + 10, y + 10);
    }


    void setPosition(float x, float y) {
        button.setPosition(x, y);
        text.setPosition(x + 10, y + 10);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }

    bool isClicked(sf::Vector2i mousePos) {
        return button.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

private:
    sf::RectangleShape button;
    sf::Text text;
    sf::Font font;
};


class Menu {
    public:
        Menu();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update();
        void render(sf::RenderWindow& window);
        bool isPlayButtonClicked(const sf::Event& event, sf::RenderWindow& window);

    private:
        sf::Font font;
        sf::Text title;
        Button playButton;
        Button playAIButton;
        Button quitButton;
        bool playButtonClicked = false;
};

#endif // MENU_H
