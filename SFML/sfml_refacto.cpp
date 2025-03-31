#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <array>

const float PI = 3.14159265359f;

bool isPointInConvexShape(const sf::ConvexShape& shape, const sf::Vector2i& point) {
    int count = shape.getPointCount();
    bool inside = false;

    for (int i = 0, j = count - 1; i < count; j = i++) {
        sf::Vector2f vi = shape.getPoint(i);
        sf::Vector2f vj = shape.getPoint(j);
        
        if ((vi.y > point.y) != (vj.y > point.y) &&
            (point.x < (vj.x - vi.x) * (point.y - vi.y) / (vj.y - vi.y) + vi.x)) {
            inside = !inside;
        }
    }
    return inside;
}

sf::Vector2f milieu(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return (p1 + p2) / 2.0f;
}

std::array<sf::Vertex, 2> createLine(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color) {
    return {sf::Vertex(start, color), sf::Vertex(end, color)};
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

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Hexagone Personnalisé");
    std::vector<float> side_lengths = {450, 460, 460, 450, 460, 460};
    std::vector<sf::Vector2f> points;
    
    float angle = 0;
    sf::Vector2f origin(250, 100);
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

    std::vector<sf::Vector2f> milieux = {
        milieu(points[4], points[3]), milieu(points[3], points[2]),
        milieu(points[0], points[1]), milieu(points[0], points[5]),
        milieu(points[5], points[4]), milieu(points[1], points[2])
    };

    std::vector<std::array<sf::Vertex, 2>> lines;
    for (const auto& m : milieux) {
        lines.push_back(createLine(center, m, sf::Color::Red));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Création des lignes de la matrice 5
    sf::Vector2f mat5_1_start = center + 0.25f * (milieux[2] - center);// 25% de la distance
    sf::Vector2f mat5_1_end = (1 - 0.375f) * points[1] + 0.375f * points[2];

    sf::Vector2f mat5_2_start = center + 0.50f * (milieux[2] - center);// 50% de la distance
    sf::Vector2f mat5_2_end = (1 - 0.25f) * points[1] + 0.25f * points[2];

    sf::Vector2f mat5_3_start = center + 0.75f * (milieux[2] - center);// 75% de la distance
    sf::Vector2f mat5_3_end = (1 - 0.125f) * points[1] + 0.125f * points[2];

    sf::Vector2f mat5_4_start = center + 0.25f * (milieux[5] - center);// 25% de la distance
    sf::Vector2f mat5_4_end = (1 - 0.625f) * points[0] + 0.625f * points[1];

    sf::Vector2f mat5_5_start = center + 0.50f * (milieux[5] - center);// 50% de la distance
    sf::Vector2f mat5_5_end = (1 - 0.750f) * points[0] + 0.750f * points[1];

    sf::Vector2f mat5_6_start = center + 0.75f * (milieux[5] - center);// 75% de la distance
    sf::Vector2f mat5_6_end = (1 - 0.875f) * points[0] + 0.875f * points[1];

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::ConvexShape losange = createLosange(center, mat5_1_start, mat5_4_start + 0.25f * (mat5_4_end - mat5_4_start), mat5_4_start, sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange2 = createLosange(mat5_1_start, mat5_2_start, mat5_4_start + 0.5f * (mat5_4_end - mat5_4_start), mat5_4_start + 0.25f * (mat5_4_end - mat5_4_start), sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange3 = createLosange(mat5_2_start, mat5_3_start, mat5_4_start + 0.75f * (mat5_4_end - mat5_4_start), mat5_4_start + 0.5f * (mat5_4_end - mat5_4_start), sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange4 = createLosange(mat5_3_start, milieux[2], mat5_4_end, mat5_4_start + 0.75f * (mat5_4_end - mat5_4_start), sf::Color::Black, sf::Color::Green);

    sf::ConvexShape losange5 = createLosange(mat5_4_start, mat5_4_start + 0.25f * (mat5_4_end - mat5_4_start), mat5_5_start + 0.25f * (mat5_5_end - mat5_5_start),mat5_5_start , sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange6 = createLosange(mat5_4_start + 0.25f * (mat5_4_end - mat5_4_start),mat5_4_start + 0.5f * (mat5_4_end - mat5_4_start), mat5_5_start + 0.5f * (mat5_5_end - mat5_5_start), mat5_5_start + 0.25f * (mat5_5_end - mat5_5_start) , sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange7 = createLosange(mat5_4_start + 0.5f * (mat5_4_end - mat5_4_start),mat5_4_start + 0.75f * (mat5_4_end - mat5_4_start),mat5_5_start + 0.75f * (mat5_5_end - mat5_5_start), mat5_5_start + 0.5f * (mat5_5_end - mat5_5_start), sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange8 = createLosange(mat5_4_start + 0.75f * (mat5_4_end - mat5_4_start), mat5_4_end, mat5_5_end, mat5_5_start + 0.75f * (mat5_5_end - mat5_5_start), sf::Color::Black, sf::Color::Green);
    
    sf::ConvexShape losange9 = createLosange(mat5_5_start, mat5_5_start + 0.25f * (mat5_5_end - mat5_5_start), mat5_6_start + 0.25f * (mat5_6_end - mat5_6_start), mat5_6_start, sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange10 = createLosange( mat5_5_start + 0.25f * (mat5_5_end - mat5_5_start), mat5_5_start + 0.5f * (mat5_5_end - mat5_5_start),mat5_6_start + 0.5f * (mat5_6_end - mat5_6_start) , mat5_6_start + 0.25f * (mat5_6_end - mat5_6_start), sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange11 = createLosange( mat5_5_start + 0.5f * (mat5_5_end - mat5_5_start), mat5_5_start + 0.75f * (mat5_5_end - mat5_5_start), mat5_6_start + 0.75f * (mat5_6_end - mat5_6_start), mat5_6_start + 0.5f * (mat5_6_end - mat5_6_start), sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange12 = createLosange( mat5_5_start + 0.75f * (mat5_5_end - mat5_5_start), mat5_5_end, mat5_6_end , mat5_6_start + 0.75f * (mat5_6_end - mat5_6_start), sf::Color::Black, sf::Color::Green);

    sf::ConvexShape losange13 = createLosange(mat5_6_start, mat5_6_start + 0.25f * (mat5_6_end - mat5_6_start), mat5_1_end,milieux[5] , sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange14 = createLosange(mat5_6_start + 0.25f * (mat5_6_end - mat5_6_start), mat5_6_start + 0.5f * (mat5_6_end - mat5_6_start),mat5_2_end ,mat5_1_end , sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange15 = createLosange(mat5_6_start + 0.5f * (mat5_6_end - mat5_6_start) ,mat5_6_start + 0.75f * (mat5_6_end - mat5_6_start) ,mat5_3_end ,mat5_2_end , sf::Color::Black, sf::Color::Green);
    sf::ConvexShape losange16 = createLosange(mat5_6_start + 0.75f * (mat5_6_end - mat5_6_start), mat5_3_end, points[1], mat5_6_end, sf::Color::Black, sf::Color::Green);

    
    
    bool losangeFilled = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (isPointInConvexShape(losange, mousePos)) {
                    losange.setFillColor(losangeFilled ? sf::Color::Blue : sf::Color::Black);
                    losangeFilled = !losangeFilled;
               }
            }
        }

        window.clear();
        window.draw(hexagon);
        for (const auto& line : lines) {
            window.draw(line.data(), 2, sf::Lines);
        }
        window.draw(losange);
        window.draw(losange2);
        window.draw(losange3);
        window.draw(losange4);
        window.draw(losange5);
        window.draw(losange6);
        window.draw(losange7);
        window.draw(losange8);
        window.draw(losange9);
        window.draw(losange10);
        window.draw(losange11);
        window.draw(losange12);
        window.draw(losange13);
        window.draw(losange14);
        window.draw(losange15);
        window.draw(losange16);
        window.display();
    }
    return 0;
}
