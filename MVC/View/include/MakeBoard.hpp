/**
 * @file MakeBoard.hpp
 * @brief Définition des classes pour la création et la gestion du plateau de jeu d'échecs Yalta
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <array>

/**
 * @class PieceImage
 * @brief Classe représentant une pièce d'échecs avec son image et sa position
 * 
 * Cette classe gère l'affichage et le positionnement d'une pièce sur le plateau,
 * ainsi que son appartenance à un camp (blanc, rouge ou noir).
 */
class PieceImage {
    public:
        /**
         * @brief Constructeur de la pièce
         * @param sprite Sprite SFML de la pièce
         * @param tilePositions Position de la pièce sur le plateau
         * @param camp Camp de la pièce ("White", "Red" ou "Black")
         */
        PieceImage(const sf::Sprite& sprite, const std::vector<int>& tilePositions, const std::string& camp)
            : sprite(sprite), tilePositions(tilePositions), camp(camp) {}
    
        sf::Sprite& getSprite() { return sprite; }  ///< Version modifiable du sprite
        const sf::Sprite& getSprite() const { return sprite; }  ///< Version constante du sprite

        std::vector<int>& getTilePositions()  { return tilePositions; }  ///< Obtient les positions de la pièce
    
        void setSprite(const sf::Sprite& sprite) { this->sprite = sprite; }  ///< Modifie le sprite
        void setTilePositions(const std::vector<int>& tilePositions) { this->tilePositions = tilePositions; }  ///< Modifie les positions
    
        /**
         * @brief Modifie la position de la pièce
         * @param position Nouvelle position du sprite
         * @param tilePosition Nouvelle position sur le plateau
         */
        void setPosition(const sf::Vector2f& position, const std::vector<int>& tilePosition) {
            sprite.setPosition(position);
            this->tilePositions==tilePosition;
        }
        std::string& getCamp(){ return camp; }  ///< Obtient le camp de la pièce
        void setCamp(std::string camp){ this->camp=camp; }  ///< Modifie le camp de la pièce
    
    private:
        sf::Sprite sprite;                 ///< Sprite SFML de la pièce
        std::vector<int> tilePositions;    ///< Positions de la pièce sur le plateau
        std::string camp;                  ///< Camp de la pièce
};

/**
 * @class MakeBoard
 * @brief Classe gérant la création et la manipulation du plateau de jeu
 * 
 * Cette classe est responsable de :
 * - La création du plateau hexagonal
 * - La gestion des pièces et de leurs positions
 * - Le chargement des textures
 * - La gestion des interactions avec le plateau
 */
class MakeBoard {
    public:
        /**
         * @brief Constructeur du plateau
         * Initialise le plateau, charge les textures et place les pièces
         */
        MakeBoard();
    
        /**
         * @brief Calcule le point milieu entre deux points
         * @param p1 Premier point
         * @param p2 Deuxième point
         * @return Point milieu
         */
        sf::Vector2f milieu(const sf::Vector2f& p1, const sf::Vector2f& p2);

        /**
         * @brief Crée une ligne entre deux points
         * @param start Point de départ
         * @param end Point d'arrivée
         * @param color Couleur de la ligne
         * @return Tableau de deux sommets formant la ligne
         */
        std::array<sf::Vertex, 2> createLine(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color);

        /**
         * @brief Crée les lignes d'une matrice
         * @param center Centre de la matrice
         * @param milieu1 Premier point milieu
         * @param milieu2 Deuxième point milieu
         * @param point1 Premier point
         * @param point2 Deuxième point
         * @param point3 Troisième point
         * @return Vecteur des points formant les lignes
         */
        std::vector<sf::Vector2f> createMatrixLines(const sf::Vector2f& center, const sf::Vector2f& milieu1,const sf::Vector2f& milieu2, const sf::Vector2f& point1,const sf::Vector2f& point2, const sf::Vector2f& point3);

        /**
         * @brief Crée un losange
         * @param p1 Premier point
         * @param p2 Deuxième point
         * @param p3 Troisième point
         * @param p4 Quatrième point
         * @param fill Couleur de remplissage
         * @param outline Couleur du contour
         * @return Losange créé
         */
        sf::ConvexShape createLosange(const sf::Vector2f& p1, const sf::Vector2f& p2,const sf::Vector2f& p3, const sf::Vector2f& p4,sf::Color fill, sf::Color outline);

