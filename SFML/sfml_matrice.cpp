#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    int taille = 4; // Taille des matrices
    float cellSize = 100.f; // Taille des cellules
    float offsetX = taille * cellSize + 20.f; // Décalage pour la deuxième matrice

    // Création des matrices
    std::vector<std::vector<int>> matrice1(taille, std::vector<int>(taille, 0));
    std::vector<std::vector<int>> matrice2(taille, std::vector<int>(taille, 0));

    // Initialisation des matrices
    matrice1[0][0] = 1;
    matrice1[1][1] = 2;
    matrice1[2][2] = 3;
    matrice1[3][3] = 3;
    
    matrice2[0][3] = 1;
    matrice2[1][2] = 2;
    matrice2[2][1] = 3;
    matrice2[3][0] = 3;

    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(2 * taille * cellSize + 40, taille * cellSize), "Deux Matrices 4x4");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Dessin de la première matrice
        for (int i = 0; i < taille; ++i) {
            for (int j = 0; j < taille; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                if (matrice1[i][j] == 1) cell.setFillColor(sf::Color::Red);
                else if (matrice1[i][j] == 2) cell.setFillColor(sf::Color::Green);
                else if (matrice1[i][j] == 3) cell.setFillColor(sf::Color::Blue);
                else cell.setFillColor(sf::Color::White);

                window.draw(cell);
            }
        }

        // Dessin de la deuxième matrice
        for (int i = 0; i < taille; ++i) {
            for (int j = 0; j < taille; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize + offsetX, i * cellSize);

                if (matrice2[i][j] == 1) cell.setFillColor(sf::Color::Red);
                else if (matrice2[i][j] == 2) cell.setFillColor(sf::Color::Green);
                else if (matrice2[i][j] == 3) cell.setFillColor(sf::Color::Blue);
                else cell.setFillColor(sf::Color::White);

                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}
