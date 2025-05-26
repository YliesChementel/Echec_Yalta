/**
 * @file FallingPiece.hpp
 * @brief Définition de la classe FallingPiece pour l'animation des pièces tombantes
 */

#ifndef FALLING_PIECE_HPP
#define FALLING_PIECE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

/**
 * @class FallingPiece
 * @brief Classe gérant l'animation des pièces qui tombent
 * 
 * Cette classe est responsable de l'animation des pièces qui tombent comme des confettis.
 * Elle gère le mouvement, la rotation et le redimensionnement aléatoire des pièces.
 */
class FallingPiece {
public:
    /**
     * @brief Constructeur de la pièce tombante
     * @param texture Texture de la pièce à afficher
     * @param startX Position X de départ
     * @param speedGiven Vitesse de base de la chute
     * 
     * Initialise une pièce avec une position, une vitesse et des paramètres aléatoires
     * pour l'animation.
     */
    FallingPiece(const sf::Texture& texture, float startX, float speedGiven) {
        sprite.setTexture(texture);
        float startY = -200.f;
        sprite.setPosition(startX, startY);
        speed = speedGiven + static_cast<float>(rand() % 100);
        setRandomScale();
        sprite.setRotation(static_cast<float>(rand() % 360));
        rotationSpeed = -50.f + static_cast<float>(rand()) / RAND_MAX * 100.f;
        delay = static_cast<float>(rand() % 1000) / 100.f;
        elapsedTime = 0.f;
    }

    /**
     * @brief Définit une échelle aléatoire pour la pièce
     * 
     * Applique une échelle aléatoire entre 0.2 et 0.6 à la pièce
     * pour créer un effet visuel varié.
     */
    void setRandomScale() {
        float scale = 0.2f + static_cast<float>(rand()) / RAND_MAX * 0.4f;
        sprite.setScale(scale, scale);
    }

    /**
     * @brief Obtient l'échelle actuelle de la pièce
     * @return L'échelle horizontale de la pièce
     */
    float getScale() const {
        return sprite.getScale().x;
    }

    /**
     * @brief Met à jour la position et l'état de la pièce
     * @param deltaTime Temps écoulé depuis la dernière mise à jour
     * 
     * Gère le mouvement de la pièce, sa réinitialisation lorsqu'elle sort de l'écran,
     * et les délais d'animation.
     */
    void update(float deltaTime) {
        elapsedTime += deltaTime;
        if (elapsedTime >= delay) {
            sprite.move(0.f, speed * deltaTime);
            if (sprite.getPosition().y > 1200.f) {
                float resetY = -200.f + static_cast<float>(rand() % 150);
                sprite.setPosition(static_cast<float>(rand() % 1100), -200.f);
                elapsedTime = 0.f;
                delay = static_cast<float>(rand() % 200) / 100.f;
                setRandomScale();
            }
        }
    }

    /**
     * @brief Dessine la pièce dans la fenêtre
     * @param window Fenêtre de rendu SFML
     */
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;        ///< Sprite SFML de la pièce
    float speed;             ///< Vitesse de chute de la pièce
    float rotationSpeed;     ///< Vitesse de rotation de la pièce
    float delay;            ///< Délai avant le début de l'animation
    float elapsedTime;      ///< Temps écoulé depuis le début de l'animation
};

#endif
