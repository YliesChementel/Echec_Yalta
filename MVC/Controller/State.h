#ifndef STATE_H
#define STATE_H

#include "BoardController.h"

class BoardController;

class State {
public:
    virtual ~State() = default;
    virtual void handleMousePressed(BoardController& controller, const sf::Event& event) = 0;
    virtual void handleMouseMoved(BoardController& controller, const sf::Event& event) = 0;
    virtual void handleMouseReleased(BoardController& controller, const sf::Event& event) = 0;
    virtual void update(BoardController& controller, float deltaTime) = 0;
    virtual void render(BoardController& controller) = 0;
    virtual std::string getStateName() const = 0;
};

#endif