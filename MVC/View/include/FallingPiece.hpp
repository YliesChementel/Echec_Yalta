#ifndef FALLING_PIECE_HPP
#define FALLING_PIECE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class FallingPiece {
public:
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

    void setRandomScale() {
        float scale = 0.2f + static_cast<float>(rand()) / RAND_MAX * 0.4f;
        sprite.setScale(scale, scale);
    }

    float getScale() const {
        return sprite.getScale().x;
    }

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

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;
    float speed;
    float rotationSpeed;
    float delay;
    float elapsedTime;
};

#endif
