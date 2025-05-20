#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "FallingPiece.h"

class Button {
public:
    Button(float x, float y, const std::string& label, int fontSize) {
        button.setSize(sf::Vector2f(200.f, 50.f));
        button.setPosition(x, y);
        sf::Color beige(0xEE, 0xCF, 0xA1);
        button.setFillColor(beige);

        font.loadFromFile("resources/font/arial.ttf"); 
        text.setFont(font);
        //text.setStyle(sf::Text::Bold);
        text.setString(label);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + 10);
    }


    void setPosition(float x, float y) {
        button.setPosition(x, y);
        text.setPosition(x + 10, y + 10);
    }

    void setSize(float size1, float size2) {
        button.setSize(sf::Vector2f(size1, size2));
    }

    void setColor(sf::Color color) {
        button.setFillColor(color);
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

class Checkbox {
public:
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

    void setPosition(float x, float y) {
        box.setPosition(x, y);
        sprite.setPosition(x, y + 25);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(sprite);
    }

    bool isClicked(sf::Vector2i mousePos) {
        return box.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    void toggle() {
        isChecked = !isChecked;
        box.setFillColor(isChecked ? sf::Color(0xEE, 0xCF, 0xA1) : sf::Color::White);
    }

    bool getState() const {
        return isChecked;
    }

private:
    sf::RectangleShape box;
    sf::Sprite sprite;
    sf::Texture texture;
    bool isChecked = false;
};

class Menu {
    public:
        Menu();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(float deltaTime);
        void render(sf::RenderWindow& window);
        bool isPlayButtonClicked();
        void setPlayButtonClicked(bool clicked) { playButtonClicked = clicked; }

        void makePieces();
        bool isWhiteAI() const { return whiteAICheckbox.getState(); }
        bool isRedAI() const { return redAICheckbox.getState(); }
        bool isBlackAI() const { return blackAICheckbox.getState(); }

    private:
        sf::Font font;
        Button title;
        Button playButton;
        Button quitButton;
        Button frameCheckbox;
        Checkbox whiteAICheckbox;
        Checkbox redAICheckbox;
        Checkbox blackAICheckbox;
        bool playButtonClicked = false;

        std::vector<sf::Texture> pieceTextures;
        std::vector<FallingPiece> fallingPieces;
        std::vector<std::string> piecePaths = {
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
