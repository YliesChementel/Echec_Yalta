#ifndef PROMOTIONSTATE_H
#define PROMOTIONSTATE_H

#include "BoardController.h"
#include "State.h"
#include "PlayState.h"
#include "DebugModeState.h"

class PromotionState : public State {
public:
    void handleMousePressed(BoardController& controller, const sf::Event& event) override {
        sf::Vector2f mousePos = controller.getWindow().mapPixelToCoords(sf::Mouse::getPosition(controller.getWindow()));
        int choix = controller.PromotionChoix(mousePos);
        
        if (choix != -1) {
            controller.getJeu().getBoard().PawnPromotion(
                controller.getCoupEnAttentePromotion().first,
                controller.getCoupEnAttentePromotion().second,
                choix,
                controller.getJeu().getPlayerList(),
                controller.getJeu().getBoard().getMatrix()
            );
            
            std::vector<PieceImage>& piecesCamp = *controller.getListePieces()[controller.getCouleurIndex()];
            piecesCamp[controller.getSelectedPieceIndex()].getSprite()
                .setTexture(controller.getDrawBoard().getPromotionTexture(choix, controller.getCouleurIndex()), true);
            
            if(controller.isDebugMode()){
                controller.setState(std::make_unique<DebugModeState>());
            }else{
                controller.setState(std::make_unique<PlayingState>());
            }
            
        }
        else if (controller.getMakeBoard().isMouseOverBackButton(mousePos)) {
            controller.setHome(true);
            return;
        }
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
        controller.getDrawBoard().drawChoice(controller.getCouleurIndex());
        controller.getDrawBoard().display();
    }

    std::string getStateName() const override { return "Promotion"; }
};

#endif