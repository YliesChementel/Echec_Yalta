#ifndef FALLING_PIECE_H
#define FALLING_PIECE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class FallingPiece {
public:
    FallingPiece(const sf::Texture& texture, float startX) {
        sprite.setTexture(texture);
        float startY = -200.f;
        sprite.setPosition(startX, startY); // commence en haut
        speed = 100.f + static_cast<float>(rand() % 100); // Vitesse aléatoire
        float scale = 0.3f + static_cast<float>(rand()) / RAND_MAX * 0.3f;
        sprite.setScale(scale, scale);
        sprite.setRotation(static_cast<float>(rand() % 360));
        rotationSpeed = -50.f + static_cast<float>(rand()) / RAND_MAX * 100.f;
    }

    void update(float deltaTime) {
        sprite.move(0.f, speed * deltaTime);
        if (sprite.getPosition().y > 1200.f) { // reset si en bas
            float resetY = -200.f + static_cast<float>(rand() % 150);
            sprite.setPosition(static_cast<float>(rand() % 1100), -200.f);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;
    float speed;
    float rotationSpeed;
};

#endif
