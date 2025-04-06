#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "model.hpp"


class BoardView {
    public:
        BoardView(sf::RenderWindow& window);
        void drawHexagons(const sf::ConvexShape& hex1, const sf::ConvexShape& hex2);
        void drawBoard(const std::vector<std::vector<sf::ConvexShape>>& matrices);
        void drawPieces(const std::vector<PieceImage>& white, const std::vector<PieceImage>& red, const std::vector<PieceImage>& black);
        void drawLines(const std::vector<std::array<sf::Vertex, 2>>& lines);
        void drawText(const std::vector<sf::Text>& texts);
        void changeColorTile(std::vector<sf::ConvexShape>& losanges);
        void changeColorTile2(std::vector<sf::ConvexShape>& losanges);
        void changeColorTileTest(sf::ConvexShape& losange);
        void clear();
        void display();
    
    private:
        sf::RenderWindow& window;
    };
    
#endif
