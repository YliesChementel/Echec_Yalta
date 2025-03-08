#ifndef JEU_H
#define JEU_H
#include "Joueur.h"
#include "Plateau.h"

class Jeu {
public:
    Jeu();
    void ChangerTourJoueur();
    void VerifStatutJoueur();

private:
    Joueur* ListeJoueur;
    bool etatDeParti;
};


#endif
