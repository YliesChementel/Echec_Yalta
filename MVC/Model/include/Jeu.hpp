/**
 * @file Jeu.hpp
 * @brief Classe principale du modèle de jeu, gérant l'état global du jeu et les joueurs
 */

#ifndef JEU_HPP
#define JEU_HPP
#include "Joueur.hpp"
#include "Plateau.hpp"

/**
 * @class Jeu
 * @brief Classe principale du modèle qui gère l'état global du jeu
 * 
 * Cette classe est responsable de :
 * - L'initialisation des joueurs et de leurs pièces
 * - La gestion du plateau de jeu
 * - L'accès aux composants principaux du jeu
 */
class Jeu {
public:
    /**
     * @brief Constructeur initialisant le jeu
     * Crée les joueurs et initialise leurs pièces sur le plateau
     */
    Jeu();

    /**
     * @brief Destructeur libérant la mémoire des joueurs
     */
    ~Jeu() { delete[] playerList; }

    /**
     * @brief Initialise la liste des pièces pour un joueur
     * @param joueur Référence au joueur à initialiser
     * @param side Numéro du joueur (1: Blanc, 2: Rouge, 3: Noir)
     */
    void InitPieceList(Joueur& joueur, int side);

    /**
     * @brief Accède au plateau de jeu
     * @return Référence au plateau de jeu
     */
    Plateau& getBoard() { return board; }

    /**
     * @brief Accède à la liste des joueurs
     * @return Pointeur vers le tableau des joueurs
     */
    Joueur* getPlayerList() { return playerList; }

private:
    Joueur* playerList;    ///< Tableau des joueurs
    Plateau board;         ///< Plateau de jeu
};

#endif
