#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window({640, 480}, "Hexagons", sf::Style::Default, sf::ContextSettings(0, 0, 8));

    sf::CircleShape hexagon(100, 6);
    hexagon.setOutlineColor(sf::Color::Black);
    hexagon.setOutlineThickness(5);
    hexagon.setFillColor(sf::Color::White);
    hexagon.setOrigin(25, 25);
    hexagon.setPosition(250, 100);
    hexagon.setRotation(90);


    // Créer un losange avec un ConvexShape
    sf::ConvexShape losange;
    losange.setPointCount(4); // Un losange a 4 points

    // Définir les coordonnées des 4 points du losange
    losange.setPoint(0, sf::Vector2f(400.f, 250.f)); // Point supérieur
    losange.setPoint(1, sf::Vector2f(500.f, 300.f)); // Point à droite
    losange.setPoint(2, sf::Vector2f(400.f, 400.f)); // Point inférieur
    losange.setPoint(3, sf::Vector2f(300.f, 300.f)); // Point à gauche

    // Donner une couleur au losange
    losange.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);


        window.draw(hexagon);
        window.draw(losange);
        
        window.display();
    }
}