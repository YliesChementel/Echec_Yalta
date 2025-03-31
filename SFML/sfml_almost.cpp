#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>


int main() {
    int taille = 4; // Taille des matrices
    float cellSize = 100.f; // Taille des cellules
    float offsetX = taille * cellSize + 20.f; // Décalage pour la deuxième matrice

    float offsetX2 = taille * cellSize + 100.f; // Décalage pour la troisième matrice

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
       /* for (int i = 0; i < taille; ++i) {
            for (int j = 0; j < taille; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                if (matrice1[i][j] == 1) cell.setFillColor(sf::Color::Red);
                else if (matrice1[i][j] == 2) cell.setFillColor(sf::Color::Green);
                else if (matrice1[i][j] == 3) cell.setFillColor(sf::Color::Blue);
                else cell.setFillColor(sf::Color::White);

                window.draw(cell);
            }
        }*/

        // Dessin de la deuxième matrice
        /*sf::Transform transform;
        float angle = 30.f; // Angle d'inclinaison en degrés
        
        // Calcul du centre de la matrice pour pivoter autour d'un point central
        sf::Vector2f center(offsetX + (taille * cellSize) / 2, (taille * cellSize) / 2);
        
        // Appliquer la transformation
        transform.translate(center);   // Déplacer au centre
        transform.rotate(angle);       // Appliquer la rotation
        transform.translate(-center);  // Revenir à la position initiale
        
        // Dessin de la deuxième matrice inclinée
        for (int i = 0; i < taille; ++i) {
            for (int j = 0; j < taille; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize + offsetX, i * cellSize);
        
                // Couleurs selon la valeur dans la matrice
                if (matrice2[i][j] == 1) cell.setFillColor(sf::Color::Red);
                else if (matrice2[i][j] == 2) cell.setFillColor(sf::Color::Green);
                else if (matrice2[i][j] == 3) cell.setFillColor(sf::Color::Blue);
                else cell.setFillColor(sf::Color::White);
        
                // Dessiner la cellule avec la transformation
                window.draw(cell, transform);
            }
        }*/
        

        /*sf::Transform transform2;
        float scaleX = 1.5f;  // Étire horizontalement
        float scaleY = 0.5f;  // Écrase verticalement
        //float angle2 = 30.f;   // Angle d'inclinaison

        // Centre de la matrice pour pivot
        sf::Vector2f center2(offsetX + (taille * cellSize) / 2, (taille * cellSize) / 2);

        transform2.translate(center2);   
        //transform2.rotate(angle2);       
        transform2.scale(scaleX, scaleY);  // Ajout de l'écrasement
        transform2.translate(-center2);

        // Dessiner la matrice avec l'écrasement
        for (int i = 0; i < taille; ++i) {
            for (int j = 0; j < taille; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize + offsetX, i * cellSize);

                if (matrice2[i][j] == 1) cell.setFillColor(sf::Color::Red);
                else if (matrice2[i][j] == 2) cell.setFillColor(sf::Color::Green);
                else if (matrice2[i][j] == 3) cell.setFillColor(sf::Color::Blue);
                else cell.setFillColor(sf::Color::White);

                window.draw(cell, transform2);
            }
        }*/

        sf::Transform shearTransform;
        float shearX = std::tan(30 * 3.14159265 / 180);  // Shear pour obtenir 120° et 60°

        // Appliquer la transformation
        shearTransform = sf::Transform(1, shearX, 0,   // Shear horizontal
                                    0, 1, 0,        // Pas de shear vertical
                                    0, 0, 1);

        // Dessin de la deuxième matrice écrasée
        for (int i = 0; i < taille; ++i) {
            for (int j = 0; j < taille; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize , i * cellSize);

                if (matrice2[i][j] == 1) cell.setFillColor(sf::Color::Red);
                else if (matrice2[i][j] == 2) cell.setFillColor(sf::Color::Green);
                else if (matrice2[i][j] == 3) cell.setFillColor(sf::Color::Blue);
                else cell.setFillColor(sf::Color::White);

                // Appliquer l’écrasement (shear) à toute la matrice
                window.draw(cell, shearTransform);
            }
        }

        window.display();
    }

    return 0;
}
