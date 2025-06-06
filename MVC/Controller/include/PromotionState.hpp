/**
 * @file PromotionState.hpp
 * @brief État du jeu gérant la promotion des pions
 */

#ifndef PROMOTIONSTATE_HPP
#define PROMOTIONSTATE_HPP

#include "BoardController.hpp"
#include "State.hpp"
#include "PlayState.hpp"
#include "DebugModeState.hpp"

class PromotionState : public State {
public:
    /**
     * @brief Gère la sélection de la pièce de promotion et le bouton retour
     */
    void handleMousePressed(BoardController& controller, const sf::Event& event) override {
        sf::Vector2f mousePos = controller.getWindow().mapPixelToCoords(sf::Mouse::getPosition(controller.getWindow()));
        int choix = controller.PromotionChoix(mousePos);
        
        if (choix != -1) {
            // Effectue la promotion du pion
            controller.getJeu().getBoard().PawnPromotion(
                controller.getCoupEnAttentePromotion().first,
                controller.getCoupEnAttentePromotion().second,
                choix,
                controller.getJeu().getPlayerList(),
                controller.getJeu().getBoard().getMatrix()
            );
            
            // Met à jour l'apparence de la pièce
            std::vector<PieceImage>& piecesCamp = *controller.getListePieces()[controller.getCouleurIndex()];
            piecesCamp[controller.getSelectedPieceIndex()].getSprite()
                .setTexture(controller.getDrawBoard().getPromotionTexture(choix, controller.getCouleurIndex()), true);
            
            // Retourne au mode de jeu approprié
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

    /**
     * @brief Dessine l'écran de promotion avec les choix de pièces
     */
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