        /**
         * @brief Crée une matrice de losanges
         * @param center Centre de la matrice
         * @param mat_lines Lignes de la matrice
         * @param point Point de référence
         * @param milieu1 Premier point milieu
         * @param milieu2 Deuxième point milieu
         * @param color1 Première couleur
         * @param color2 Deuxième couleur
         * @return Vecteur des losanges créés
         */
        std::vector<sf::ConvexShape> createMatrixLosange(const sf::Vector2f& center, const std::vector<sf::Vector2f>& mat_lines,const sf::Vector2f& point, const sf::Vector2f& milieu1, const sf::Vector2f& milieu2,sf::Color color1, sf::Color color2);

        /**
         * @brief Crée un texte
         * @param textStr Texte à afficher
         * @param startPosition Position de départ
         * @param characterSize Taille des caractères
         * @param color Couleur du texte
         * @param font Police à utiliser
         * @return Texte créé
         */
        sf::Text createText(const std::string& textStr, const sf::Vector2f& startPosition, unsigned int characterSize, sf::Color color, sf::Font& font);

        /**
         * @brief Charge les textures des pièces
         * @param paths Chemins des fichiers de textures
         * @return Vecteur des textures chargées
         */
        std::vector<sf::Texture> loadTextures(const std::vector<std::string>& paths);

        /**
         * @brief Calcule le centre d'un losange
         * @param shape Losange
         * @return Point central
         */
        sf::Vector2f calculerCentreLosange(const sf::ConvexShape& shape);

        /**
         * @brief Charge une image dans un losange
         * @param shape Losange cible
         * @param scaleX Échelle horizontale
         * @param scaleY Échelle verticale
         * @param texture Texture à charger
         * @return Sprite créé
         */
        sf::Sprite chargerImageDansLosange(const sf::ConvexShape& shape, float scaleX, float scaleY, sf::Texture& texture);

        /**
         * @brief Crée les pièces pour un camp
         * @param matriceA Première matrice
         * @param matriceB Deuxième matrice
         * @param positionMatriceA Position dans la première matrice
         * @param positionMatriceB Position dans la deuxième matrice
         * @param textures Textures des pièces
         * @param camp Camp des pièces
         * @return Vecteur des pièces créées
         */
        std::vector<PieceImage> CreerPiece(const std::vector<sf::ConvexShape> matriceA, const std::vector<sf::ConvexShape> matriceB, int positionMatriceA, int positionMatriceB, std::vector<sf::Texture>& textures,std::string camp);

        /**
         * @brief Vérifie si un point est dans une matrice
         * @param point Point à vérifier
         * @param matrice Matrice à tester
         * @return true si le point est dans la matrice
         */
        bool PieceDansMatrice(const sf::Vector2f& point, const std::vector<sf::ConvexShape> matrice);

        /**
         * @brief Vérifie si un point est dans un losange
         * @param shape Losange à tester
         * @param point Point à vérifier
         * @return true si le point est dans le losange
         */
        bool PieceDansLosange(const sf::ConvexShape& shape, const sf::Vector2f& point);

        /**
         * @brief Place une pièce sur le plateau
         * @param selectedPieceIndex Index de la pièce sélectionnée
         * @param losange Losange cible
         * @param listePieces Liste des pièces
         * @param IndexMat Index de la matrice
         * @param IndexLos Index du losange
         */
        void PlacementPiece(int& selectedPieceIndex, const sf::ConvexShape& losange, std::vector<PieceImage>& listePieces, int IndexMat,int IndexLos);

        /**
         * @brief Replace une pièce à sa position d'origine
         * @param selectedPieceIndex Index de la pièce
         * @param camp Camp de la pièce
         * @param matriceIndex Index de la matrice
         * @param pieces Liste des pièces
         */
        void ReplacementPiece(int& selectedPieceIndex, int camp, int matriceIndex, std::vector<PieceImage>& pieces);

        /**
         * @brief Détermine la sous-matrice à partir des coordonnées
         * @param x Coordonnée X
         * @param y Coordonnée Y
         * @return Index de la sous-matrice
         */
        int determineSubMatrix(int x, int y);

        /**
         * @brief Convertit des coordonnées en index de losange
         * @param x Coordonnée X
         * @param y Coordonnée Y
         * @param matrice Index de la matrice
         * @return Index du losange
         */
        int coordonneEnIndexDeLosange(int x, int y, int matrice);

