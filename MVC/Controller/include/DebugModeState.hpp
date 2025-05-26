/**
 * @file DebugModeState.hpp
 * @brief État du jeu permettant de déplacer librement les pièces pour tester le jeu
 */

#ifndef DEBUGMODESTATE_HPP
#define DEBUGMODESTATE_HPP

#include "BoardController.hpp"
#include "State.hpp"

class DebugModeState : public State {
public:
    /**
     * @brief Gère la sélection des pièces de toutes les couleurs
     */
    void handleMousePressed(BoardController& controller, const sf::Event& event) override {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        
        controller.handleBackButtonClick(mousePos);

        // Permet de sélectionner des pièces de toutes les couleurs
        if (controller.TrouverPieceSelectioner(*controller.getListePieces()[0], 0, mousePos)) {
            controller.setDragging(true);
        }
        if (controller.TrouverPieceSelectioner(*controller.getListePieces()[1], 1, mousePos)) {
            controller.setDragging(true);
        }
        if (controller.TrouverPieceSelectioner(*controller.getListePieces()[2], 2, mousePos)) {
            controller.setDragging(true);
        }
    }

    /**
     * @brief Gère le déplacement de la pièce sélectionnée
     */
    void handleMouseMoved(BoardController& controller, const sf::Event& event) override {
        if (!controller.isDragging()) return;
        sf::Vector2f mousePos = controller.getWindow().mapPixelToCoords(sf::Mouse::getPosition(controller.getWindow()));
        (*controller.getListePieces()[controller.getCouleurIndex()])[controller.getSelectedPieceIndex()].getSprite().setPosition(mousePos - controller.getOffsetImage());
    }

    /**
     * @brief Gère le placement de la pièce et la vérification des règles
     */
    void handleMouseReleased(BoardController& controller, const sf::Event& event) override {
        if (!controller.isDragging()) return;

        sf::Vector2f mousePos = controller.getWindow().mapPixelToCoords(sf::Mouse::getPosition(controller.getWindow()));
        bool piecePut = false;

        for (int i = 1; i <= 6; i++) {
            if (controller.PlacerPieceDansMatrice(controller.getMakeBoard().getMatrice(i), i, mousePos)) {
                piecePut = true;
                // Gestion du roque
                if (controller.getJeu().getBoard().isCastling()) {
                    controller.caslingChanges(
                        (*controller.getListePieces()[controller.getCouleurIndex()])[controller.getSelectedPieceIndex()].getTilePositions()[1],
                        *controller.getListePieces()[controller.getCouleurIndex()]
                    );
                    controller.getJeu().getBoard().setCastling(false);
                }
                
                // Gestion de la prise en passant
                if (controller.getJeu().getBoard().isEnPassantMove()) {
                    controller.enPassantChanges();
                }
                
                controller.PlaySound();
                
                // Mise à jour des messages d'échec
                std::string echec =" ";
                if(!controller.getJeu().getBoard().getSidesInCheck().empty()){
                    echec+="Rois en echec : ";
                    for (const auto& side : controller.getJeu().getBoard().getSidesInCheck()){
                        echec += side;
                        echec += " ";
                    }
                }
                controller.getMakeBoard().setTextEchec(echec);

                // Vérification de la fin de partie
                if(controller.getJeu().getBoard().isEndOfGame()){
                    controller.getMakeBoard().setTextGame("Partie Terminee");
                    if(controller.getJeu().getBoard().isStalemate()){
                        controller.getMakeBoard().setTextEchec("Stalemate");
                    }
                    else{
                        controller.getMakeBoard().setTextEchec("Gagnant : "+controller.getJeu().getBoard().getWinner());
                    }
                    controller.setState(std::make_unique<VictoryState>());
                }
                break;
            }
        }
        
        // Remise en place de la pièce si le déplacement est invalide
        if(!piecePut){
            int matrix = (*controller.getListePieces()[controller.getCouleurIndex()])[controller.getSelectedPieceIndex()].getTilePositions()[1];
            int selectedPieceIndex = controller.getSelectedPieceIndex();
            controller.getMakeBoard().ReplacementPiece(selectedPieceIndex, controller.getCouleurIndex(), matrix, (*controller.getListePieces()[controller.getCouleurIndex()]));
            controller.setSelectedPieceIndex(selectedPieceIndex);
        }

        controller.setDragging(false);
        
        controller.RemettreCouleurDefautCases();
    }

    /**
     * @brief Dessine l'état du mode debug
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
        controller.getDrawBoard().display();
    }

    void update(BoardController& controller, float deltaTime) override {}

    std::string getStateName() const override { return "DebugMode"; }
};

#endif