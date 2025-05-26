/**
 * @file DrawBoard.hpp
 * @brief Définition de la classe DrawBoard pour le rendu graphique du plateau de jeu
 */

#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "Makeboard.hpp"

/**
 * @class DrawBoard
 * @brief Classe gérant le rendu graphique du plateau de jeu d'échecs Yalta
 * 
 * Cette classe est responsable de l'affichage de tous les éléments graphiques du jeu :
 * - Le plateau hexagonal
 * - Les pièces
 * - Les lignes
 * - Les textes et boutons
 * - L'interface de promotion des pions
 */
class DrawBoard {
    public:
        /**
         * @brief Constructeur de la classe DrawBoard
         * @param window Référence à la fenêtre de rendu SFML
         */
        DrawBoard(sf::RenderWindow& window);

        /**
         * @brief Dessine deux hexagones sur la fenêtre
         * @param hex1 Premier hexagone à dessiner
         * @param hex2 Deuxième hexagone à dessiner
         */
        void drawHexagons(const sf::ConvexShape& hex1, const sf::ConvexShape& hex2);

        /**
         * @brief Dessine le plateau de jeu complet
         * @param matrices Vecteur de matrices contenant les hexagones du plateau
         */
        void drawBoard(const std::vector<std::vector<sf::ConvexShape>>& matrices);

        /**
         * @brief Dessine toutes les pièces sur le plateau
         * @param white Vecteur des pièces blanches
         * @param red Vecteur des pièces rouges
         * @param black Vecteur des pièces noires
         */
        void drawPieces(const std::vector<PieceImage>& white, const std::vector<PieceImage>& red, const std::vector<PieceImage>& black);

        /**
         * @brief Dessine les lignes de connexion entre les hexagones
         * @param lines Vecteur de paires de points définissant les lignes
         */
        void drawLines(const std::vector<std::array<sf::Vertex, 2>>& lines);

        /**
         * @brief Dessine un ensemble de textes sur la fenêtre
         * @param texts Vecteur des textes à afficher
         */
        void drawText(const std::vector<sf::Text>& texts);

        /**
         * @brief Dessine un texte centré horizontalement
         * @param text Texte à afficher
         */
        void drawTextGame(sf::Text& text);

        /**
         * @brief Dessine un bouton retour avec son texte
         * @param button Forme du bouton
         * @param text Texte du bouton
         */
        void drawBackButton(const sf::RectangleShape& button, const sf::Text& text);

        /**
         * @brief Assombrit la couleur d'une case
         * @param losange Case à assombrir
         */
        void changeColorTileDark(sf::ConvexShape& losange);

        /**
         * @brief Éclaircit la couleur d'une case
         * @param losange Case à éclaircir
         */
        void changeColorTileBright(sf::ConvexShape& losange);

        /**
         * @brief Charge les textures pour l'interface de promotion
         */
        void loadPromotionTextures();

        /**
         * @brief Dessine l'interface de promotion des pions
         * @param camp Camp du joueur (0: blanc, 1: rouge, 2: noir)
         */
        void drawChoice(int camp);

        /**
         * @brief Efface la fenêtre
         */
        void clear();

        /**
         * @brief Met à jour l'affichage
         */
        void display();

        /**
         * @brief Vecteur des choix de promotion disponibles
         */
        std::vector<std::pair<sf::RectangleShape, int>> promotionChoix;

        /**
         * @brief Obtient la texture de promotion pour un camp donné
         * @param index Index de la pièce (0: reine, 1: fou, 2: cavalier, 3: tour)
         * @param camp Camp du joueur (0: blanc, 1: rouge, 2: noir)
         * @return Référence à la texture demandée
         */
        sf::Texture& getPromotionTexture(int index, int camp) {
            if(camp==0){
                return texturesPromotionWhite[index];
            }
            else if(camp==1){
                return texturesPromotionRed[index];
            }
            else{
                return texturesPromotionBlack[index];
            }
        }

    private:
        sf::RenderWindow& window;                          ///< Référence à la fenêtre de rendu
        std::vector<sf::Texture> texturesPromotionWhite;   ///< Textures de promotion pour les pièces blanches
        std::vector<sf::Texture> texturesPromotionRed;     ///< Textures de promotion pour les pièces rouges
        std::vector<sf::Texture> texturesPromotionBlack;   ///< Textures de promotion pour les pièces noires
};
    
#endif
