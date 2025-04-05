// Model.hpp
#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <array>

class Board {
    private:
        sf::ConvexShape hexagon;
        sf::ConvexShape hexagon2;
        std::vector<std::array<sf::Vertex, 2>> lines;
        sf::Font font;
        std::vector<sf::Text> coordText;
        std::vector<sf::ConvexShape> matrice1;
        std::vector<sf::ConvexShape> matrice2;
        std::vector<sf::ConvexShape> matrice3;
        std::vector<sf::ConvexShape> matrice4;
        std::vector<sf::ConvexShape> matrice5;
        std::vector<sf::ConvexShape> matrice6;
        std::vector<sf::Sprite> WhitePieces;
        std::vector<sf::Texture> texturesWhite;
        std::vector<sf::Sprite> BlackPieces;
        std::vector<sf::Texture> texturesBlack;
        std::vector<sf::Sprite> RedPieces;
        std::vector<sf::Texture> texturesRed;
public:
    Board();
    
    sf::Vector2f milieu(const sf::Vector2f& p1, const sf::Vector2f& p2);

    std::array<sf::Vertex, 2> createLine(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color);

    std::vector<sf::Vector2f> createMatrixLines(const sf::Vector2f& center, const sf::Vector2f& milieu1,const sf::Vector2f& milieu2, const sf::Vector2f& point1,const sf::Vector2f& point2, const sf::Vector2f& point3);

    sf::ConvexShape createLosange(const sf::Vector2f& p1, const sf::Vector2f& p2,const sf::Vector2f& p3, const sf::Vector2f& p4,sf::Color fill, sf::Color outline);

    std::vector<sf::ConvexShape> createMatrixLosange(const sf::Vector2f& center, const std::vector<sf::Vector2f>& mat_lines,const sf::Vector2f& point, const sf::Vector2f& milieu1, const sf::Vector2f& milieu2,sf::Color color1, sf::Color color2);

    sf::Text createText(const std::string& textStr, const sf::Vector2f& startPosition, unsigned int characterSize, sf::Color color, sf::Font& font);

    std::vector<sf::Texture> loadTextures(const std::vector<std::string>& paths);

    sf::Vector2f calculerCentreLosange(const sf::ConvexShape& shape);

    sf::Sprite chargerImageDansLosange(const sf::ConvexShape& shape, float scaleX, float scaleY, sf::Texture& texture);

    std::vector<sf::Sprite> CreerPiece( const std::vector<sf::ConvexShape> matriceA, const std::vector<sf::ConvexShape> matriceB,  std::vector<sf::Texture>& textures);

    bool PieceDansMatrice(const sf::Vector2f& point, const std::vector<sf::ConvexShape> matrice);

    bool PieceDansLosange(const sf::ConvexShape& shape, const sf::Vector2f& point);
    
    void PlacementPiece(int& selectedPieceIndex,const sf::ConvexShape losange,std::vector<sf::Sprite>& WhitePieces,std::vector<sf::Sprite>& BlackPieces,std::vector<sf::Sprite>& RedPieces);

    const sf::ConvexShape& getHexagon() const { return hexagon; }
    const sf::ConvexShape& getHexagon2() const { return hexagon2; }
    const std::vector<std::array<sf::Vertex, 2>>& getLines() const { return lines; }
    const std::vector<sf::Text>& getCoordText() const { return coordText; }
    const std::vector<sf::ConvexShape>& getMatrice1() const { return matrice1; }
    const std::vector<sf::ConvexShape>& getMatrice2() const { return matrice2; }
    const std::vector<sf::ConvexShape>& getMatrice3() const { return matrice3; }
    const std::vector<sf::ConvexShape>& getMatrice4() const { return matrice4; }
    const std::vector<sf::ConvexShape>& getMatrice5() const { return matrice5; }
    const std::vector<sf::ConvexShape>& getMatrice6() const { return matrice6; }
    std::vector<sf::Sprite>& getWhitePieces() { return WhitePieces; }
    std::vector<sf::Sprite>& getBlackPieces() { return BlackPieces; }
    std::vector<sf::Sprite>& getRedPieces() { return RedPieces; }
};
#endif // MODEL_HPP
