#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>

class BoardView {
    public:
        BoardView(sf::RenderWindow& window);
        void drawHexagons(const sf::ConvexShape& hex1, const sf::ConvexShape& hex2);
        void drawBoard(const std::vector<std::vector<sf::ConvexShape>>& matrices);
        void drawPieces(const std::vector<sf::Sprite>& white, const std::vector<sf::Sprite>& red, const std::vector<sf::Sprite>& black);
        void drawLines(const std::vector<std::array<sf::Vertex, 2>>& lines);
        void drawText(const std::vector<sf::Text>& texts);
        void clear();
        void display();
    
    private:
        sf::RenderWindow& window;
    };
    
#endif
