#include <SFML/Graphics.hpp>
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
    shapes.push_back(createLosange( mat_lines[8] + 0.25f * (mat_lines[9] - mat_lines[8]), mat_lines[8] + 0.5f * (mat_lines[9] - mat_lines[8]),mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]) , mat_lines[10] + 0.25f * (mat_lines[11] - mat_lines[10]), color2, sf::Color::Black));
    shapes.push_back(createLosange( mat_lines[8] + 0.5f * (mat_lines[9] - mat_lines[8]), mat_lines[8] + 0.75f * (mat_lines[9] - mat_lines[8]), mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]), mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]), color1, sf::Color::Black));
    shapes.push_back(createLosange( mat_lines[8] + 0.75f * (mat_lines[9] - mat_lines[8]), mat_lines[9], mat_lines[11] , mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]), color2, sf::Color::Black));

    shapes.push_back(createLosange(mat_lines[10], mat_lines[10] + 0.25f * (mat_lines[11] - mat_lines[10]), mat_lines[1], milieu2, color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[10] + 0.25f * (mat_lines[11] - mat_lines[10]), mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]),mat_lines[3] ,mat_lines[1] , color1, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[10] + 0.5f * (mat_lines[11] - mat_lines[10]) ,mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]) ,mat_lines[5] ,mat_lines[3] , color2, sf::Color::Black));
    shapes.push_back(createLosange(mat_lines[10] + 0.75f * (mat_lines[11] - mat_lines[10]), mat_lines[5], point, mat_lines[11], color1, sf::Color::Black));
    return shapes;
}


sf::Text createText(const std::string& textStr, const sf::Vector2f& position, unsigned int characterSize, sf::Color color, sf::Font& font) {
    sf::Text text;
    text.setString(textStr);
    text.setFont(font);  // Utilisation de la police passée en argument
    text.setPosition(position);
    text.setFillColor(color);
    return text;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Echec Yalta");
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
    hexagon2.setOutlineThickness(10);

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
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    sf::Text aBas = createText("a", milieu(points[3], points2[4]) - sf::Vector2f(-30, 18), 30, sf::Color::Black, font);
    sf::Text bBas = createText("b", milieu(points[3], points2[4]) - sf::Vector2f(-87, 18), 30, sf::Color::Black, font);
    sf::Text cBas = createText("c", milieu(points[3], points2[4]) - sf::Vector2f(-144, 18), 30, sf::Color::Black, font);
    sf::Text dBas = createText("d", milieu(points[3], points2[4]) - sf::Vector2f(-201, 18), 30, sf::Color::Black, font);
    sf::Text eBas = createText("e", milieu(points[3], points2[4]) - sf::Vector2f(-258, 18), 30, sf::Color::Black, font);
    sf::Text fBas = createText("f", milieu(points[3], points2[4]) - sf::Vector2f(-315, 18), 30, sf::Color::Black, font);
    sf::Text gBas = createText("g", milieu(points[3], points2[4]) - sf::Vector2f(-372, 18), 30, sf::Color::Black, font);
    sf::Text hBas = createText("h", milieu(points[3], points2[4]) - sf::Vector2f(-429, 18), 30, sf::Color::Black, font);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Dessin de l'interface
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            }
        }


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);
        for (auto& losange : matrice1) {
            if (losange.getGlobalBounds().contains(mouseWorldPos)) {
                if (losange.getFillColor() == beige) {
                    losange.setFillColor(blanc);
                } else {
                    losange.setFillColor(beige);
                }

            }
        }

        window.clear(sf::Color::White);
        window.draw(hexagon);
        window.draw(hexagon2);
        window.draw(aBas);
        window.draw(bBas);
        window.draw(cBas);
        window.draw(dBas);
        window.draw(eBas);
        window.draw(fBas);
        window.draw(gBas);
        window.draw(hBas);
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
    window.display();
    }
    return 0;
}
