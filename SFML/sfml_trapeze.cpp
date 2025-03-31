#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
    int taille = 4; // Taille de la matrice
    float cellSize = 100.f; // Taille de base des cellules
    float perspectiveFactor = 0.5f; // Facteur de réduction en hauteur
    float depthFactor = 0.3f; // Facteur pour rétrécir les cases du haut

    sf::RenderWindow window(sf::VideoMode(600, 600), "Matrice en Perspective");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::VertexArray grid(sf::Quads, taille * taille * 4);

        for (int i = 0; i < taille; ++i) {
            for (int j = 0; j < taille; ++j) {
                // Facteur de rétrécissement en hauteur
                float scaleY = 1.0f - (i * depthFactor / taille);
                float scaleX = 1.0f - (i * depthFactor / taille);
                
                float x0 = j * cellSize * scaleX;
                float x1 = (j + 1) * cellSize * scaleX;
                float y0 = i * cellSize * scaleY;
                float y1 = (i + 1) * cellSize * scaleY;

                // Décalage en X pour simuler la perspective (shear)
                float shearX = (taille - i) * 20.f;

                grid[(i * taille + j) * 4 + 0].position = sf::Vector2f(x0 + shearX, y0);
                grid[(i * taille + j) * 4 + 1].position = sf::Vector2f(x1 + shearX, y0);
                grid[(i * taille + j) * 4 + 2].position = sf::Vector2f(x1 + shearX - 20, y1);
                grid[(i * taille + j) * 4 + 3].position = sf::Vector2f(x0 + shearX - 20, y1);

                // Couleur alternée
                if ((i + j) % 2 == 0)
                    grid[(i * taille + j) * 4].color = sf::Color(200, 170, 120);
                else
                    grid[(i * taille + j) * 4].color = sf::Color(240, 230, 200);
            }
        }

        window.draw(grid);
        window.display();
    }
    return 0;
}