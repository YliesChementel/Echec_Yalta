/**
 * @file MakeBoard.cpp
 * @brief Implémentation de la classe MakeBoard pour la création et la gestion du plateau de jeu
 */

#include "include/MakeBoard.hpp"
#include <cmath>
#include <iostream>
#include <locale>
#include <codecvt>

const float PI = 3.14159265359f;  ///< Constante Pi pour les calculs trigonométriques

/**
 * @brief Constructeur de la classe MakeBoard
 * 
 * Initialise le plateau de jeu en créant :
 * - Les hexagones extérieur et intérieur
 * - Les lignes de séparation
 * - Les matrices de losanges
 * - Les textes de coordonnées
 * - Les pièces pour chaque camp
 */
MakeBoard::MakeBoard() {
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création de l'héxagon du plateau
    std::vector<float> side_lengths = {450, 460, 460, 450, 460, 460};  // Longueurs des côtés de l'hexagone
    std::vector<sf::Vector2f> points;  // Points de l'hexagone
    float angle = 0;  // Angle initial
    sf::Vector2f origin(350, 150);  // Point d'origine
    points.push_back(origin + sf::Vector2f(side_lengths[0], 0));
    
    // Calcul des points de l'hexagone
    for (int i = 1; i < 6; i++) {
        angle += PI / 3;
        points.push_back(points.back() + sf::Vector2f(std::cos(angle), std::sin(angle)) * side_lengths[i]);
    }

    // Configuration de l'hexagone extérieur
    this->hexagon.setPointCount(6);
    for (size_t i = 0; i < 6; i++) this->hexagon.setPoint(i, points[i]);
    this->hexagon.setFillColor(sf::Color::Transparent);
    this->hexagon.setOutlineColor(sf::Color::White);
    this->hexagon.setOutlineThickness(2);

    // Calcul du centre de l'hexagone
    sf::Vector2f center(0, 0);
    for (const auto& p : points) center += p;
    center /= static_cast<float>(points.size());

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création de l'héxagon 2 (intérieur)
    std::vector<sf::Vector2f> points2;
    std::vector<float> side_lengths2 = {500, 510, 510, 500, 510, 510};  // Longueurs des côtés du deuxième hexagone
    points2.push_back(origin + sf::Vector2f(side_lengths2[0], 0));
    
    // Calcul des points du deuxième hexagone
    for (int i = 1; i < 6; i++) {
        angle += PI / 3;
        points2.push_back(points2.back() + sf::Vector2f(std::cos(angle), std::sin(angle)) * side_lengths2[i]);
    }

    // Calcul du centre du deuxième hexagone
    sf::Vector2f center2(0, 0);
    for (const auto& p : points2) center2 += p;
    center2 /= static_cast<float>(points2.size());

    // Alignement des deux hexagones
    sf::Vector2f offset = center - center2; 
    for (auto& p : points2) {
        p += offset;
    }

    // Configuration du deuxième hexagone
    this->hexagon2.setPointCount(6);
    for (size_t i = 0; i < 6; i++) this->hexagon2.setPoint(i, points2[i]);
    this->hexagon2.setFillColor(sf::Color::White);
    this->hexagon2.setOutlineColor(sf::Color::Black);
    this->hexagon2.setOutlineThickness(7);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des milieux des arêtes
    std::vector<sf::Vector2f> milieux = {
        milieu(points[4], points[3]), // bas gauche
        milieu(points[3], points[2]), // bas
        milieu(points[0], points[1]), // haut droite
        milieu(points[0], points[5]), // haut
        milieu(points[5], points[4]), // haut gauche
        milieu(points[1], points[2])  // bas droite
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des lignes séparant les matrices
    for (const auto& m : milieux) {
        this->lines.push_back(createLine(center, m, sf::Color::Red));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des lignes des matrices pour créer les losanges
    std::vector<sf::Vector2f> mat1_lines = createMatrixLines(center, milieux[1], milieux[0], points[3], points[4], points[2]);
    std::vector<sf::Vector2f> mat2_lines = createMatrixLines(center, milieux[5], milieux[1], points[2], points[3], points[1]);
    std::vector<sf::Vector2f> mat3_lines = createMatrixLines(center, milieux[0], milieux[4], points[4], points[5], points[3]);
    std::vector<sf::Vector2f> mat4_lines = createMatrixLines(center, milieux[4], milieux[3], points[5], points[0], points[4]);
    std::vector<sf::Vector2f> mat5_lines = createMatrixLines(center, milieux[2], milieux[5], points[1], points[2], points[0]);
    std::vector<sf::Vector2f> mat6_lines = createMatrixLines(center, milieux[3], milieux[2], points[0], points[1], points[5]);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des losanges pour chaque matrice
    sf::Color blanc(0xFE, 0xF7, 0xE5);  // Couleur claire
    sf::Color beige(0xEE, 0xCF, 0xA1);  // Couleur foncée
    this->matrice1 = createMatrixLosange(center,mat1_lines, points[3], milieux[1], milieux[0], beige, blanc);
    this->matrice2 = createMatrixLosange(center,mat2_lines, points[2], milieux[5], milieux[1], blanc, beige);
    this->matrice3 = createMatrixLosange(center,mat3_lines, points[4], milieux[0], milieux[4], blanc, beige);
    this->matrice4 = createMatrixLosange(center,mat4_lines, points[5], milieux[4], milieux[3], beige, blanc);
    this->matrice5 = createMatrixLosange(center,mat5_lines, points[1], milieux[2], milieux[5], beige, blanc);
    this->matrice6 = createMatrixLosange(center,mat6_lines, points[0], milieux[3], milieux[2], blanc, beige);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création du texte pour les cases
    if (!this->font.loadFromFile("resources/font/arial.ttf")) {
        throw std::runtime_error("Error loading font!");
    }

    // Définition des coordonnées pour chaque bord du plateau
    std::vector<std::string> lettresBas = {"a", "b", "c", "d", "e", "f", "g", "h"};
    std::vector<std::string> lettresHaut = {"8", "7", "6", "5", "9", "10", "11", "12"};
    std::vector<std::string> chiffresBasGauche = {"1", "2", "3", "4", "5", "6", "7", "8"};
    std::vector<std::string> lettresHautDroite = {"h", "g", "f", "e", "i", "j", "k", "l"};
    std::vector<std::string> lettresHautGauche = {"l", "k", "j", "i", "d", "c", "b", "a"};
    std::vector<std::string> lettresBasDroite = {"1", "2", "3", "4", "9", "10", "11", "12"};

    // Positionnement des textes de coordonnées
    sf::Vector2f startBas = milieu(points[3], points2[4]) - sf::Vector2f(-30, 18);
    sf::Vector2f startHaut = milieu(points[5], points2[0]) - sf::Vector2f(-30, 18);
    sf::Vector2f startBasGauche = milieu(points[4], points2[5]) + sf::Vector2f(213, 370);
    sf::Vector2f startHautDroite = milieu(points[0], points2[1]) + sf::Vector2f(213, 360);
    sf::Vector2f startHautGauche = milieu(points[5], points2[0]) - sf::Vector2f(35, -15);
    sf::Vector2f startBasDroite = milieu(points[2], points2[3]) + sf::Vector2f(7, -55);

    // Création des textes de coordonnées
    for (size_t i = 0; i < 8; ++i) {
        this->coordText.push_back(createText(lettresBas[i], startBas + sf::Vector2f(i * 57.0f, 0.0f), 28, sf::Color::Black, this->font));
        if(i > 4) {
            this->coordText.push_back(createText(lettresHaut[i], startHaut + sf::Vector2f(i * 56.0f, 0.0f), 28, sf::Color::Black, this->font));
        }
        else {
            this->coordText.push_back(createText(lettresHaut[i], startHaut + sf::Vector2f(i * 57.0f, 0.0f), 28, sf::Color::Black, this->font));
        }
        this->coordText.push_back(createText(chiffresBasGauche[i], startBasGauche - sf::Vector2f(i * 29.0f, i * 50.0f), 28, sf::Color::Black, this->font));
        this->coordText.push_back(createText(lettresHautDroite[i], startHautDroite - sf::Vector2f(i * 29.0f, i * 50.0f), 28, sf::Color::Black, this->font));
        this->coordText.push_back(createText(lettresHautGauche[i], startHautGauche + sf::Vector2f(7 - i * 29.0f, i * 50.0f), 28, sf::Color::Black, this->font));
        if(i > 4) {
            this->coordText.push_back(createText(lettresBasDroite[i], startBasDroite + sf::Vector2f(i * 28.0f, 7 - i * 50.0f), 28, sf::Color::Black, this->font));
        }
        else {
            this->coordText.push_back(createText(lettresBasDroite[i], startBasDroite + sf::Vector2f(i * 29.0f, 7 - i * 50.0f), 28, sf::Color::Black, this->font));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des pièces du jeu
    // Chargement des textures et création des pièces pour chaque camp
    std::vector<std::string> texturePathWhite = {
        "WhiteRook.png", "WhiteKnight.png", "WhiteBishop.png", "WhiteQueen.png",
        "WhiteKing.png", "WhiteBishop.png", "WhiteKnight.png", "WhiteRook.png",
        "WhitePawn.png", "WhitePawn.png", "WhitePawn.png", "WhitePawn.png",
        "WhitePawn.png", "WhitePawn.png", "WhitePawn.png", "WhitePawn.png"
    };
    this->texturesWhite = loadTextures(texturePathWhite);
    this->WhitePieces = CreerPiece(this->matrice1, this->matrice2, 1, 2, texturesWhite, "White"); 

    std::vector<std::string> texturePathRed = {
        "RedRook.png", "RedKnight.png", "RedBishop.png", "RedQueen.png",
        "RedKing.png", "RedBishop.png", "RedKnight.png", "RedRook.png",
        "RedPawn.png", "RedPawn.png", "RedPawn.png", "RedPawn.png",
        "RedPawn.png", "RedPawn.png", "RedPawn.png", "RedPawn.png"
    };
    this->texturesRed = loadTextures(texturePathRed);
    this->RedPieces = CreerPiece(this->matrice4, this->matrice3, 4, 3, texturesRed,"Red");

    std::vector<std::string> texturePathBlack = {
        "BlackRook.png", "BlackKnight.png", "BlackBishop.png", "BlackQueen.png",
        "BlackKing.png", "BlackBishop.png", "BlackKnight.png", "BlackRook.png",
        "BlackPawn.png", "BlackPawn.png", "BlackPawn.png", "BlackPawn.png",
        "BlackPawn.png", "BlackPawn.png", "BlackPawn.png", "BlackPawn.png"
    };
    this->texturesBlack = loadTextures(texturePathBlack);
    this->BlackPieces = CreerPiece(this->matrice5, this->matrice6, 5, 6,texturesBlack,"Black");

    // Initialisation des textes et du bouton retour
    setTextGame("Bienvenue sur le jeu Yalta !"); 
    setTextEchec(""); 

    backButton.setSize(sf::Vector2f(100, 40));
    backButton.setPosition(sf::Vector2f(1045, 5));
    backButton.setFillColor(beige);
    backButton.setOutlineColor(sf::Color::Black);
    backButton.setOutlineThickness(2);
    backButtonText = createText("Accueil", sf::Vector2f(1063, 12), 20, sf::Color::Black, font);
}

/**
 * @brief Calcule le point milieu entre deux points
 * @param p1 Premier point
 * @param p2 Deuxième point
 * @return Point milieu
 */
sf::Vector2f MakeBoard::milieu(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return (p1 + p2) / 2.0f;
}

/**
 * @brief Crée une ligne entre deux points
 * @param start Point de départ
 * @param end Point d'arrivée
 * @param color Couleur de la ligne
 * @return Tableau de deux sommets formant la ligne
 */
std::array<sf::Vertex, 2> MakeBoard::createLine(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color) {
    return {sf::Vertex(start, color), sf::Vertex(end, color)};
}

/**
 * @brief Crée les lignes d'une matrice
 * @param center Centre de la matrice
 * @param milieu1 Premier point milieu
 * @param milieu2 Deuxième point milieu
 * @param point1 Premier point
 * @param point2 Deuxième point
 * @param point3 Troisième point
 * @return Vecteur des points formant les lignes
 */
std::vector<sf::Vector2f> MakeBoard::createMatrixLines(const sf::Vector2f& center, const sf::Vector2f& milieu1,const sf::Vector2f& milieu2, const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3) {
    std::vector<sf::Vector2f> lines;
    // Création des lignes pour la première partie de la matrice
    for (float ratio : {0.25f, 0.50f, 0.75f}) {
        lines.push_back(center + ratio * (milieu1 - center));
        lines.push_back((1 - (1 - ratio) / 2) * point1 + ((1 - ratio) / 2) * point2);
    }
    // Création des lignes pour la deuxième partie de la matrice
    for (float ratio : {0.25f, 0.50f, 0.75f}) {
        lines.push_back(center + ratio * (milieu2 - center));
        lines.push_back((1 - (1 + ratio) / 2) * point3 + ((1 + ratio) / 2) * point1);
    }
    return lines;
}

/**
 * @brief Crée un losange
 * @param p1 Premier point
 * @param p2 Deuxième point
 * @param p3 Troisième point
 * @param p4 Quatrième point
 * @param fill Couleur de remplissage
 * @param outline Couleur du contour
 * @return Losange créé
 */
sf::ConvexShape MakeBoard::createLosange(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4, sf::Color fill, sf::Color outline) {
    sf::ConvexShape losange;
    losange.setPointCount(4);
    losange.setPoint(0, p1);
    losange.setPoint(1, p2);
    losange.setPoint(2, p3);
    losange.setPoint(3, p4);
    losange.setFillColor(fill);
    losange.setOutlineColor(outline);
    losange.setOutlineThickness(2);
    return losange;
}

/**
 * @brief Crée une matrice de losanges
 * @param center Centre de la matrice
 * @param mat_lines Lignes de la matrice
 * @param point Point de référence
 * @param milieu1 Premier point milieu
 * @param milieu2 Deuxième point milieu
 * @param color1 Première couleur
 * @param color2 Deuxième couleur
 * @return Vecteur des losanges créés
 */
std::vector<sf::ConvexShape> MakeBoard::createMatrixLosange(const sf::Vector2f& center, const std::vector<sf::Vector2f>& mat_lines, const sf::Vector2f& point, const sf::Vector2f& milieu1, const sf::Vector2f& milieu2, sf::Color color1, sf::Color color2) {
    std::vector<sf::ConvexShape> shapes;
    // Création des losanges pour chaque section de la matrice
    shapes.push_back(createLosange(center, mat_lines[0], mat_lines[6] + 0.25f * (mat_lines[7] - mat_lines[6]), mat_lines[6], color1, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[0], mat_lines[2], mat_lines[6] + 0.5f * (mat_lines[7] - mat_lines[6]), mat_lines[6] + 0.25f * (mat_lines[7] - mat_lines[6]), color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[2], mat_lines[4], mat_lines[6] + 0.75f * (mat_lines[7] - mat_lines[6]), mat_lines[6] + 0.5f * (mat_lines[7] - mat_lines[6]), color1, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[4], milieu1, mat_lines[7], mat_lines[6] + 0.75f * (mat_lines[7] - mat_lines[6]), color2, sf::Color::Black));

    shapes.push_back(createLosange(mat_lines[6], mat_lines[6] + 0.25f * (mat_lines[7] - mat_lines[6]), mat_lines[8] + 0.25f * (mat_lines[9] - mat_lines[8]),mat_lines[8] , color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[6] + 0.25f * (mat_lines[7] - mat_lines[6]),mat_lines[6] + 0.5f * (mat_lines[7] - mat_lines[6]), mat_lines[8] + 0.5f * (mat_lines[9] - mat_lines[8]), mat_lines[8] + 0.25f * (mat_lines[9] - mat_lines[8]) , color1, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[6] + 0.5f * (mat_lines[7] - mat_lines[6]),mat_lines[6] + 0.75f * (mat_lines[7] - mat_lines[6]),mat_lines[8] + 0.75f * (mat_lines[9] - mat_lines[8]), mat_lines[8] + 0.5f * (mat_lines[9] - mat_lines[8]), color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[6] + 0.75f * (mat_lines[7] - mat_lines[6]), mat_lines[7], mat_lines[9], mat_lines[8] + 0.75f * (mat_lines[9] - mat_lines[8]), color1, sf::Color::Black));

    shapes.push_back(createLosange(mat_lines[8], mat_lines[8] + 0.25f * (mat_lines[9] - mat_lines[8]), mat_lines[10] + 0.25f * (mat_lines[11] - mat_lines[10]), mat_lines[10], color1, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[8] + 0.25f * (mat_lines[9] - mat_lines[8]), mat_lines[8] + 0.5f * (mat_lines[9] - mat_lines[8]),mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]) , mat_lines[10] + 0.25f * (mat_lines[11] - mat_lines[10]), color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[8] + 0.5f * (mat_lines[9] - mat_lines[8]), mat_lines[8] + 0.75f * (mat_lines[9] - mat_lines[8]), mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]), mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]), color1, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[8] + 0.75f * (mat_lines[9] - mat_lines[8]), mat_lines[9], mat_lines[11] , mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]), color2, sf::Color::Black));

    shapes.push_back(createLosange(mat_lines[10], mat_lines[10] + 0.25f * (mat_lines[11] - mat_lines[10]), mat_lines[1], milieu2, color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[10] + 0.25f * (mat_lines[11] - mat_lines[10]), mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]),mat_lines[3] ,mat_lines[1] , color1, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]) ,mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]) ,mat_lines[5] ,mat_lines[3] , color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]), mat_lines[5], point, mat_lines[11], color1, sf::Color::Black));
    return shapes;
}

