#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    const int windowWidth = 600;
    const int windowHeight = 400;
    const int rows = 4;
    const int cols = 4;
    const int tileSize = 50; // Réduit pour mieux voir l'ensemble

    sf::ConvexShape matrix[rows][cols];

    // Angles en radians
    float angle120 = 2.0f * M_PI / 3.0f; // 120 degrés
    float angle60 = M_PI / 3.0f; // 60 degrés

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j].setPointCount(4);

            // Position de base pour chaque case
            float baseX = 100 + j * tileSize - i * (tileSize / 2.0f);
            float baseY = 100 + i * (tileSize * 0.866f); // 0.866 est approximativement sin(60°)

            // Définition des quatre points de chaque case
            matrix[i][j].setPoint(0, sf::Vector2f(baseX, baseY)); // Angle droit
            matrix[i][j].setPoint(1, sf::Vector2f(baseX + tileSize, baseY)); // Angle 120°
            matrix[i][j].setPoint(2, sf::Vector2f(baseX + tileSize * 1.5f, 
                                                baseY + tileSize * 0.866f)); // Angle droit
            matrix[i][j].setPoint(3, sf::Vector2f(baseX + tileSize * 0.5f, 
                                                baseY + tileSize * 0.866f)); // Angle 60°

            // Couleurs alternées
            if ((i + j) % 2 == 0) {
                matrix[i][j].setFillColor(sf::Color(255, 228, 181));
            } else {
                matrix[i][j].setFillColor(sf::Color(240, 240, 240));
            }
        }
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Matrix");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        
        // Draw the matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                window.draw(matrix[i][j]);
            }
        }

        window.display();
    }

    return 0;
}