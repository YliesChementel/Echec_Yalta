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

void BoardView::drawPieces(const std::vector<sf::Sprite>& whites, const std::vector<sf::Sprite>& reds, const std::vector<sf::Sprite>& blacks) {
    for (const auto& piece : whites) {
        window.draw(piece);
    }
    for (const auto& piece : reds) {
        window.draw(piece);
    }
    for (const auto& piece : blacks) {
        window.draw(piece);
    }
}
