#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

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
int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Hexagone Personnalisé");

    std::vector<float> side_lengths = {450, 460, 460, 450, 460, 460};
    std::vector<sf::Vector2f> points;

    float angle = 0;
    sf::Vector2f origin(250, 100); // Centre de l'écran
    points.push_back(origin + sf::Vector2f(side_lengths[0], 0));

    for (int i = 1; i < 6; i++) {
        angle += PI / 3; // 60°
        sf::Vector2f direction(std::cos(angle), std::sin(angle));
        points.push_back(points.back() + direction * side_lengths[i]);
    }

    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);
    for (size_t i = 0; i < 6; i++) {
        hexagon.setPoint(i, points[i]);
    }

    hexagon.setFillColor(sf::Color::Transparent);
    hexagon.setOutlineColor(sf::Color::White);
    hexagon.setOutlineThickness(2);

    // Calcul du centre de l’hexagone (moyenne des sommets)
    sf::Vector2f center(0, 0);
    for (const auto& p : points) {
        center += p;
    }
    center /= static_cast<float>(points.size());

    // Trouver le milieu d'une arête (ex: entre le 1er et le 2e sommet)
    sf::Vector2f matrice3_1 = (points[4] + points[3]) / 2.0f;
    sf::Vector2f matrice1_2 = (points[3] + points[2]) / 2.0f;
    sf::Vector2f matrice5_6 = (points[0] + points[1]) / 2.0f;
    sf::Vector2f matrice6_4 = (points[0] + points[5]) / 2.0f;
    sf::Vector2f matrice4_3 = (points[5] + points[4]) / 2.0f;
    sf::Vector2f matrice2_5 = (points[1] + points[2]) / 2.0f;

    // Création de la ligne
    sf::Vertex line1[] = {
        sf::Vertex(center, sf::Color::Red),
        sf::Vertex(matrice2_5, sf::Color::Red)
    };

    sf::Vertex line2[] = {
        sf::Vertex(center, sf::Color::Red),
        sf::Vertex(matrice1_2, sf::Color::Red)
    };

    sf::Vertex line3[] = {
        sf::Vertex(center, sf::Color::Red),
        sf::Vertex(matrice5_6, sf::Color::Red)
    };

    sf::Vertex line4[] = {
        sf::Vertex(center, sf::Color::Red),
        sf::Vertex(matrice6_4, sf::Color::Red)
    };

    sf::Vertex line5[] = {
        sf::Vertex(center, sf::Color::Red),
        sf::Vertex(matrice4_3, sf::Color::Red)
    };

    sf::Vertex line6[] = {
        sf::Vertex(center, sf::Color::Red),
        sf::Vertex(matrice3_1, sf::Color::Red)
    };

    // Création des lignes de la matrice 5
    sf::Vector2f mat5_1_start = center + 0.25f * (matrice5_6 - center);// 25% de la distance
    sf::Vector2f mat5_1_end = (1 - 0.375f) * points[1] + 0.375f * points[2];
    sf::Vertex mat5_1[] = {
        sf::Vertex(mat5_1_start, sf::Color::Green),
        sf::Vertex(mat5_1_end, sf::Color::Green)
    };

    sf::Vector2f mat5_2_start = center + 0.50f * (matrice5_6 - center);// 50% de la distance
    sf::Vector2f mat5_2_end = (1 - 0.25f) * points[1] + 0.25f * points[2];
    sf::Vertex mat5_2[] = {
        sf::Vertex(mat5_2_start, sf::Color::Green),
        sf::Vertex(mat5_2_end, sf::Color::Green)
    };

    sf::Vector2f mat5_3_start = center + 0.75f * (matrice5_6 - center);// 75% de la distance
    sf::Vector2f mat5_3_end = (1 - 0.125f) * points[1] + 0.125f * points[2];
    sf::Vertex mat5_3[] = {
        sf::Vertex(mat5_3_start, sf::Color::Green),
        sf::Vertex(mat5_3_end, sf::Color::Green)
    };

    sf::Vector2f mat5_4_start = center + 0.25f * (matrice2_5 - center);// 25% de la distance
    sf::Vector2f mat5_4_end = (1 - 0.625f) * points[0] + 0.625f * points[1];
    sf::Vertex mat5_4[] = {
        sf::Vertex(mat5_4_start, sf::Color::Green),
        sf::Vertex(mat5_4_end, sf::Color::Green)
    };

    sf::Vector2f mat5_5_start = center + 0.50f * (matrice2_5 - center);// 50% de la distance
    sf::Vector2f mat5_5_end = (1 - 0.750f) * points[0] + 0.750f * points[1];
    sf::Vertex mat5_5[] = {
        sf::Vertex(mat5_5_start, sf::Color::Green),
        sf::Vertex(mat5_5_end, sf::Color::Green)
    };

    sf::Vector2f mat5_6_start = center + 0.75f * (matrice2_5 - center);// 75% de la distance
    sf::Vector2f mat5_6_end = (1 - 0.875f) * points[0] + 0.875f * points[1];
    sf::Vertex mat5_6[] = {
        sf::Vertex(mat5_6_start, sf::Color::Green),
        sf::Vertex(mat5_6_end, sf::Color::Green)
    };



    // Création du losange
    sf::ConvexShape losange;
    losange.setPointCount(4);
    losange.setPoint(0, center);
    losange.setPoint(1, mat5_1_start);
    losange.setPoint(2, mat5_4_start + 0.25f * (mat5_4_end - mat5_4_start));
    losange.setPoint(3, mat5_4_start);
    losange.setFillColor(sf::Color::Blue);
    losange.setOutlineColor(sf::Color::Green);
    losange.setOutlineThickness(2);

    sf::ConvexShape losange2;
    losange2.setPointCount(4);
    losange2.setPoint(0, mat5_1_start);
    losange2.setPoint(1, mat5_2_start);
    losange2.setPoint(2, mat5_4_start + 0.5f * (mat5_4_end - mat5_4_start));
    losange2.setPoint(3, mat5_4_start + 0.25f * (mat5_4_end - mat5_4_start));
    losange2.setFillColor(sf::Color::Black);
    losange2.setOutlineColor(sf::Color::Green);
    losange2.setOutlineThickness(2);

    sf::ConvexShape losange3;
    losange3.setPointCount(4);
    losange3.setPoint(0, mat5_2_start);
    losange3.setPoint(1, mat5_3_start);
    losange3.setPoint(2, mat5_4_start + 0.75f * (mat5_4_end - mat5_4_start));
    losange3.setPoint(3, mat5_4_start + 0.5f * (mat5_4_end - mat5_4_start));
    losange3.setFillColor(sf::Color::Black);
    losange3.setOutlineColor(sf::Color::Green);
    losange3.setOutlineThickness(2);

    bool losangeFilled = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (isPointInConvexShape(losange, mousePos)) {
                        // Si le clic est à l'intérieur du losange, on change sa couleur
                        if (losangeFilled) {
                            losange.setFillColor(sf::Color::Blue); // Retourne à la couleur d'origine
                        } else {
                            losange.setFillColor(sf::Color::Red); // Change la couleur
                        }
                        losangeFilled = !losangeFilled; // Bascule l'état
                    }
                }
            }
        }

        window.clear();
        window.draw(hexagon);
        window.draw(line1, 2, sf::Lines);
        window.draw(line2, 2, sf::Lines);
        window.draw(line3, 2, sf::Lines);
        window.draw(line4, 2, sf::Lines);
        window.draw(line5, 2, sf::Lines);
        window.draw(line6, 2, sf::Lines);
        window.draw(mat5_1, 2, sf::Lines);
        window.draw(mat5_2, 2, sf::Lines);
        window.draw(mat5_3, 2, sf::Lines);
        window.draw(mat5_4, 2, sf::Lines);
        window.draw(mat5_5, 2, sf::Lines);
        window.draw(mat5_6, 2, sf::Lines);
       

        // Dessiner le losange avec une couleur de remplissage si nécessaire
        if (losangeFilled) {
            losange.setFillColor(sf::Color::Blue);
        } else {
            losange.setFillColor(sf::Color::Transparent);
        }
        window.draw(losange); 
        window.draw(losange2); 
        window.draw(losange3);

        window.display();

    }
    return 0;
}
