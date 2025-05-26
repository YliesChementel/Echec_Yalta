/**
 * @file DrawBoard.cpp
 * @brief Implémentation de la classe DrawBoard pour le rendu graphique du plateau de jeu
 */

#include "include/DrawBoard.hpp"
#include <iterator>
#include <vector>
#include <iostream>

/**
 * @brief Constructeur de la classe DrawBoard
 * Initialise la fenêtre de rendu et charge les textures de promotion
 * @param win Référence à la fenêtre de rendu SFML
 */
DrawBoard::DrawBoard(sf::RenderWindow& win) : window(win) { loadPromotionTextures(); }

/**
 * @brief Efface la fenêtre avec une couleur de fond
 */
void DrawBoard::clear() {
    this->window.clear(sf::Color(48, 46, 43));
}

/**
 * @brief Met à jour l'affichage de la fenêtre
 */
void DrawBoard::display() {
    window.display();
}

/**
 * @brief Dessine deux hexagones sur la fenêtre
 * @param hex1 Premier hexagone à dessiner
 * @param hex2 Deuxième hexagone à dessiner
 */
void DrawBoard::drawHexagons(const sf::ConvexShape& hex1, const sf::ConvexShape& hex2) {
    window.draw(hex1);
    window.draw(hex2);
}

/**
 * @brief Dessine les lignes de connexion entre les hexagones
 * @param lines Vecteur de paires de points définissant les lignes
 */
void DrawBoard::drawLines(const std::vector<std::array<sf::Vertex, 2>>& lines) {
    for (const auto& line : lines) {
        window.draw(line.data(), 2, sf::Lines);
    }
}

/**
 * @brief Dessine un ensemble de textes sur la fenêtre
 * @param texts Vecteur des textes à afficher
 */
void DrawBoard::drawText(const std::vector<sf::Text>& texts) {
    for (const auto& text : texts) {
        window.draw(text);
    }
}

/**
 * @brief Dessine un texte centré horizontalement
 * @param text Texte à afficher
 */
void DrawBoard::drawTextGame(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    float x = (window.getSize().x - bounds.width) / 2.f - bounds.left;
    float y = text.getPosition().y;
    text.setPosition(x, y);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

/**
 * @brief Dessine le plateau de jeu complet
 * @param matrices Vecteur de matrices contenant les hexagones du plateau
 */
void DrawBoard::drawBoard(const std::vector<std::vector<sf::ConvexShape>>& matrices) {
    for (const auto& matrice : matrices) {
        for (const auto& losange : matrice) {
            window.draw(losange);
        }
    }
}

/**
 * @brief Dessine toutes les pièces sur le plateau
 * @param whites Vecteur des pièces blanches
 * @param blacks Vecteur des pièces noires
 * @param reds Vecteur des pièces rouges
 */
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

/**
 * @brief Assombrit la couleur d'une case
 * @param losange Case à assombrir
 */
void DrawBoard::changeColorTileDark(sf::ConvexShape& losange) {
    sf::Color actuel = losange.getFillColor();

    sf::Color darkerColor(
        actuel.r * 0.5, actuel.g * 0.5, actuel.b * 0.5, actuel.a
    );

    losange.setFillColor(darkerColor);
}

/**
 * @brief Éclaircit la couleur d'une case
 * @param losange Case à éclaircir
 */
void DrawBoard::changeColorTileBright(sf::ConvexShape& losange) {
    sf::Color actuel = losange.getFillColor();

    sf::Color brighterColor(
        actuel.r * 2, actuel.g * 2, actuel.b * 2, actuel.a
    );

    losange.setFillColor(brighterColor);
}

/**
 * @brief Crée un carré avec une image pour l'interface de promotion
 * @param texture Texture à afficher
 * @param position Position du carré
 * @return Paire contenant le carré et le sprite
 */
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

/**
 * @brief Dessine l'interface de promotion des pions
 * @param camp Camp du joueur (0: blanc, 1: rouge, 2: noir)
 */
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

/**
 * @brief Charge les textures pour l'interface de promotion
 * Charge les textures des pièces pour chaque camp (blanc, rouge, noir)
 */
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

/**
 * @brief Dessine un bouton retour avec son texte
 * @param button Forme du bouton
 * @param text Texte du bouton
 */
void DrawBoard::drawBackButton(const sf::RectangleShape& button, const sf::Text& text) {
    window.draw(button);
    window.draw(text);
}

