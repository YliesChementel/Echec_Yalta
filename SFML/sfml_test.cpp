#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Carrés inclinés");

    sf::ConvexShape square1, square2, square3, square4;
    square1.setPointCount(4);
    square2.setPointCount(4);
    square3.setPointCount(4);
    square4.setPointCount(4);

    // Définir les points pour chaque carré incliné
    square1.setPoint(0, sf::Vector2f(100, 200));
    square1.setPoint(1, sf::Vector2f(200, 180));
    square1.setPoint(2, sf::Vector2f(220, 250));
    square1.setPoint(3, sf::Vector2f(120, 270));
    square1.setFillColor(sf::Color(240, 220, 180));

    square2.setPoint(0, sf::Vector2f(200, 180));
    square2.setPoint(1, sf::Vector2f(300, 160));
    square2.setPoint(2, sf::Vector2f(320, 230));
    square2.setPoint(3, sf::Vector2f(220, 250));
    square2.setFillColor(sf::Color(255, 245, 225));

    square3.setPoint(0, sf::Vector2f(300, 160));
    square3.setPoint(1, sf::Vector2f(400, 140));
    square3.setPoint(2, sf::Vector2f(420, 210));
    square3.setPoint(3, sf::Vector2f(320, 230));
    square3.setFillColor(sf::Color(240, 220, 180));

    square4.setPoint(0, sf::Vector2f(400, 140));
    square4.setPoint(1, sf::Vector2f(500, 120));
    square4.setPoint(2, sf::Vector2f(520, 190));
    square4.setPoint(3, sf::Vector2f(420, 210));
    square4.setFillColor(sf::Color(255, 245, 225));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(square1);
        window.draw(square2);
        window.draw(square3);
        window.draw(square4);
        window.display();
    }

    return 0;
}
