#ifndef JEU_H
#define JEU_H
#include "Joueur.h"
#include "Plateau.h"

class Jeu {
public:
    Jeu();
    void ChangerTourJoueur();
    void VerifStatutJoueur();
    void InitListePiece(Joueur& joueur, int camp);
    Plateau& GetPlateau() { return plateau; }

private:
    Joueur* ListeJoueur;
    bool etatDeParti;
    int tourJoueur;
    Plateau plateau;
};


#endif