        /**
         * @brief Convertit un index en coordonnées de plateau
         * @param index Index à convertir
         * @param sousMatrice Sous-matrice
         * @return Paire de coordonnées (x, y)
         */
        std::pair<int, int> indexEnCoordonneDePlateau(int index, int sousMatrice);

        /**
         * @brief Place une pièce pour l'IA
         * @param listePieces Liste des pièces
         * @param IndexMatStart Index de la matrice de départ
         * @param IndexLosStart Index du losange de départ
         * @param IndexMatEnd Index de la matrice d'arrivée
         * @param IndexLosEnd Index du losange d'arrivée
         * @param selectedPieceIndex Index de la pièce sélectionnée
         */
        void PlacementPieceAI(std::vector<PieceImage>& listePieces, int IndexMatStart,int IndexLosStart,int IndexMatEnd,int IndexLosEnd, int& selectedPieceIndex);

        // Accesseurs pour les éléments du plateau
        const sf::ConvexShape& getHexagon() const { return hexagon; }
        const sf::ConvexShape& getHexagon2() const { return hexagon2; }
        const std::vector<std::array<sf::Vertex, 2>>& getLines() const { return lines; }
        const std::vector<sf::Text>& getCoordText() const { return coordText; }
        std::vector<sf::ConvexShape>& getMatrice(int index);
        std::vector<sf::ConvexShape>& getMatrice1() { return matrice1; }
        std::vector<sf::ConvexShape>& getMatrice2() { return matrice2; }
        std::vector<sf::ConvexShape>& getMatrice3() { return matrice3; }
        std::vector<sf::ConvexShape>& getMatrice4() { return matrice4; }
        std::vector<sf::ConvexShape>& getMatrice5() { return matrice5; }
        std::vector<sf::ConvexShape>& getMatrice6() { return matrice6; }

        // Accesseurs pour les pièces
        std::vector<PieceImage>& getWhitePieces() { return WhitePieces; }
        std::vector<PieceImage>& getBlackPieces() { return BlackPieces; }
        std::vector<PieceImage>& getRedPieces() { return RedPieces; }

        // Accesseurs pour les textes
        sf::Text& getTextGame() { return textGame; }
        void setTextGame(std::string text) {
            textGame = createText(text, sf::Vector2f(350, 12), 28, sf::Color::Black, font);
        }
        sf::Text& getTextEchec() { return textEchec; }
        void setTextEchec(std::string text) {
            textEchec = createText(text, sf::Vector2f(350, 50), 28, sf::Color::Black, font);
        }

        // Accesseurs pour le bouton retour
        const sf::RectangleShape& getBackButton() const { return backButton; }
        const sf::Text& getBackButtonText() const { return backButtonText; }
        bool isMouseOverBackButton(const sf::Vector2f& mousePos) const;

    private:
        // Éléments du plateau
        sf::ConvexShape hexagon;           ///< Hexagone extérieur
        sf::ConvexShape hexagon2;          ///< Hexagone intérieur
        std::vector<std::array<sf::Vertex, 2>> lines;  ///< Lignes de séparation
        sf::Font font;                     ///< Police de caractères
        std::vector<sf::Text> coordText;   ///< Textes des coordonnées

        // Matrices de losanges
        std::vector<sf::ConvexShape> matrice1;  ///< Matrice 1
        std::vector<sf::ConvexShape> matrice2;  ///< Matrice 2
        std::vector<sf::ConvexShape> matrice3;  ///< Matrice 3
        std::vector<sf::ConvexShape> matrice4;  ///< Matrice 4
        std::vector<sf::ConvexShape> matrice5;  ///< Matrice 5
        std::vector<sf::ConvexShape> matrice6;  ///< Matrice 6

        // Pièces et textures
        std::vector<PieceImage> WhitePieces;    ///< Pièces blanches
        std::vector<sf::Texture> texturesWhite; ///< Textures des pièces blanches
        std::vector<PieceImage> BlackPieces;    ///< Pièces noires
        std::vector<sf::Texture> texturesBlack; ///< Textures des pièces noires
        std::vector<PieceImage> RedPieces;      ///< Pièces rouges
        std::vector<sf::Texture> texturesRed;   ///< Textures des pièces rouges

        // Éléments d'interface
        sf::Text textGame;                ///< Texte du jeu
        sf::Text textEchec;               ///< Texte d'échec
        sf::RectangleShape backButton;    ///< Bouton retour
        sf::Text backButtonText;          ///< Texte du bouton retour
};

#endif
