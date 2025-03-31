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

    sf::ConvexShape losange = createLosange(center, center + 0.25f * (milieux[2] - center), center + 0.25f * (matrice2_5 - center) + 0.25f * (mat5_4_end - mat5_4_start), milieux[5], sf::Color::Blue, sf::Color::Green);
    //sf::ConvexShape losange2 = createLosange(milieux[1], milieux[1] + 0.25f * (points[2] - milieux[1]), milieux[5] + 0.5f * (points[1] - milieux[5]), milieux[5] + 0.25f * (points[1] - milieux[5]), sf::Color::Black, sf::Color::Green);
    //sf::ConvexShape losange3 = createLosange(milieux[1] + 0.25f * (points[2] - milieux[1]), milieux[1] + 0.5f * (points[2] - milieux[1]), milieux[5] + 0.75f * (points[1] - milieux[5]), milieux[5] + 0.5f * (points[1] - milieux[5]), sf::Color::Black, sf::Color::Green);
    
    bool losangeFilled = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (isPointInConvexShape(losange, mousePos)) {
                    losange.setFillColor(losangeFilled ? sf::Color::Blue : sf::Color::Red);
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
        window.display();
    }
    return 0;
}
