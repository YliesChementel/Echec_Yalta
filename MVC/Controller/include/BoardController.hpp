/**
 * @file BoardController.hpp
 * @brief Contrôleur gérant la logique du plateau de jeu et les interactions avec les pièces
 */

#ifndef BOARD_CONTROLLER_HPP
#define BOARD_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "../View/include/MakeBoard.hpp"
#include "../View/include/DrawBoard.hpp"
#include "../Model/include/Jeu.hpp"
#include "../View/include/FallingPiece.hpp"
#include <thread>
#include <atomic>

class BoardController {
public:
    /**
     * @brief Constructeur initialisant le contrôleur du plateau
     * @param makeBoard Référence au constructeur du plateau
     * @param drawBoard Référence au dessinateur du plateau
     * @param window Référence à la fenêtre SFML
     * @param jeu Référence au modèle de jeu
     * @param ia Tableau indiquant quels joueurs sont contrôlés par l'IA
     * @param debugMode Indique si le mode debug est activé
     * @param isAiDifficult Indique si l'IA est difficile
     */
    BoardController(MakeBoard& makeBoard, DrawBoard& drawBoard, sf::RenderWindow& window, Jeu& jeu, std::array<bool, 3> ia, bool debugMode, bool isAiDifficult);

    /**
     * @brief Lance la boucle principale du contrôleur
     */
    void run();

    /**
     * @brief Change l'état actuel du jeu
     * @param newState Le nouvel état à définir
     */
    void setState(std::unique_ptr<State> newState){
        currentState = std::move(newState);
    }

    // Méthodes de gestion du jeu
    void initListePieces();
    void handleSound();
    void PlaySound();
    bool TrouverPieceSelectioner(std::vector<PieceImage>& liste, int listeIndex, sf::Vector2f mousePos);
    bool PlacerPieceDansMatrice(const std::vector<sf::ConvexShape>& matrix, int indexMatrice, const sf::Vector2f& mousePos);
    void RemettreCouleurDefautCases();
    void TrouverPieceCapture(std::vector<int> positions);
    int PromotionChoix(const sf::Vector2f& mousePos);
    void handleBackButtonClick(const sf::Vector2f& mousePos);
    void handleCoup(std::vector<int>& tilePositions);
    bool handleCoupJouer(std::vector<int>& tilePositionsOrigine, std::vector<int>& tilePositionsDestination);
    void finDeTour();
    void aiMove();
    void caslingChanges(int matrix, std::vector<PieceImage>& listePieces);
    void enPassantChanges();
    void makeConfetto();
    void update(float deltaTime);
    void startAiMove();

    // Getters
    MakeBoard& getMakeBoard() { return makeBoard; }
    DrawBoard& getDrawBoard() { return drawBoard; }
    sf::RenderWindow& getWindow() { return window; }
    Jeu& getJeu() { return jeu; }
    bool isDebugMode() const { return debugMode; }
    std::array<std::vector<PieceImage>*, 3>& getListePieces() { return listePieces; }
    int getCouleurIndex() const { return couleurIndex; }
    int getSelectedPieceIndex() const { return selectedPieceIndex; }
    const std::pair<int, int>& getCoupEnAttentePromotion() const { return coupEnAttentePromotion; }
    bool isHome() const { return home; }
    bool isPromotion() const { return promotion; }
    int getTour() const { return tour; }
    bool isEndOfGame() const { return endOfGame; }
    int getRookRight() const { return rookRight; }
    bool isDragging() const { return Dragging; }
    const std::vector<std::pair<int, int>>& getPossibleMoves() const { return possibleMoves; }
    int getIndexDernierePiecePrise() const { return indexDernierePiecePrise; }
    const std::vector<std::vector<int>>& getTilesToChangeColor() const { return tilesToChangeColor; }
    sf::Vector2f getOffsetImage() const { return offsetImage; }
    std::vector<FallingPiece>& getFallingConfetto() { return fallingConfetto; }
    std::array<bool, 3>& getIa() { return ia; }
    float getLoadingDotsTimer() const { return loadingDotsTimer; }
    int getLoadingDotsCount() const { return loadingDotsCount; }
    const std::string& getBaseText() const { return baseText; }
    const float getLoadingDotsInterval() const { return LOADING_DOTS_INTERVAL; }
    std::string getDots() const {
        return std::string(loadingDotsCount, '.');
    }

