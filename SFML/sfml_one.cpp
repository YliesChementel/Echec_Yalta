#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

// Fonction qui crée un polygone avec des angles et une longueur de côté donnés
sf::ConvexShape createPolygon(const std::vector<float>& angles, float length, const sf::Vector2f& startPosition) {
    // Créer un objet ConvexShape pour dessiner le polygone
    sf::ConvexShape shape;
    shape.setPointCount(angles.size());  // Le nombre de points est le même que le nombre d'angles

    sf::Vector2f currentPosition = startPosition;  // Point de départ
    float currentAngle = 0.f;  // Angle de départ (0° initialement, regardant vers la droite)

    // Calculer les positions des points
    for (size_t i = 0; i < angles.size(); ++i) {
        // Convertir l'angle en radians
        float angleInRadians = currentAngle * M_PI / 180.f;

        // Calculer la position suivante en utilisant la trigonométrie
        float x = currentPosition.x + length * cos(angleInRadians);
        float y = currentPosition.y + length * sin(angleInRadians);

        // Définir le point du polygone
        shape.setPoint(i, sf::Vector2f(x, y));

        // Mettre à jour la position pour le prochain sommet
        currentPosition = sf::Vector2f(x, y);

        // Mettre à jour l'angle pour le prochain côté
        currentAngle += angles[i];  // Ajouter l'angle pour le prochain côté
    }

    return shape;
}

int main() {
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Polygone avec Angles");

    // Paramètres de la forme
    std::vector<float> angles = {115.f,60.f, 115.f,70.f};  // Les angles en degrés
    std::vector<float> angles2 = {110.f,65.f, 110.f,75.f};  // Les angles en degrés
    float length = 100.f;  // Longueur des côtés (vous pouvez ajuster)
    sf::Vector2f startPosition(400.f, 300.f);  // Point de départ (centre ou coin)
    sf::Vector2f startPosition2(550.f, 300.f);  // Point de départ (centre ou coin)

    // Créer le polygone en utilisant la fonction createPolygon
    sf::ConvexShape shape = createPolygon(angles, length, startPosition);
    sf::ConvexShape shape1 = createPolygon(angles2, length, startPosition2);

    // Boucle principale de la fenêtre
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer et dessiner la forme
        window.clear();
        window.draw(shape);
        window.draw(shape1);
        window.display();
    }

    return 0;
}
