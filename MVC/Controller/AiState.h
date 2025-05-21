#ifndef AI_STATE_H
#define AI_STATE_H

#include "BoardController.h"
#include "State.h"

class AiState : public State {
public:
    void handleMousePressed(BoardController& controller, const sf::Event& event) override {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        controller.handleBackButtonClick(mousePos);
    }

    void handleMouseMoved(BoardController& controller, const sf::Event& event) override {}

    void handleMouseReleased(BoardController& controller, const sf::Event& event) override {}

    void update(BoardController& controller, float deltaTime) override {}

    void render(BoardController& controller) override {
        controller.getDrawBoard().clear();
        controller.getDrawBoard().drawHexagons(controller.getMakeBoard().getHexagon(), controller.getMakeBoard().getHexagon2());
        controller.getDrawBoard().drawLines(controller.getMakeBoard().getLines());

        controller.getDrawBoard().drawText(controller.getMakeBoard().getCoordText());
        controller.getDrawBoard().drawTextGame(controller.getMakeBoard().getTextGame());
        controller.getDrawBoard().drawTextGame(controller.getMakeBoard().getTextEchec());

        controller.getDrawBoard().drawBoard({controller.getMakeBoard().getMatrice1(),controller.getMakeBoard().getMatrice2(),controller.getMakeBoard().getMatrice3(),controller.getMakeBoard().getMatrice4(),controller.getMakeBoard().getMatrice5(),controller.getMakeBoard().getMatrice6()});
        controller.getDrawBoard().drawPieces(controller.getMakeBoard().getWhitePieces(), controller.getMakeBoard().getRedPieces(), controller.getMakeBoard().getBlackPieces());
        controller.getDrawBoard().drawBackButton(controller.getMakeBoard().getBackButton(), controller.getMakeBoard().getBackButtonText());
        controller.getDrawBoard().display();
    }

    std::string getStateName() const override { return "Ai"; }
};

#endif