/**
 * @brief Crée un texte
 * @param textStr Texte à afficher
 * @param startPosition Position de départ
 * @param characterSize Taille des caractères
 * @param color Couleur du texte
 * @param font Police à utiliser
 * @return Texte créé
 */
sf::Text MakeBoard::createText(const std::string& textStr, const sf::Vector2f& startPosition, unsigned int characterSize, sf::Color color, sf::Font& font) {
    sf::Text text;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(textStr);
    text.setString(wtext);
    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(characterSize);
    text.setPosition(startPosition);
    return text;
}

/**
 * @brief Calcule le centre d'un losange
 * @param shape Losange
 * @return Point central
 */
sf::Vector2f MakeBoard::calculerCentreLosange(const sf::ConvexShape& shape) {
    sf::Vector2f centre;
    const sf::Vector2f& A = shape.getPoint(0);
    const sf::Vector2f& C = shape.getPoint(2);
    centre.x = (A.x + C.x) / 2.0f;
    centre.y = (A.y + C.y) / 2.0f;
    return centre;
}

/**
 * @brief Charge une image dans un losange
 * @param shape Losange cible
 * @param scaleX Échelle horizontale
 * @param scaleY Échelle verticale
 * @param texture Texture à charger
 * @return Sprite créé
 */
sf::Sprite MakeBoard::chargerImageDansLosange(const sf::ConvexShape& shape, float scaleX, float scaleY, sf::Texture& texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
    sf::Vector2f centre = calculerCentreLosange(shape);
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setPosition(centre.x - bounds.width / 2.0f, centre.y - bounds.height / 2.0f);
    return sprite;
}

