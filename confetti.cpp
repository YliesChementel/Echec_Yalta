#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Confetti {
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

class ConfettiEmitter {
public:
    ConfettiEmitter() {
        // Initialise le générateur de nombres aléatoires
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void update() {
        // Crée de nouveaux confettis
        if (std::rand() % 10 == 0) {
            Confetti confetti;
            confetti.shape.setRadius(5 + std::rand() % 10); // Taille aléatoire
            confetti.shape.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256)); // Couleur aléatoire
            confetti.shape.setPosition(sf::Vector2f(std::rand() % 800, 0)); // Position aléatoire en haut de l'écran
            confetti.velocity = sf::Vector2f(std::rand() % 3 - 1, 1 + std::rand() % 3); // Vitesse aléatoire (la gravité)
            confettis.push_back(confetti);
        }

        // Mise à jour de la position des confettis
        for (auto& confetti : confettis) {
            confetti.shape.move(confetti.velocity); // Déplacement selon la vitesse
            // Si le confetti sort de l'écran, on le réinitialise en haut
            if (confetti.shape.getPosition().y > 600) {
                confetti.shape.setPosition(sf::Vector2f(std::rand() % 800, 0));
                confetti.velocity.y = 1 + std::rand() % 3;
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (auto& confetti : confettis) {
            window.draw(confetti.shape);
        }
    }

private:
    std::vector<Confetti> confettis; // Liste des confettis
};

int main() {
    // Crée la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Confettis!");

    ConfettiEmitter emitter;

    // Boucle principale
    while (window.isOpen()) {
        // Gère les événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Met à jour les confettis
        emitter.update();

        // Efface l'écran
        window.clear(sf::Color::Black);

        // Dessine les confettis
        emitter.draw(window);

        // Affiche tout le contenu à l'écran
        window.display();
    }

    return 0;
}
