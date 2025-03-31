#include <SFML/Graphics.hpp>

int main() {
    // Dimensions de la fenêtre
    const int windowWidth = 400; // Ajusté pour une matrice 4x4
    const int windowHeight = 400; // Ajusté pour une matrice 4x4

    // Dimensions de la matrice
    const int rows = 4; // Nombre de lignes
    const int cols = 4; // Nombre de colonnes
    const int tileSize = 100; // Taille d'une case

    // Création de la matrice
    sf::RectangleShape matrix[rows][cols];

    // Initialisation de la matrice
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j].setSize(sf::Vector2f(tileSize, tileSize));
            matrix[i][j].setPosition(j * tileSize, i * tileSize);

            // Alterner les couleurs
            if ((i + j) % 2 == 0) {
                matrix[i][j].setFillColor(sf::Color(255, 228, 181)); // Couleur beige
            } else {
                matrix[i][j].setFillColor(sf::Color(240, 240, 240)); // Couleur blanche
            }
        }
    }

    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Matrice 4x4 SFML");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Dessin de la matrice
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                window.draw(matrix[i][j]);
            }
        }

        window.display();
    }

    return 0;
}