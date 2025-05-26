/**
 * @file Joueur.hpp
 * @brief Classe représentant un joueur et sa collection de pièces
 */

#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include "Piece.hpp"

/**
 * @class Joueur
 * @brief Classe gérant la collection de pièces d'un joueur
 * 
 * Cette classe est responsable de :
 * - La gestion de la liste des pièces d'un joueur
 * - L'ajout et la suppression de pièces
 * - Le remplacement de pièces (notamment pour la promotion)
 */
class Joueur {
public:
    /**
     * @brief Constructeur initialisant un joueur vide
     */
    Joueur();

    /**
     * @brief Accède à la liste des pièces du joueur
     * @return Pointeur vers le tableau des pièces
     */
    Piece** getListPiece();

    /**
     * @brief Obtient le nombre de pièces du joueur
     * @return Nombre de pièces
     */
    int getSize();

    /**
     * @brief Modifie le nombre de pièces du joueur
     * @param pieceListSize Nouveau nombre de pièces
     */
    void setSize(int pieceListSize);

    /**
     * @brief Définit la liste des pièces du joueur
     * @param pieceList Nouvelle liste de pièces
     */
    void setListPiece(Piece** pieceList);

    /**
     * @brief Supprime une pièce de la liste
     * @param piece Pointeur vers la pièce à supprimer
     */
    void removePiece(Piece* piece);

    /**
     * @brief Remplace une pièce par une autre
     * @param oldPiece Pièce à remplacer
     * @param newPiece Nouvelle pièce
     */
    void replacePiece(Piece* oldPiece,Piece* newPiece);

    /**
     * @brief Destructeur libérant la mémoire des pièces
     */
    ~Joueur();

private:
    int pieceListSize = 16;    ///< Nombre de pièces du joueur
    Piece** pieceList;         ///< Liste des pièces du joueur
};

#endif
