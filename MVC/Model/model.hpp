// Model.hpp
#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <array>

class PieceImage {
    public:
        PieceImage(const sf::Sprite& sprite, const std::vector<int>& tilePositions, const std::string& camp)
            : sprite(sprite), tilePositions(tilePositions), camp(camp) {}
    
        sf::Sprite& getSprite() { return sprite; }  //  version pour modifier les pièces
        const sf::Sprite& getSprite() const { return sprite; }  // version sans modifier l'objet

        std::vector<int>& getTilePositions()  { return tilePositions; }
    
        void setSprite(const sf::Sprite& sprite) { this->sprite = sprite; }
        void setTilePositions(const std::vector<int>& tilePositions) { this->tilePositions = tilePositions; }
    
        void setPosition(const sf::Vector2f& position, const std::vector<int>& tilePosition) {
            sprite.setPosition(position);
            this->tilePositions==tilePosition;
        }
        std::string& getCamp(){
            return camp;
        }
        void setCamp(std::string camp){
            this->camp=camp;
        }
    
    private:
        sf::Sprite sprite;     
        std::vector<int> tilePositions;
        std::string camp;
};

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
        std::vector<PieceImage> WhitePieces;
        std::vector<sf::Texture> texturesWhite;
        std::vector<PieceImage> BlackPieces;
        std::vector<sf::Texture> texturesBlack;
        std::vector<PieceImage> RedPieces;
        std::vector<sf::Texture> texturesRed;

        sf::Text textGame;
        sf::Text textEchec;

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

    std::vector<PieceImage> CreerPiece(const std::vector<sf::ConvexShape> matriceA, const std::vector<sf::ConvexShape> matriceB, int positionMatriceA, int positionMatriceB, std::vector<sf::Texture>& textures,std::string camp);

    bool PieceDansMatrice(const sf::Vector2f& point, const std::vector<sf::ConvexShape> matrice);

    bool PieceDansLosange(const sf::ConvexShape& shape, const sf::Vector2f& point);
    
    void PlacementPiece(int& selectedPieceIndex, const sf::ConvexShape& losange, std::vector<PieceImage>& listePieces, int IndexMat,int IndexLos);

    void ReplacementPiece(int& selectedPieceIndex, int camp, int matriceIndex, std::vector<PieceImage>& pieces);

    int determineSubMatrix(int x, int y);
    int coordonneEnIndexDeLosange(int x, int y, int matrice);
    std::pair<int, int> indexEnCoordonneDePlateau(int index, int sousMatrice);


    const sf::ConvexShape& getHexagon() const { return hexagon; }
    const sf::ConvexShape& getHexagon2() const { return hexagon2; }
    const std::vector<std::array<sf::Vertex, 2>>& getLines() const { return lines; }
    const std::vector<sf::Text>& getCoordText() const { return coordText; }
    std::vector<sf::ConvexShape>& getMatrice(int index);
    std::vector<sf::ConvexShape>& getMatrice1()  { return matrice1; }
    std::vector<sf::ConvexShape>& getMatrice2()  { return matrice2; }
    std::vector<sf::ConvexShape>& getMatrice3()  { return matrice3; }
    std::vector<sf::ConvexShape>& getMatrice4()  { return matrice4; }
    std::vector<sf::ConvexShape>& getMatrice5()  { return matrice5; }
    std::vector<sf::ConvexShape>& getMatrice6()  { return matrice6; }
    std::vector<PieceImage>& getWhitePieces() { return WhitePieces; }
    std::vector<PieceImage>& getBlackPieces() { return BlackPieces; }
    std::vector<PieceImage>& getRedPieces() { return RedPieces; }

    sf::Text& getTextGame() { return textGame; }
    void setTextGame(std::string text) {
        textGame = createText(text, sf::Vector2f(350, 12), 28, sf::Color::Black, font);
    }
    sf::Text& getTextEchec() { return textEchec; }
    void setTextEchec(std::string text) {
        textEchec = createText(text, sf::Vector2f(350, 50), 28, sf::Color::Black, font);
    }
};
#endif // MODEL_HPP
