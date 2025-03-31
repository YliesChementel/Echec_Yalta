#include <SFML/Graphics.hpp>
#include <iostream>

// Fonction pour appliquer la transformation de perspective
sf::Vector2f applyPerspective(const sf::Vector2f& point, float depth, float perspectiveFactor) {
    float scale = perspectiveFactor / (perspectiveFactor + depth);
    return sf::Vector2f(point.x * scale, point.y * scale);
}

int main() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Perspective 3D Effect");

    // Définir les points du carré en 2D
    sf::Vector2f squarePoints[4] = {
        {150, 150},
        {350, 150},
        {350, 350},
        {150, 350}
    };

    // Profondeur des points (plus la profondeur est grande, plus le point est "loin")
    float depths[4] = {100, 100, 200, 200};

    // Facteur de perspective
    float perspectiveFactor = 200.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Appliquer la transformation de perspective aux points du carré
        sf::Vertex squareVertices[5] = {
            sf::Vertex(applyPerspective(squarePoints[0], depths[0], perspectiveFactor)),
            sf::Vertex(applyPerspective(squarePoints[1], depths[1], perspectiveFactor)),
            sf::Vertex(applyPerspective(squarePoints[2], depths[2], perspectiveFactor)),
            sf::Vertex(applyPerspective(squarePoints[3], depths[3], perspectiveFactor)),
            sf::Vertex(applyPerspective(squarePoints[0], depths[0], perspectiveFactor)) // Pour fermer le carré
        };

        // Dessiner le carré avec l'effet de perspective
        window.draw(squareVertices, 5, sf::Lines);

        window.display();
    }

    return 0;
}