/**
 * @brief Charge les textures des pièces
 * @param filePaths Chemins des fichiers de textures
 * @return Vecteur des textures chargées
 */
std::vector<sf::Texture> MakeBoard::loadTextures(const std::vector<std::string>& filePaths) {
    std::vector<sf::Texture> textures;
    for (const auto& path : filePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile("resources/images/"+path)) {
            std::cerr << "Erreur : Impossible de charger l'image " << path << std::endl;
        }
        textures.push_back(texture);
    }
    return textures;
}

/**
 * @brief Crée les pièces pour un camp
 * @param matriceA Première matrice
 * @param matriceB Deuxième matrice
 * @param positionMatriceA Position dans la première matrice
 * @param positionMatriceB Position dans la deuxième matrice
 * @param textures Textures des pièces
 * @param camp Camp des pièces
 * @return Vecteur des pièces créées
 */
std::vector<PieceImage> MakeBoard::CreerPiece(const std::vector<sf::ConvexShape> matriceA, const std::vector<sf::ConvexShape> matriceB, int positionMatriceA, int positionMatriceB, std::vector<sf::Texture>& textures,std::string camp) {
    std::vector<PieceImage> pieceImage;
    sf::Texture texture;
    // Création des pièces majeures (tours, cavaliers, fous, reine, roi)
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[15], 0.2f, 0.2f,textures[0]),std::vector<int>{15, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[11], 0.2f, 0.2f, textures[1]),std::vector<int>{11, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[7], 0.2f, 0.2f, textures[2]),std::vector<int>{7, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[3], 0.2f, 0.2f, textures[3]),std::vector<int>{3, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[12], 0.2f, 0.2f, textures[4]),std::vector<int>{12, positionMatriceB},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[13], 0.2f, 0.2f, textures[5]),std::vector<int>{13, positionMatriceB},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[14], 0.2f, 0.2f, textures[6]),std::vector<int>{14, positionMatriceB},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[15], 0.2f, 0.2f, textures[7]),std::vector<int>{15, positionMatriceB},camp));
    // Création des pions
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[14], 0.2f, 0.2f, textures[8]),std::vector<int>{14, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[10], 0.2f, 0.2f, textures[9]),std::vector<int>{10, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[6], 0.2f, 0.2f, textures[10]),std::vector<int>{6, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceA[2], 0.2f, 0.2f, textures[11]),std::vector<int>{2, positionMatriceA},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[8], 0.2f, 0.2f, textures[12]),std::vector<int>{8, positionMatriceB},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[9], 0.2f, 0.2f, textures[13]),std::vector<int>{9, positionMatriceB},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[10], 0.2f, 0.2f, textures[14]),std::vector<int>{10, positionMatriceB},camp));
    pieceImage.push_back(PieceImage(chargerImageDansLosange(matriceB[11], 0.2f, 0.2f, textures[15]),std::vector<int>{11, positionMatriceB},camp));
    return pieceImage;
}

