#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include <array>
#include <iostream>

const float PI = 3.14159265359f;

sf::Vector2f milieu(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return (p1 + p2) / 2.0f;
}

std::array<sf::Vertex, 2> createLine(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color) {
    return {sf::Vertex(start, color), sf::Vertex(end, color)};
}

std::vector<sf::Vector2f> createMatrixLines(const sf::Vector2f& center, const sf::Vector2f& milieu1,const sf::Vector2f& milieu2, const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3) {
    std::vector<sf::Vector2f> lines;
        for (float ratio : {0.25f, 0.50f, 0.75f}) {
            lines.push_back(center + ratio * (milieu1 - center));
            lines.push_back((1 - (1 - ratio) / 2) * point1 + ((1 - ratio) / 2) * point2);
        }
        for (float ratio : {0.25f, 0.50f, 0.75f}) {
            lines.push_back(center + ratio * (milieu2 - center));
            lines.push_back((1 - (1 + ratio) / 2) * point3 + ((1 + ratio) / 2) * point1);
        }
    return lines;
}

sf::ConvexShape createLosange(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4, sf::Color fill, sf::Color outline) {
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

std::vector<sf::ConvexShape> createMatrixLosange( const sf::Vector2f& center,const std::vector<sf::Vector2f>& mat_lines, const sf::Vector2f& point, const sf::Vector2f& milieu1, const sf::Vector2f& milieu2,sf::Color color1,sf::Color color2) {
    std::vector<sf::ConvexShape> shapes;
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


sf::Text createText(const std::string& textStr, const sf::Vector2f& startPosition, unsigned int characterSize, sf::Color color, sf::Font& font) {
    sf::Text text;
    text.setString(textStr);
    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(characterSize);
    text.setPosition(startPosition);
    return text;
}

sf::Sprite chargerImage(const std::string& cheminFichier, float posX, float posY, float scaleX, float scaleY, sf::Texture& texture) {
    if (!texture.loadFromFile(cheminFichier)) {
        std::cerr << "Erreur : Impossible de charger l'image " << cheminFichier << std::endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);
    
    return sprite;
}

sf::Vector2f calculerCentreLosange(const sf::ConvexShape& shape) {
    sf::Vector2f centre;
    const sf::Vector2f& A = shape.getPoint(0);
    const sf::Vector2f& C = shape.getPoint(2);
    centre.x = (A.x + C.x) / 2.0f;
    centre.y = (A.y + C.y) / 2.0f;
    return centre;
}

// Fonction pour charger une image et la centrer dans un losange (sf::ConvexShape)
sf::Sprite chargerImageDansLosange(const std::string& cheminFichier, const sf::ConvexShape& shape, float scaleX, float scaleY, sf::Texture& texture) {
    if (!texture.loadFromFile(cheminFichier)) {
        std::cerr << "Erreur : Impossible de charger l'image " << cheminFichier << std::endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
    sf::Vector2f centre = calculerCentreLosange(shape);
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setPosition(centre.x - bounds.width / 2.0f, centre.y - bounds.height / 2.0f);

    return sprite;
}

std::vector<sf::Texture> loadTextures(const std::vector<std::string>& filePaths) {
    std::vector<sf::Texture> textures;
    for (const auto& path : filePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Erreur : Impossible de charger l'image " << path << std::endl;
        }
        textures.push_back(texture);
    }
    return textures;
}

std::vector<sf::Sprite> CreerPiece(const std::vector<std::string>& cheminFichiers, const std::vector<sf::ConvexShape> matriceA, const std::vector<sf::ConvexShape> matriceB,  std::vector<sf::Texture>& textures) {
    std::vector<sf::Sprite> Pieces;
    sf:: Texture texture;
    Pieces.push_back(chargerImageDansLosange("images/"+ cheminFichiers[0], matriceA[15], 0.2f, 0.2f,textures[0]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[1], matriceA[11], 0.2f, 0.2f, textures[1]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[2], matriceA[7], 0.2f, 0.2f, textures[2]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[3], matriceA[3], 0.2f, 0.2f, textures[3]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[4], matriceB[12], 0.2f, 0.2f, textures[4]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[5], matriceB[13], 0.2f, 0.2f, textures[5]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[6], matriceB[14], 0.2f, 0.2f, textures[6]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[7], matriceB[15], 0.2f, 0.2f, textures[7]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[8], matriceA[14], 0.2f, 0.2f, textures[8]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[9], matriceA[10], 0.2f, 0.2f, textures[9]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[10], matriceA[6], 0.2f, 0.2f, textures[10]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[11], matriceA[2], 0.2f, 0.2f, textures[11]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[12], matriceB[8], 0.2f, 0.2f, textures[12]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[13], matriceB[9], 0.2f, 0.2f, textures[13]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[14], matriceB[10], 0.2f, 0.2f, textures[14]));
    Pieces.push_back(chargerImageDansLosange("images/"+cheminFichiers[15], matriceB[11], 0.2f, 0.2f, textures[15]));
    return Pieces;
}

bool PieceDansMatrice(const sf::Vector2f& point, const std::vector<sf::ConvexShape> matrice){
    std::vector<sf::Vector2i> polygon = {
        sf::Vector2i(matrice[0].getPoint(0).x, matrice[0].getPoint(0).y),
        sf::Vector2i(matrice[3].getPoint(1).x, matrice[3].getPoint(1).y),
        sf::Vector2i(matrice[15].getPoint(2).x, matrice[15].getPoint(2).y),
        sf::Vector2i(matrice[12].getPoint(3).x, matrice[12].getPoint(3).y)
    };
    bool inside = false;

    for (int i = 0, j = 4 - 1; i < 4; j = i++) {
        if ((point.y > polygon[i].y) != (point.y > polygon[j].y) &&(point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }

    return inside;
}

bool PieceDansLosange(const sf::ConvexShape& shape, const sf::Vector2f& point){
    int n = shape.getPointCount();
    bool inside = false;
    // On parcourt les bords du polygone (les segments entre les points successifs)
    for (int i = 0, j = n - 1; i < n; j = i++) {
        sf::Vector2f p1 = shape.getPoint(i);
        sf::Vector2f p2 = shape.getPoint(j);

        // Vérification si le point est à l'intérieur du polygone en utilisant l'algorithme du ray-casting
        if (((p1.y > point.y) != (p2.y > point.y)) &&
            (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)) {
            inside = !inside;
        }
    }

    return inside;
}


void PlacementPiece(int& selectedPieceIndex,const sf::ConvexShape losange,std::vector<sf::Sprite>& WhitePieces,std::vector<sf::Sprite>& BlackPieces,std::vector<sf::Sprite>& RedPieces){
    sf::Vector2f centre = calculerCentreLosange(losange);
    if (selectedPieceIndex < WhitePieces.size()) {
        WhitePieces[selectedPieceIndex].setPosition(centre.x - WhitePieces[selectedPieceIndex].getGlobalBounds().width / 2.0f, centre.y - WhitePieces[selectedPieceIndex].getGlobalBounds().height / 2.0f);
    } else if (selectedPieceIndex < WhitePieces.size() + RedPieces.size()) {
        RedPieces[selectedPieceIndex - WhitePieces.size()].setPosition(centre.x - RedPieces[selectedPieceIndex - WhitePieces.size()].getGlobalBounds().width / 2.0f, centre.y - RedPieces[selectedPieceIndex - WhitePieces.size()].getGlobalBounds().height / 2.0f);
    } else {
        BlackPieces[selectedPieceIndex - WhitePieces.size() - RedPieces.size()].setPosition(centre.x - BlackPieces[selectedPieceIndex - WhitePieces.size() - RedPieces.size()].getGlobalBounds().width / 2.0f, centre.y - BlackPieces[selectedPieceIndex - WhitePieces.size() - RedPieces.size()].getGlobalBounds().height / 2.0f);
    }
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1150, 1000), "Echec Yalta",sf::Style::Default,settings);
    std::vector<float> side_lengths = {450, 460, 460, 450, 460, 460};
    std::vector<sf::Vector2f> points;
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création de l'héxagon du plateau
    float angle = 0;
    sf::Vector2f origin(350, 100);
    points.push_back(origin + sf::Vector2f(side_lengths[0], 0));
    
    for (int i = 1; i < 6; i++) {
        angle += PI / 3;
        points.push_back(points.back() + sf::Vector2f(std::cos(angle), std::sin(angle)) * side_lengths[i]);
    }

    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);
    for (size_t i = 0; i < 6; i++) hexagon.setPoint(i, points[i]);
    hexagon.setFillColor(sf::Color::Transparent);
    hexagon.setOutlineColor(sf::Color::White);
    hexagon.setOutlineThickness(2);

    sf::Vector2f center(0, 0);
    for (const auto& p : points) center += p;
    center /= static_cast<float>(points.size());


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création de l'héxagon 2
    std::vector<sf::Vector2f> points2;
    std::vector<float> side_lengths2 = {500, 510, 510, 500, 510, 510};
    points2.push_back(origin + sf::Vector2f(side_lengths2[0], 0));
    
    for (int i = 1; i < 6; i++) {
        angle += PI / 3;
        points2.push_back(points2.back() + sf::Vector2f(std::cos(angle), std::sin(angle)) * side_lengths2[i]);
    }

    sf::Vector2f center2(0, 0);
    for (const auto& p : points2) center2 += p;
    center2 /= static_cast<float>(points2.size());

    // Déplacer tous les points de l'héxagone 2 pour qu'il soit centré sur le même point que l'héxagone 1
    sf::Vector2f offset = center - center2; 
    for (auto& p : points2) {
        p += offset;  // Appliquer l'offset à chaque point
    }

    sf::ConvexShape hexagon2;
    hexagon2.setPointCount(6);
    for (size_t i = 0; i < 6; i++) hexagon2.setPoint(i, points2[i]);
    hexagon2.setFillColor(sf::Color::Transparent);
    hexagon2.setOutlineColor(sf::Color::Black);
    hexagon2.setOutlineThickness(7);

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
    std::vector<std::array<sf::Vertex, 2>> lines;
    for (const auto& m : milieux) {
        lines.push_back(createLine(center, m, sf::Color::Red));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des lignes des matrices pour créer les losanges en leurs donnant une position sur ces lignes
    std::vector<sf::Vector2f> mat1_lines = createMatrixLines(center, milieux[1], milieux[0], points[3], points[4], points[2]);
    std::vector<sf::Vector2f> mat2_lines = createMatrixLines(center, milieux[5], milieux[1], points[2], points[3], points[1]);
    std::vector<sf::Vector2f> mat3_lines = createMatrixLines(center, milieux[0], milieux[4], points[4], points[5], points[3]);
    std::vector<sf::Vector2f> mat4_lines = createMatrixLines(center, milieux[4], milieux[3], points[5], points[0], points[4]);
    std::vector<sf::Vector2f> mat5_lines = createMatrixLines(center, milieux[2], milieux[5], points[1], points[2], points[0]);
    std::vector<sf::Vector2f> mat6_lines = createMatrixLines(center, milieux[3], milieux[2], points[0], points[1], points[5]);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des losanges
    sf::Color blanc(0xFE, 0xF7, 0xE5);
    sf::Color beige(0xEE, 0xCF, 0xA1);
    std::vector<sf::ConvexShape> matrice1 = createMatrixLosange(center,mat1_lines, points[3], milieux[1], milieux[0], beige, blanc);
    std::vector<sf::ConvexShape> matrice2 = createMatrixLosange(center,mat2_lines, points[2], milieux[5], milieux[1], blanc, beige);
    std::vector<sf::ConvexShape> matrice3 = createMatrixLosange(center,mat3_lines, points[4], milieux[0], milieux[4], blanc, beige);
    std::vector<sf::ConvexShape> matrice4 = createMatrixLosange(center,mat4_lines, points[5], milieux[4], milieux[3], beige, blanc);
    std::vector<sf::ConvexShape> matrice5 = createMatrixLosange(center,mat5_lines, points[1], milieux[2], milieux[5], beige, blanc);
    std::vector<sf::ConvexShape> matrice6 = createMatrixLosange(center,mat6_lines, points[0], milieux[3], milieux[2], blanc, beige);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création du texte pour les cases
    sf::Font font;
    if (!font.loadFromFile("./font/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    std::vector<std::string> lettresBas = {"a", "b", "c", "d", "e", "f", "g", "h"};
    std::vector<std::string> lettresHaut = {"8", "7", "6", "5", "9", "10", "11", "12"};
    std::vector<std::string> chiffresBasGauche = {"1", "2", "3", "4", "5", "6", "7", "8"};
    std::vector<std::string> lettresHautDroite = {"h", "g", "f", "e", "i", "j", "k", "l"};
    std::vector<std::string> lettresHautGauche = {"l", "k", "j", "i", "d", "c", "b", "a"};
    std::vector<std::string> lettresBasDroite = {"1", "2", "3", "4", "9", "10", "11", "12"};

    sf::Vector2f startBas = milieu(points[3], points2[4]) - sf::Vector2f(-30, 18);
    sf::Vector2f startHaut = milieu(points[5], points2[0]) - sf::Vector2f(-30, 18);
    sf::Vector2f startBasGauche = milieu(points[4], points2[5]) + sf::Vector2f(213, 370);
    sf::Vector2f startHautDroite = milieu(points[0], points2[1]) + sf::Vector2f(213, 360);
    sf::Vector2f startHautGauche = milieu(points[5], points2[0]) - sf::Vector2f(35, -15);
    sf::Vector2f startBasDroite = milieu(points[2], points2[3]) + sf::Vector2f(7, -55);

    std::vector<sf::Text> coordText;
    for (size_t i = 0; i < 8; ++i) {
        coordText.push_back(createText(lettresBas[i], startBas + sf::Vector2f(i * 57.0f, 0.0f), 28, sf::Color::Black, font));
        if(i > 4) {
            coordText.push_back(createText(lettresHaut[i], startHaut + sf::Vector2f(i * 56.0f, 0.0f), 28, sf::Color::Black, font));
        }
        else {
            coordText.push_back(createText(lettresHaut[i], startHaut + sf::Vector2f(i * 57.0f, 0.0f), 28, sf::Color::Black, font));
        }
        coordText.push_back(createText(chiffresBasGauche[i], startBasGauche - sf::Vector2f(i * 29.0f, i * 50.0f), 28, sf::Color::Black, font));
        coordText.push_back(createText(lettresHautDroite[i], startHautDroite - sf::Vector2f(i * 29.0f, i * 50.0f), 28, sf::Color::Black, font));
        coordText.push_back(createText(lettresHautGauche[i], startHautGauche + sf::Vector2f(7 - i * 29.0f, i * 50.0f), 28, sf::Color::Black, font));
        if(i > 4) {
            coordText.push_back(createText(lettresBasDroite[i], startBasDroite + sf::Vector2f(i * 28.0f, 7 - i * 50.0f), 28, sf::Color::Black, font));

        }
        else {
            coordText.push_back(createText(lettresBasDroite[i], startBasDroite + sf::Vector2f(i * 29.0f, 7 - i * 50.0f), 28, sf::Color::Black, font));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des pièces du jeu
    std::vector<std::string> texturePathWhite = {
        "WhiteRook.png", "WhiteKnight.png", "WhiteBishop.png", "WhiteKing.png",
        "WhiteQueen.png", "WhiteBishop.png", "WhiteKnight.png", "WhiteRook.png",
        "WhitePawn.png", "WhitePawn.png", "WhitePawn.png", "WhitePawn.png",
        "WhitePawn.png", "WhitePawn.png", "WhitePawn.png", "WhitePawn.png"
    };
    std::vector<sf::Texture> texturesWhite = loadTextures(texturePathWhite);
    std::vector<sf::Sprite> WhitePieces = CreerPiece(texturePathWhite, matrice1, matrice2, texturesWhite);

    std::vector<std::string> texturePathRed = {
        "RedRook.png", "RedKnight.png", "RedBishop.png", "RedKing.png",
        "RedQueen.png", "RedBishop.png", "RedKnight.png", "RedRook.png",
        "RedPawn.png", "RedPawn.png", "RedPawn.png", "RedPawn.png",
        "RedPawn.png", "RedPawn.png", "RedPawn.png", "RedPawn.png"
    };
    std::vector<sf::Texture> texturesRed = loadTextures(texturePathRed);
    std::vector<sf::Sprite> RedPieces = CreerPiece(texturePathRed, matrice4, matrice3, texturesRed);

    std::vector<std::string> texturePathBlack = {
        "BlackRook.png", "BlackKnight.png", "BlackBishop.png", "BlackKing.png",
        "BlackQueen.png", "BlackBishop.png", "BlackKnight.png", "BlackRook.png",
        "BlackPawn.png", "BlackPawn.png", "BlackPawn.png", "BlackPawn.png",
        "BlackPawn.png", "BlackPawn.png", "BlackPawn.png", "BlackPawn.png"
    };
    std::vector<sf::Texture> texturesBlack = loadTextures(texturePathBlack);
    std::vector<sf::Sprite> BlackPieces = CreerPiece(texturePathBlack, matrice5, matrice6, texturesBlack);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Chargement du fichier audio
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound/coup.ogg")) {
        return -1;  // Si le fichier n'a pas pu être chargé
    }
    sf::Sound sound;
    sound.setBuffer(buffer);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Variables pour le drag and drop
    bool isDragging = false;
    sf::Vector2f offsetImage;
    int selectedPieceIndex = -1;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Dessin de l'interface
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Vérification de si on clique sur l'image
                for (size_t i = 0; i < WhitePieces.size(); ++i) {
                    if (WhitePieces[i].getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        selectedPieceIndex = i;
                        offsetImage = mousePos - WhitePieces[i].getPosition();
                        break;
                    }
                }
                for (size_t i = 0; i < RedPieces.size(); ++i) {
                    if (RedPieces[i].getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        selectedPieceIndex = i + WhitePieces.size();
                        offsetImage = mousePos - RedPieces[i].getPosition();
                        break;
                    }
                }
                for (size_t i = 0; i < BlackPieces.size(); ++i) {
                    if (BlackPieces[i].getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        selectedPieceIndex = i + WhitePieces.size() + RedPieces.size();
                        offsetImage = mousePos - BlackPieces[i].getPosition();
                        break;
                    }
                }
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Déplacement de l'image avec la souris
            if (event.type == sf::Event::MouseMoved && isDragging) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (selectedPieceIndex < WhitePieces.size()) {
                    WhitePieces[selectedPieceIndex].setPosition(mousePos - offsetImage);
                } else if (selectedPieceIndex < WhitePieces.size() + RedPieces.size()) {
                    RedPieces[selectedPieceIndex - WhitePieces.size()].setPosition(mousePos - offsetImage);
                } else {
                    BlackPieces[selectedPieceIndex - WhitePieces.size() - RedPieces.size()].setPosition(mousePos - offsetImage);
                }
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Relâchement de l'image
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sound.play();
                isDragging = false;
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                bool placed = false;
                if(PieceDansMatrice(mousePos, matrice1)){
                    for (const auto& losange : matrice1) {
                        if (PieceDansLosange(losange, mousePos)) {
                            PlacementPiece(selectedPieceIndex,losange,WhitePieces,BlackPieces,RedPieces);
                            placed = true;
                            break;
                        }
                    }
                }
                else if(!placed && PieceDansMatrice(mousePos, matrice2)){
                    for (const auto& losange : matrice2) {
                        if (PieceDansLosange(losange, mousePos)) {
                            PlacementPiece(selectedPieceIndex,losange,WhitePieces,BlackPieces,RedPieces);
                            placed = true;
                            break;
                        }
                    }
                }
                else if(!placed && PieceDansMatrice(mousePos, matrice3)){
                    for (const auto& losange : matrice3) {
                        if (PieceDansLosange(losange, mousePos)) {
                            PlacementPiece(selectedPieceIndex,losange,WhitePieces,BlackPieces,RedPieces);
                            placed = true;
                            break;
                        }
                    }
                }
                else if(!placed && PieceDansMatrice(mousePos, matrice4)){
                    for (const auto& losange : matrice4) {
                        if (PieceDansLosange(losange, mousePos)) {
                            PlacementPiece(selectedPieceIndex,losange,WhitePieces,BlackPieces,RedPieces);
                            placed = true;
                            break;
                        }
                    }
                }
                else if(!placed && PieceDansMatrice(mousePos, matrice5)){
                    for (const auto& losange : matrice5) {
                        if (PieceDansLosange(losange, mousePos)) {
                            PlacementPiece(selectedPieceIndex,losange,WhitePieces,BlackPieces,RedPieces);
                            placed = true;
                            break;
                        }
                    }
                }
                else if(!placed && PieceDansMatrice(mousePos, matrice6)){
                    for (const auto& losange : matrice6) {
                        if (PieceDansLosange(losange, mousePos)) {
                            PlacementPiece(selectedPieceIndex,losange,WhitePieces,BlackPieces,RedPieces);
                            placed = true;
                            break;
                        }
                    }
                }
                
            }
        }

        window.clear(sf::Color::White);
        window.draw(hexagon);
        window.draw(hexagon2);
        
        for (const auto& text : coordText) {
            window.draw(text);
        }

        for (const auto& line : lines) {
            window.draw(line.data(), 2, sf::Lines);
        }
        for (const auto& losange : matrice1) {
            window.draw(losange);
        }
        for (const auto& losange : matrice2) {
            window.draw(losange);
        }
        for (const auto& losange : matrice3) {
            window.draw(losange);
        }
        for (const auto& losange : matrice4) {
            window.draw(losange);
        }
        for (const auto& losange : matrice5) {
            window.draw(losange);
        }
        for (const auto& losange : matrice6) {
            window.draw(losange);
        }

        for (const auto& piece : WhitePieces) {
            window.draw(piece);
        }

        for (const auto& piece : RedPieces) {
            window.draw(piece);
        }

        for (const auto& piece : BlackPieces) {
            window.draw(piece);
        }

        window.display();
    }
    return 0;
}