    // Setters
    void setDebugMode(bool debugMode) { this->debugMode = debugMode; }
    void setCouleurIndex(int couleurIndex) { this->couleurIndex = couleurIndex; }
    void setSelectedPieceIndex(int selectedPieceIndex) { this->selectedPieceIndex = selectedPieceIndex; }
    void setCoupEnAttentePromotion(const std::pair<int, int>& coupEnAttentePromotion) { this->coupEnAttentePromotion = coupEnAttentePromotion; }
    void setHome(bool home) { this->home = home; }
    void setPromotion(bool promotion) { this->promotion = promotion; }
    void setTour(int tour) { this->tour = tour; }
    void setEndOfGame(bool endOfGame) { this->endOfGame = endOfGame; }
    void setRookRight(int rookRight) { this->rookRight = rookRight; }
    void setDragging(bool isDragging) { this->Dragging = isDragging; }
    void setIndexDernierePiecePrise(int indexDernierePiecePrise) { this->indexDernierePiecePrise = indexDernierePiecePrise; }
    void addTileToChangeColor(const std::vector<int>& tile) { tilesToChangeColor.push_back(tile); }
    void clearTilesToChangeColor() { tilesToChangeColor.clear(); }
    void setOffsetImage(const sf::Vector2f& offsetImage) { this->offsetImage = offsetImage; }
    void setFallingConfetto(const std::vector<FallingPiece>& fallingConfetto) { this->fallingConfetto = fallingConfetto; }
    void setLoadingDotsTimer(float timer) { this->loadingDotsTimer = timer; }
    void setLoadingDotsCount(int count) { this->loadingDotsCount = count; }
    void setBaseText(const std::string& text) { this->baseText = text; }

private:
    // Références aux composants principaux
    MakeBoard& makeBoard;         ///< Constructeur du plateau
    DrawBoard& drawBoard;         ///< Dessinateur du plateau
    sf::RenderWindow& window;     ///< Fenêtre SFML
    Jeu& jeu;                     ///< Modèle de jeu
    std::array<bool, 3> ia;       ///< Configuration des joueurs IA
    bool debugMode;               ///< Mode debug activé/désactivé

    // État du jeu
    std::unique_ptr<State> currentState;  ///< État actuel du jeu
    int tour = 0;                         ///< Tour actuel (0: Blanc, 1: Rouge, 2: Noir)
    bool endOfGame = false;               ///< Indique si la partie est terminée
    int rookRight = 7;                    ///< Index de la tour droite pour le roque
    bool home = false;                    ///< Indique si on retourne au menu
    bool promotion = false;               ///< Indique si une promotion est en cours

    // Gestion des pièces
    std::array<std::vector<PieceImage>*, 3> listePieces;  ///< Liste des pièces par couleur
    int indexDernierePiecePrise;                          ///< Index de la dernière pièce prise
    std::pair<int, int> coupEnAttentePromotion;           ///< Coup en attente de promotion
    std::vector<std::pair<int, int>> possibleMoves;       ///< Coups possibles pour la pièce sélectionnée

    // Gestion du drag & drop
    bool Dragging;                    ///< Indique si une pièce est en cours de déplacement
    int selectedPieceIndex;           ///< Index de la pièce sélectionnée
    int couleurIndex;                 ///< Index de la couleur de la pièce sélectionnée
    sf::Vector2f offsetImage;         ///< Offset pour le drag & drop

    // Effets visuels
    std::vector<sf::Texture> confettoTextures;    ///< Textures des confettis
    std::vector<FallingPiece> fallingConfetto;    ///< Confettis en cours de chute
    std::vector<std::string> confettoPaths = {    ///< Chemins des textures de confettis
        "resources/images/confetti/Confetto_blanc.png",
        "resources/images/confetti/Confetto_bleu.png",
        "resources/images/confetti/Confetto_jaune.png",
        "resources/images/confetti/Confetto_orange.png",
        "resources/images/confetti/Confetto_rose.png",
        "resources/images/confetti/Confetto_rouge.png",
        "resources/images/confetti/Confetto_vert.png",
        "resources/images/confetti/Confetto_violet.png"
    };

    // Sons
    sf::Sound sound;                  ///< Son de déplacement
    sf::SoundBuffer buffer;           ///< Buffer du son

    // Interface
    std::vector<std::vector<int>> tilesToChangeColor;  ///< Cases à changer de couleur

    // Animation de chargement IA
    float loadingDotsTimer = 0.0f;                    ///< Timer pour l'animation des points
    int loadingDotsCount = 0;                         ///< Nombre de points à afficher
    const float LOADING_DOTS_INTERVAL = 0.5f;         ///< Intervalle entre les points
    std::string baseText;                             ///< Texte de base pour l'IA

    // Gestion de l'IA
    std::atomic<bool> stopAiThread = false;           ///< Signal d'arrêt du thread IA
    std::thread aiThread;                             ///< Thread de calcul de l'IA
    std::atomic<bool> aiMoveReady = false;            ///< Indique si le coup de l'IA est prêt
    std::atomic<bool> aiCalculating = false;          ///< Indique si l'IA est en train de calculer
    bool iaEnCours = false;                           ///< Indique si c'est le tour de l'IA
    int depthLevel;                                   ///< Niveau de profondeur pour l'IA
};

#endif
