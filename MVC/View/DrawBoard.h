#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "Makeboard.h"


class DrawBoard {
    public:
        DrawBoard(sf::RenderWindow& window);
        void drawHexagons(const sf::ConvexShape& hex1, const sf::ConvexShape& hex2);
        void drawBoard(const std::vector<std::vector<sf::ConvexShape>>& matrices);
        void drawPieces(const std::vector<PieceImage>& white, const std::vector<PieceImage>& red, const std::vector<PieceImage>& black);
        void drawLines(const std::vector<std::array<sf::Vertex, 2>>& lines);
        void drawText(const std::vector<sf::Text>& texts);
        void drawTextGame(sf::Text& text);
        void drawBackButton(const sf::RectangleShape& button, const sf::Text& text);
        void changeColorTileDark(sf::ConvexShape& losange);
        void changeColorTileBright(sf::ConvexShape& losange);
        void loadPromotionTextures();
        void drawChoice(int camp);
        void clear();
        void display();
        std::vector<std::pair<sf::RectangleShape, int>> promotionChoix;
        sf::Texture& getPromotionTexture(int index, int camp) {
            if(camp==0){
                return texturesPromotionWhite[index];
            }
            else if(camp==1){
                return texturesPromotionRed[index];
            }
            else{
                return texturesPromotionBlack[index];
            }
        }
    private:
        sf::RenderWindow& window;
        std::vector<sf::Texture> texturesPromotionWhite;
        std::vector<sf::Texture> texturesPromotionRed;
        std::vector<sf::Texture> texturesPromotionBlack;
    };
    
#endif