/**
 * @brief Vérifie si un point est dans une matrice
 * @param point Point à vérifier
 * @param matrice Matrice à tester
 * @return true si le point est dans la matrice
 */
bool MakeBoard::PieceDansMatrice(const sf::Vector2f& point, const std::vector<sf::ConvexShape> matrice){
    std::vector<sf::Vector2i> polygon = {
        sf::Vector2i(matrice[0].getPoint(0).x, matrice[0].getPoint(0).y),
        sf::Vector2i(matrice[3].getPoint(1).x, matrice[3].getPoint(1).y),
        sf::Vector2i(matrice[15].getPoint(2).x, matrice[15].getPoint(2).y),
        sf::Vector2i(matrice[12].getPoint(3).x, matrice[12].getPoint(3).y)
    };
    bool inside = false;

    // Algorithme du ray casting pour déterminer si le point est dans le polygone
    for (int i = 0, j = 4 - 1; i < 4; j = i++) {
        if ((point.y > polygon[i].y) != (point.y > polygon[j].y) &&(point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }

    return inside;
}

/**
 * @brief Vérifie si un point est dans un losange
 * @param shape Losange à tester
 * @param point Point à vérifier
 * @return true si le point est dans le losange
 */
bool MakeBoard::PieceDansLosange(const sf::ConvexShape& shape, const sf::Vector2f& point){
    int n = shape.getPointCount();
    bool inside = false;
    // Algorithme du ray casting pour déterminer si le point est dans le losange
    for (int i = 0, j = n - 1; i < n; j = i++) {
        sf::Vector2f p1 = shape.getPoint(i);
        sf::Vector2f p2 = shape.getPoint(j);

        if (((p1.y > point.y) != (p2.y > point.y)) &&
            (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)) {
            inside = !inside;
        }
    }

    return inside;
}

/**
 * @brief Obtient une matrice par son index
 * @param index Index de la matrice
 * @return Référence à la matrice demandée
 */
std::vector<sf::ConvexShape>& MakeBoard::getMatrice(int index) {
    switch(index) {
        case 1: return matrice1;
        case 2: return matrice2;
        case 3: return matrice3;
        case 4: return matrice4;
        case 5: return matrice5;
        case 6: return matrice6;
        default: throw std::out_of_range("Index de matrice invalide");
    }
}

/**
 * @brief Place une pièce sur le plateau
 * @param selectedPieceIndex Index de la pièce sélectionnée
 * @param losange Losange cible
 * @param listePieces Liste des pièces
 * @param IndexMat Index de la matrice
 * @param IndexLos Index du losange
 */
void MakeBoard::PlacementPiece(int& selectedPieceIndex, const sf::ConvexShape& losange, std::vector<PieceImage>& listePieces, int IndexMat,int IndexLos) {
    sf::Vector2f centre = calculerCentreLosange(losange);
    // Positionnement de la pièce au centre du losange
    listePieces[selectedPieceIndex].getSprite().setPosition(
        centre.x - listePieces[selectedPieceIndex].getSprite().getGlobalBounds().width / 2.0f,
        centre.y - listePieces[selectedPieceIndex].getSprite().getGlobalBounds().height / 2.0f
        );
    listePieces[selectedPieceIndex].setTilePositions({IndexLos,IndexMat});
}

/**
 * @brief Replace une pièce à sa position d'origine
 * @param selectedPieceIndex Index de la pièce
 * @param camp Camp de la pièce
 * @param matriceIndex Index de la matrice
 * @param pieces Liste des pièces
 */
void MakeBoard::ReplacementPiece(int& selectedPieceIndex, int camp, int matriceIndex, std::vector<PieceImage>& pieces) {
    std::vector<std::vector<sf::ConvexShape>> matrices = {getMatrice1(), getMatrice2(), getMatrice3(), getMatrice4(), getMatrice5(), getMatrice6()};
    int tileIndex = pieces[selectedPieceIndex].getTilePositions()[0];
    const sf::ConvexShape& losange = matrices[matriceIndex - 1][tileIndex];
    sf::Vector2f centre = calculerCentreLosange(losange);

    // Repositionnement de la pièce à sa position d'origine
    pieces[selectedPieceIndex].getSprite().setPosition(
        centre.x - pieces[selectedPieceIndex].getSprite().getGlobalBounds().width / 2.0f,
        centre.y - pieces[selectedPieceIndex].getSprite().getGlobalBounds().height / 2.0f
    );
}

/**
 * @brief Détermine la sous-matrice à partir des coordonnées
 * @param x Coordonnée X
 * @param y Coordonnée Y
 * @return Index de la sous-matrice
 */
int MakeBoard::determineSubMatrix(int x, int y) {
    if (x < 4 && y < 4) return 1; // haut gauche
    if (x < 4 && y >= 4 && y < 8) return 2; // haut milieu
    if (y < 4 && x >= 4 && x < 8) return 3; // milieu gauche
    if (y >= 7 && x >= 4 && x < 8) return 4; // milieu droite
    if (x >= 7 && y >= 4 && y < 8) return 5; // bas milieu
    if (x >= 7 && y >= 7) return 6; // bas droite
    return 0;
}

/**
 * @brief Convertit des coordonnées en index de losange
 * @param x Coordonnée X
 * @param y Coordonnée Y
 * @param matrice Index de la matrice
 * @return Index du losange
 */
int MakeBoard::coordonneEnIndexDeLosange(int x, int y, int matrice) {
    if (matrice == 1) {
        return 15 - (x + 4 * y); //bon
    }
    else if (matrice == 2) {
        return (3 - x) * 4 + y; //bon
    }
    else if (matrice == 3) { //bon
        return 4 * x + (3 - y);
    }
    else if (matrice == 4) { //bon
        return 4 * y + x;
    }
    else if (matrice == 5) { //bon
        return 4 * y + x;
    }
    else if (matrice == 6) { //bon
        return  x * 4 + y;
    }
    return -1;
}

/**
 * @brief Convertit un index en coordonnées de plateau
 * @param index Index à convertir
 * @param sousMatrice Sous-matrice
 * @return Paire de coordonnées (x, y)
 */
std::pair<int, int> MakeBoard::indexEnCoordonneDePlateau(int index, int sousMatrice) {
    int x, y;
    
    // Conversion selon la sous-matrice
    if(sousMatrice == 1) {
        y = 3 - (index / 4);  // division entière pour obtenir la ligne
        x = 3 - (index % 4);  // reste pour obtenir la colonne
    }
    else if(sousMatrice == 2) {
        x = 3 - index / 4;
        y = (index % 4) + 4;
    }
    else if(sousMatrice == 3) {
        x =  index / 4 + 4 ;
        y = 3 - index % 4 ;
    }
    else if(sousMatrice == 4) {
        y = index / 4 + 8;
        x = index % 4 + 4;
    }
    else if(sousMatrice == 5) {
        y = index / 4 + 4;
        x = index % 4 + 8;
    }
    else if(sousMatrice == 6) {
        x = index / 4 + 8;
        y = index % 4 + 8;
    }
    
    return {x, y};
}

/**
 * @brief Place une pièce pour l'IA
 * @param listePieces Liste des pièces
 * @param IndexMatStart Index de la matrice de départ
 * @param IndexLosStart Index du losange de départ
 * @param IndexMatEnd Index de la matrice d'arrivée
 * @param IndexLosEnd Index du losange d'arrivée
 * @param selectedPieceIndex Index de la pièce sélectionnée
 */
void MakeBoard::PlacementPieceAI(std::vector<PieceImage>& listePieces, int IndexMatStart,int IndexLosStart,int IndexMatEnd,int IndexLosEnd,int& selectedPieceIndex) {
    // Recherche de la pièce à déplacer
    int aiPieceIndex = -1;
    for(int i = 0; i < listePieces.size(); i++) {
        if (listePieces[i].getTilePositions()[0] == IndexLosStart && listePieces[i].getTilePositions()[1] == IndexMatStart) {
            aiPieceIndex = i;
            break;
        }
    }

    // Déplacement de la pièce
    sf::ConvexShape losange = getMatrice(IndexMatEnd)[IndexLosEnd];
    sf::Vector2f centre = calculerCentreLosange(losange);

    listePieces[aiPieceIndex].getSprite().setPosition(
        centre.x - listePieces[aiPieceIndex].getSprite().getGlobalBounds().width / 2.0f,
        centre.y - listePieces[aiPieceIndex].getSprite().getGlobalBounds().height / 2.0f
        );
    listePieces[aiPieceIndex].setTilePositions({IndexLosEnd,IndexMatEnd});
}

/**
 * @brief Vérifie si la souris est sur le bouton retour
 * @param mousePos Position de la souris
 * @return true si la souris est sur le bouton
 */
bool MakeBoard::isMouseOverBackButton(const sf::Vector2f& mousePos) const {
    return backButton.getGlobalBounds().contains(mousePos);
}