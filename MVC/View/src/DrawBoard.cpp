#include "include/DrawBoard.hpp"
#include <iterator>
#include <vector>
#include <iostream>

DrawBoard::DrawBoard(sf::RenderWindow& win) : window(win) { loadPromotionTextures(); }

void DrawBoard::clear() {
    this->window.clear(sf::Color(48, 46, 43));
}

void DrawBoard::display() {
    window.display();
}

void DrawBoard::drawHexagons(const sf::ConvexShape& hex1, const sf::ConvexShape& hex2) {
    window.draw(hex1);
    window.draw(hex2);
}

void DrawBoard::drawLines(const std::vector<std::array<sf::Vertex, 2>>& lines) {
    for (const auto& line : lines) {
        window.draw(line.data(), 2, sf::Lines);
    }
}

void DrawBoard::drawText(const std::vector<sf::Text>& texts) {
    for (const auto& text : texts) {
        window.draw(text);
    }
}

void DrawBoard::drawTextGame(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    float x = (window.getSize().x - bounds.width) / 2.f - bounds.left;
    float y = text.getPosition().y;
    text.setPosition(x, y);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}


void DrawBoard::drawBoard(const std::vector<std::vector<sf::ConvexShape>>& matrices) {
    for (const auto& matrice : matrices) {
        for (const auto& losange : matrice) {
            window.draw(losange);
        }
    }
}

void DrawBoard::drawPieces(const std::vector<PieceImage>& whites, const std::vector<PieceImage>& blacks, const std::vector<PieceImage>& reds) {
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

void DrawBoard::changeColorTileDark(sf::ConvexShape& losange) {
    sf::Color actuel = losange.getFillColor();

    sf::Color darkerColor(
        actuel.r * 0.5, actuel.g * 0.5, actuel.b * 0.5, actuel.a
    );

    losange.setFillColor(darkerColor);
}

void DrawBoard::changeColorTileBright(sf::ConvexShape& losange) {
    sf::Color actuel = losange.getFillColor();

    sf::Color brighterColor(
        actuel.r * 2, actuel.g * 2, actuel.b * 2, actuel.a
    );

    losange.setFillColor(brighterColor);
}

std::pair<sf::RectangleShape, sf::Sprite> createImageSquare(sf::Texture& texture, const sf::Vector2f& position) {
    sf::RectangleShape square(sf::Vector2f(100, 100));
    square.setPosition(position);
    square.setFillColor(sf::Color::White);
    square.setOutlineThickness(2.f);
    square.setOutlineColor(sf::Color::Black);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(position);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setScale(100.f / bounds.width, 100.f / bounds.height);

    return {square, sprite};
}

void DrawBoard::drawChoice(int camp) {
    std::vector<sf::Texture> texturesPromotion;
    promotionChoix.clear();
    if(camp==0){
        texturesPromotion = texturesPromotionWhite;
    }
    else if(camp==1){
        texturesPromotion = texturesPromotionRed;
    }
    else{
        texturesPromotion = texturesPromotionBlack;
    }
    auto [squareQueen, spriteQueen] = createImageSquare(texturesPromotion[0], {0, 0});
    auto [squareBishop, spriteBishop] = createImageSquare(texturesPromotion[1], {100, 0});
    auto [squareKnight, spriteKnight] = createImageSquare(texturesPromotion[2], {0, 100});
    auto [squareRook, spriteRook] = createImageSquare(texturesPromotion[3], {100, 100});

    promotionChoix.push_back({squareQueen, 0});  // 0 = Queen
    promotionChoix.push_back({squareBishop, 1}); // 1 = Bishop
    promotionChoix.push_back({squareKnight, 2}); // 2 = Knight
    promotionChoix.push_back({squareRook, 3});   // 3 = Rook

    window.draw(squareQueen);  window.draw(spriteQueen);
    window.draw(squareBishop); window.draw(spriteBishop);
    window.draw(squareKnight); window.draw(spriteKnight);
    window.draw(squareRook);   window.draw(spriteRook);
}

void DrawBoard::loadPromotionTextures() {
    std::vector<std::string> nomsFicherWhite = {
        "WhiteQueen.png",
        "WhiteBishop.png",
        "WhiteKnight.png",
        "WhiteRook.png"
    };

    for (const auto& nom : nomsFicherWhite) {
        sf::Texture texture;
        if (!texture.loadFromFile("resources/images/" + nom)) {
            std::cerr << "Erreur : Impossible de charger l'image " << nom << std::endl;
        }
        texturesPromotionWhite.push_back(texture);
    }
    std::vector<std::string> nomsFicherRed = {
        "RedQueen.png",
        "RedBishop.png",
        "RedKnight.png",
        "RedRook.png"
    };

    for (const auto& nom : nomsFicherRed) {
        sf::Texture texture;
        if (!texture.loadFromFile("resources/images/" + nom)) {
            std::cerr << "Erreur : Impossible de charger l'image " << nom << std::endl;
        }
        texturesPromotionRed.push_back(texture);
    }
    std::vector<std::string> nomsFicherBlack = {
        "BlackQueen.png",
        "BlackBishop.png",
        "BlackKnight.png",
        "BlackRook.png"
    };

    for (const auto& nom : nomsFicherBlack) {
        sf::Texture texture;
        if (!texture.loadFromFile("resources/images/" + nom)) {
            std::cerr << "Erreur : Impossible de charger l'image " << nom << std::endl;
        }
        texturesPromotionBlack.push_back(texture);
    }
}

void DrawBoard::drawBackButton(const sf::RectangleShape& button, const sf::Text& text) {
    window.draw(button);
    window.draw(text);
}

