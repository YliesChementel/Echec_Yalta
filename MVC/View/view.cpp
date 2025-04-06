#include "View.hpp"
#include <iterator>
#include <vector>
#include <iostream>

BoardView::BoardView(sf::RenderWindow& win) : window(win) {}

void BoardView::clear() {
    this->window.clear(sf::Color::White);
}

void BoardView::display() {
    window.display();
}

void BoardView::drawHexagons(const sf::ConvexShape& hex1, const sf::ConvexShape& hex2) {
    window.draw(hex1);
    window.draw(hex2);
}

void BoardView::drawLines(const std::vector<std::array<sf::Vertex, 2>>& lines) {
    for (const auto& line : lines) {
        window.draw(line.data(), 2, sf::Lines);
    }
}

void BoardView::drawText(const std::vector<sf::Text>& texts) {
    for (const auto& text : texts) {
        window.draw(text);
    }
}

void BoardView::drawBoard(const std::vector<std::vector<sf::ConvexShape>>& matrices) {
    for (const auto& matrice : matrices) {
        for (const auto& losange : matrice) {
            window.draw(losange);
        }
    }
}

void BoardView::drawPieces(const std::vector<PieceImage>& whites, const std::vector<PieceImage>& blacks, const std::vector<PieceImage>& reds) {
    for (const auto& piece : whites) {
        window.draw(piece.getSprite());
    }
    for (const auto& piece : blacks) {
        window.draw(piece.getSprite());
    }
    for (const auto& piece : reds) {
        window.draw(piece.getSprite());
    }
}

void BoardView::changeColorTile(std::vector<sf::ConvexShape>& losanges) {
    for (auto& losange : losanges) {
        sf::Color actuel = losange.getFillColor();

        // Appliquer un filtre noir
        sf::Color darkerColor(
            actuel.r * 0.5, actuel.g * 0.5, actuel.b * 0.5, actuel.a
        );

        losange.setFillColor(darkerColor);
    }
}

// Dans View/view.cpp
void BoardView::changeColorTileTest(sf::ConvexShape& losange) {
    sf::Color actuel = losange.getFillColor();

    // Appliquer un filtre noir
    sf::Color darkerColor(
        actuel.r * 2, actuel.g * 2, actuel.b * 2, actuel.a
    );

    losange.setFillColor(darkerColor);
}


void BoardView::changeColorTile2(std::vector<sf::ConvexShape>& losanges) {
    for (auto& losange : losanges) {
        sf::Color actuel = losange.getFillColor();

        // Appliquer un filtre noir
        sf::Color darkerColor(
            actuel.r * 2, actuel.g * 2, actuel.b * 2, actuel.a
        );

        losange.setFillColor(darkerColor);
    }
}