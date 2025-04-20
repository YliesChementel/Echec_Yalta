#include "Plateau.h"
#include <iostream>
#include <vector>

Plateau::Plateau(){
    InitMatrice();
}

void Plateau::InitMatrice(){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            matrice[i][j] = nullptr;
        }
    }
}

void Plateau::PlacerPiece(Piece** ListePiece1, Piece** ListePiece2, Piece** ListePiece3) {
    int index1 = 0, index2 = 0, index3 = 0;

    // Placement des pièces du joueur 1
    for (int j = 0; j < 8; ++j) {
        ListePiece1[index1]->SetXPosition(1);
        ListePiece1[index1]->SetYPosition(j);
        matrice[1][j] = ListePiece1[index1++];
    }
    for (int j = 0; j < 8; ++j) {
        ListePiece1[index1]->SetXPosition(0);
        ListePiece1[index1]->SetYPosition(j);
        matrice[0][j] = ListePiece1[index1++];
    }

    // Placement des pièces du joueur 2
    for (int j = 0; j < 4; ++j) {
        ListePiece2[index2]->SetXPosition(6);
        ListePiece2[index2]->SetYPosition(j);
        matrice[6][j] = ListePiece2[index2++];
    }
    for (int j = 8; j < 12; ++j) {
        ListePiece2[index2]->SetXPosition(6);
        ListePiece2[index2]->SetYPosition(j);
        matrice[6][j] = ListePiece2[index2++];
    }
    for (int j = 0; j < 4; ++j) {
        ListePiece2[index2]->SetXPosition(7);
        ListePiece2[index2]->SetYPosition(j);
        matrice[7][j] = ListePiece2[index2++];
    }
    for (int j = 8; j < 12; ++j) {
        ListePiece2[index2]->SetXPosition(7);
        ListePiece2[index2]->SetYPosition(j);
        matrice[7][j] = ListePiece2[index2++];
    }

    // Placement des pièces du joueur 3
    for (int j = 4; j < 12; ++j) {
        if(j<8){
            ListePiece3[index3]->SetXPosition(10);
            ListePiece3[index3]->SetYPosition(11-j);
            matrice[10][11-j] = ListePiece3[index3++];
        }else{
            ListePiece3[index3]->SetXPosition(10);
            ListePiece3[index3]->SetYPosition(j);
            matrice[10][j] = ListePiece3[index3++];
        }
    }
    for (int j = 4; j < 12; ++j) {
        if(j<8){
            ListePiece3[index3]->SetXPosition(11);
            ListePiece3[index3]->SetYPosition(11-j);
            matrice[11][11-j] = ListePiece3[index3++];
        }else{
            ListePiece3[index3]->SetXPosition(11);
            ListePiece3[index3]->SetYPosition(j);
            matrice[11][j] = ListePiece3[index3++];
        }
    }

    // Les cases restantes sont vides 
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (matrice[i][j] == nullptr) {
                matrice[i][j] = nullptr;
            }
        }
    }
}

//Fonction pour afficher la matrice dans le CLI
void Plateau::AffichageMatrice(Piece* matrice[12][12]){
    std::cout << "   ";
    for (int j = 0; j < 12; ++j) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 12; ++i) {
        if(i<10){
            std::cout << i << "  ";
        }else{
            std::cout << i << " ";
        }
        
        for (int j = 0; j < 12; ++j) {
            if (matrice[i][j] != nullptr) {
                std::cout << matrice[i][j]->GetType() << " ";
            } else {
                if ((i < 4 && j > 7) || (i >7 && j < 4)) {// Case non existante du plateau yalta
                    std::cout << "  ";
                }
                else if((i >3 && i < 8) && (j > 3 && j < 8)){// Case non existante du plateau yalta (milieu)
                    std::cout << "  ";
                }
                else{
                    std::cout << "X ";
                }
                
            }
        }
        std::cout << std::endl;
    }
}

//Fonction pour afficher les coupsPosibles dans le CLI
void Plateau::AfficherCoupsPossibles(std::vector<std::pair<int, int>> coupsPossibles) {
    std::cout << "   ";
    for (int j = 0; j < 12; ++j) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 12; ++i) {
        if (i < 10) {
            std::cout << i << "  ";
        } else {
            std::cout << i << " ";
        }

        for (int j = 0; j < 12; ++j) {
            bool estCoupPossible = false;
            for (const auto& coup : coupsPossibles) {
                if (coup.first == i && coup.second == j) {
                    estCoupPossible = true;
                    break;
                }
            }

            if (matrice[i][j] != nullptr) {
                std::cout << matrice[i][j]->GetType() << " ";
            } else if (estCoupPossible) {
                std::cout << "O ";
            } else {
                if ((i < 4 && j > 7) || (i > 7 && j < 4)) { // Case non existante du plateau yalta
                    std::cout << "  ";
                } else if ((i > 3 && i < 8) && (j > 3 && j < 8)) { // Case non existante du plateau yalta (milieu)
                    std::cout << "  ";
                } else {
                    std::cout << "X ";
                }
            }
        }
        std::cout << std::endl;
    }
}

// Fonction qui retourne les coups possibles à partir de coordonnées données
std::vector<std::pair<int, int>> Plateau::DeplacerPiece(int xOrigine, int yOrigine) {
    Piece* piece = matrice[xOrigine][yOrigine];
    if(piece->GetType()=="r"){
        int camp = piece->GetCamp();
        std::string nomJoueur;
        if(camp==1){nomJoueur="blanc";}
        else if(camp==2){nomJoueur="rouge";}
        else{nomJoueur="noir";}
        return RetirerCoupEnEchecRoi( nomJoueur, piece);
    }else{
        return piece->DeplacementCoup(xOrigine,yOrigine,this->matrice);
    }
}




// Fonction qui déplace une pièce via les coordonnées données et gère la capture d'une pièce, ainsi que la mise en echec et echec et mat
void Plateau::Deplacement(int xOrigine, int yOrigine,int xCoup,int yCoup, Joueur* ListeJoueur, Piece* matrice[12][12]){
    if (matrice[xCoup][yCoup] != nullptr) {
            std::cout << "Capture" << std::endl;
            if(matrice[xCoup][yCoup]->GetCamp()==1){
                ListeJoueur[0].retirerPiece(matrice[xCoup][yCoup]);
            }
            else if(matrice[xCoup][yCoup]->GetCamp()==2){
                ListeJoueur[1].retirerPiece(matrice[xCoup][yCoup]);
            }
            else{
                ListeJoueur[2].retirerPiece(matrice[xCoup][yCoup]);
            }
    }

    matrice[xCoup][yCoup] = matrice[xOrigine][yOrigine];
    matrice[xOrigine][yOrigine] = nullptr;

    matrice[xCoup][yCoup]->SetXPosition(xCoup);
    matrice[xCoup][yCoup]->SetYPosition(yCoup);

    std::cout << "Pièce déplacée de (" << xOrigine << "," << yOrigine << ") vers (" << xCoup << "," << yCoup << ")" << std::endl;
    std::vector<std::string> camps = VerifierEnEchec(ListeJoueur, matrice);
    if(!camps.empty()) {
        campsEchec=camps;
        std::cout << "Rois en échec : ";
        for (const auto& camp : camps){
            std::cout << camp << " ";
        }
        std::cout << std::endl;
        if (std::count(camps.begin(), camps.end(), "blanc") != 0) {
            if (EstEchecEtMat(0, "blanc", ListeJoueur)) {
                if(this->vainqueur.first=="Aucun"){
                    designerVainqueur(matrice[xCoup][yCoup]->GetCamp(),0);
                }
            }
            else{
                std::cout << "Ya encore une chance !" << std::endl;
                designerVainqueur(-1,-1);
            }
        }
        else if(std::count(camps.begin(), camps.end(), "rouge") != 0){
            if (EstEchecEtMat(1, "rouge", ListeJoueur)) {
                if(this->vainqueur.first=="Aucun"){
                    designerVainqueur(matrice[xCoup][yCoup]->GetCamp(),1);
                }
            }
            else{
                std::cout << "Ya encore une chance !" << std::endl;
                designerVainqueur(-1,-1);
            }
        }
        else{
            if (EstEchecEtMat(2, "noir", ListeJoueur)) {
                if(this->vainqueur.first=="Aucun"){
                    designerVainqueur(matrice[xCoup][yCoup]->GetCamp(),2);
                }
            }
            else{
                std::cout << "Ya encore une chance !" << std::endl;
                designerVainqueur(-1,-1);
            }
        }
    }
    else{
        std::cout << "La partie continue" <<std::endl;
        this->campsEchec.clear();
    }
}


// Fonction similaire à Deplacement mais sera utiliser par la copie du plateau pour la détection des echec et mat
void DeplacementPourCopie(int xOrigine, int yOrigine,int xCoup,int yCoup, Joueur* ListeJoueur, Piece* matrice[12][12]){
    if (matrice[xCoup][yCoup] != nullptr) {
            //std::cout << "Capture" << std::endl;
            if(matrice[xCoup][yCoup]->GetCamp()==1){
                ListeJoueur[0].retirerPiece(matrice[xCoup][yCoup]);
            }
            else if(matrice[xCoup][yCoup]->GetCamp()==2){
                ListeJoueur[1].retirerPiece(matrice[xCoup][yCoup]);
            }
            else{
                ListeJoueur[2].retirerPiece(matrice[xCoup][yCoup]);
            }
    }

    matrice[xCoup][yCoup] = matrice[xOrigine][yOrigine];
    matrice[xOrigine][yOrigine] = nullptr;

    matrice[xCoup][yCoup]->SetXPosition(xCoup);
    matrice[xCoup][yCoup]->SetYPosition(yCoup);

    //std::cout << "Pièce déplacée de (" << xOrigine << "," << yOrigine << ") vers (" << xCoup << "," << yCoup << ")" << std::endl;
}

// Fonction pour faire des copies des listes de pièces des joueurs, et prendre leurs tailles
Piece** copierListePiece(Piece* copie[12][12], int camp, int& taille) {
    int count = 0;
    for (int i = 0; i < 12; ++i){
        for (int j = 0; j < 12; ++j){
            if (copie[i][j] && copie[i][j]->GetCamp() == camp){
                count++;
            }
        }
    }

    Piece** liste = new Piece*[count];
    int index = 0;
    for (int i = 0; i < 12; ++i){
        for (int j = 0; j < 12; ++j){
            if (copie[i][j] && copie[i][j]->GetCamp() == camp){
                liste[index] = copie[i][j];
                liste[index]->SetXPosition(i);
                liste[index]->SetYPosition(j);
                index++;
            }
        }
    }

    taille = count;
    return liste;
}

// Fonction pour faire une copie de la matrice via les méthode clone() des pièces
void CopierMatrice(Piece* copie[12][12], Piece* original[12][12]) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (original[i][j]!=nullptr) {
                copie[i][j] = original[i][j]->clone();
            } else {
                copie[i][j] = nullptr;
            }
        }
    }
}

// Fonction pour supprimer la copie de la matrice de pièce
void LibererMatrice(Piece* (*matrice)[12]) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (matrice[i][j] != nullptr) {
                delete matrice[i][j];  // On supprime chaque pièce allouée dynamiquement
                matrice[i][j] = nullptr;
            }
        }
    }
}

// Fonction pour vérifier si les pièces attaquantes mettent les autres joueurs en echec
std::string VerifierEchecParCamp(int indexAttaquant, std::pair<int,int> roi1, std::pair<int,int> roi2, Joueur* ListeJoueur, Piece* matrice[12][12]) {
    std::vector<std::pair<int, int>> coups;
    Piece** piecesQuiAttaquent = ListeJoueur[indexAttaquant].getListePiece();
    bool echecRoi1 = false; bool echecRoi2 = false;

    for (int i = 0; i < ListeJoueur[indexAttaquant].getTaille(); ++i) {
        if (piecesQuiAttaquent[i]->GetType() != "r") {
            coups = piecesQuiAttaquent[i]->DeplacementCoup(piecesQuiAttaquent[i]->GetXPosition(), piecesQuiAttaquent[i]->GetYPosition(), matrice);
            for (const auto& coup : coups) {
                if (coup == roi1){
                    echecRoi1 = true;
                } 
                if (coup == roi2){
                    echecRoi2 = true;
                } 
            }
        }
    }

    if (echecRoi1 && echecRoi2){
        return "deux";
    }
    if (echecRoi1){
        return "roi1";
    } 
    if (echecRoi2){
        return "roi2";
    } 
    return "aucun";
}

// Fonction pour trouver la position du roi d’un joueur
std::pair<int, int> TrouverPositionRoi(Joueur& joueur) {
    Piece** pieces = joueur.getListePiece();
    for (int i = 0; i < joueur.getTaille(); ++i) {
        if (pieces[i]->GetType() == "r") {
            return { pieces[i]->GetXPosition(), pieces[i]->GetYPosition() };
        }
    }
    return { -1, -1 };
}

// Fonction pour vérifier si les rois sont en echec, si oui alors sa couleur est retourner
std::vector<std::string> Plateau::VerifierEnEchec(Joueur* ListeJoueur, Piece* matrice[12][12]) {
    std::pair<int, int> roiBlanc, roiRouge, roiNoir;

    roiBlanc = TrouverPositionRoi(ListeJoueur[0]);
    roiRouge = TrouverPositionRoi(ListeJoueur[1]);
    roiNoir = TrouverPositionRoi(ListeJoueur[2]);

    std::vector<std::string> campsEnEchec;

    std::string parBlancs = VerifierEchecParCamp(0, roiRouge, roiNoir, ListeJoueur, matrice);
    if (parBlancs == "roi1" || parBlancs == "deux"){
        campsEnEchec.push_back("rouge");
    }
    if (parBlancs == "roi2" || parBlancs == "deux"){
        campsEnEchec.push_back("noir");
    }

    std::string parRouges = VerifierEchecParCamp(1, roiBlanc, roiNoir, ListeJoueur, matrice);
    if (parRouges == "roi1" || parRouges == "deux"){
        campsEnEchec.push_back("blanc");
    }
    if (parRouges == "roi2" || parRouges == "deux"){
        if (std::count(campsEnEchec.begin(), campsEnEchec.end(), "noir") == 0){
            campsEnEchec.push_back("noir");
        }
    }

    std::string parNoirs = VerifierEchecParCamp(2, roiBlanc, roiRouge, ListeJoueur, matrice);
    if (parNoirs == "roi1" || parNoirs == "deux"){
        if (std::count(campsEnEchec.begin(), campsEnEchec.end(), "blanc") == 0){
            campsEnEchec.push_back("blanc");
        }
    }
    if (parNoirs == "roi2" || parNoirs == "deux"){
        if (std::count(campsEnEchec.begin(), campsEnEchec.end(), "rouge") == 0){
            campsEnEchec.push_back("rouge");
        }
    }

    return campsEnEchec;
}

bool Plateau::EstEchecEtMat(int indexJoueur, std::string nomJoueur, Joueur* ListeJoueur) {

    Piece** listePieces = ListeJoueur[indexJoueur].getListePiece();
    int taille = ListeJoueur[indexJoueur].getTaille();

    for (int i = 0; i < taille; ++i) {
        Piece* piece = listePieces[i];
        std::vector<std::pair<int, int>> coupsPossibles = piece->DeplacementCoup(piece->GetXPosition(), piece->GetYPosition(), this->matrice);

        for (const auto& coup : coupsPossibles) {
            Piece* copie[12][12];
            CopierMatrice(copie, this->matrice);

            int tailleBlancCopie, tailleRougeCopie ,tailleNoirCopie;
            Piece** listeBlancCopie = copierListePiece(copie, 1, tailleBlancCopie);
            Piece** listeRougeCopie = copierListePiece(copie, 2, tailleRougeCopie);
            Piece** listeNoirCopie  = copierListePiece(copie, 3, tailleNoirCopie);

            Joueur* ListeJoueurCopie = new Joueur[3];
            ListeJoueurCopie[0].setListePiece(listeBlancCopie); ListeJoueurCopie[0].setTaille(tailleBlancCopie);
            ListeJoueurCopie[1].setListePiece(listeRougeCopie); ListeJoueurCopie[1].setTaille(tailleRougeCopie);
            ListeJoueurCopie[2].setListePiece(listeNoirCopie);  ListeJoueurCopie[2].setTaille(tailleNoirCopie);

            DeplacementPourCopie(piece->GetXPosition(), piece->GetYPosition(), coup.first, coup.second, ListeJoueurCopie, copie);

            std::vector<std::string> campsEnEchecVerif = VerifierEnEchec(ListeJoueurCopie, copie);

            if (std::count(campsEnEchecVerif.begin(), campsEnEchecVerif.end(), nomJoueur) == 0) {
                LibererMatrice(copie);
                return false;
            }

            LibererMatrice(copie);
        }
    }

    std::cout << "Les " << nomJoueur << "s sont en ÉCHEC ET MAT !" << std::endl;
    return true;
}


bool Plateau::PionSurExtremite(int xOrigine, int yOrigine,int xCoup, Piece* matrice[12][12]){
    if(matrice[xOrigine][yOrigine]->GetType()=="P"){
        if(xCoup==0 || xCoup==7 || xCoup==11){
            return true;
        }
    }
    return false;
}

void Plateau::PionPromotion(int xOrigine, int yOrigine, int choixPromotion, Joueur* ListeJoueur,Piece* matrice[12][12]){
    Piece* piecePromotion;
    int campPromotion = matrice[xOrigine][yOrigine]->GetCamp();
    if(choixPromotion==0){
        piecePromotion = new Reine(campPromotion);
    }
    else if(choixPromotion==1){
        piecePromotion = new Fou(campPromotion);
    }
    else if(choixPromotion==2){
        piecePromotion = new Cavalier(campPromotion);
    }
    else if(choixPromotion==3){
        piecePromotion = new Tour(campPromotion);
    }

    if(campPromotion==1){
        ListeJoueur[0].remplacerPiece(matrice[xOrigine][yOrigine],piecePromotion);
    }
    else if(campPromotion==2){
        ListeJoueur[1].remplacerPiece(matrice[xOrigine][yOrigine],piecePromotion);
    }
    else{
        ListeJoueur[2].remplacerPiece(matrice[xOrigine][yOrigine],piecePromotion);
    }
    matrice[xOrigine][yOrigine]=piecePromotion;
}


void Plateau::designerVainqueur(int campGagnant,int campPerdant){
    if(campGagnant==0){
        this->vainqueur={"Blanc",campPerdant};
    }
    else if(campGagnant==1){
        this->vainqueur={"Rouge",campPerdant};
    }
    else if(campGagnant==2){
        this->vainqueur={"Noir",campPerdant};
    }
    else{
        this->vainqueur={"Aucun",-1};
    }

}


std::vector<std::pair<int, int>> Plateau::RetirerCoupEnEchecRoi(std::string nomJoueur, Piece* piece) {
    std::vector<std::pair<int, int>> coupsPossibles = piece->DeplacementCoup(piece->GetXPosition(), piece->GetYPosition(), this->matrice);
    std::vector<std::pair<int, int>> coupsValides;

    for (const auto& coup : coupsPossibles) {
        Piece* copie[12][12];
        CopierMatrice(copie, this->matrice);

        int tailleBlancCopie, tailleRougeCopie ,tailleNoirCopie;
        Piece** listeBlancCopie = copierListePiece(copie, 1, tailleBlancCopie);
        Piece** listeRougeCopie = copierListePiece(copie, 2, tailleRougeCopie);
        Piece** listeNoirCopie  = copierListePiece(copie, 3, tailleNoirCopie);

        Joueur* ListeJoueurCopie = new Joueur[3];
        ListeJoueurCopie[0].setListePiece(listeBlancCopie); ListeJoueurCopie[0].setTaille(tailleBlancCopie);
        ListeJoueurCopie[1].setListePiece(listeRougeCopie); ListeJoueurCopie[1].setTaille(tailleRougeCopie);
        ListeJoueurCopie[2].setListePiece(listeNoirCopie);  ListeJoueurCopie[2].setTaille(tailleNoirCopie);

        DeplacementPourCopie(piece->GetXPosition(), piece->GetYPosition(), coup.first, coup.second, ListeJoueurCopie, copie);

        std::vector<std::string> campsEnEchecVerif = VerifierEnEchec(ListeJoueurCopie, copie);

        if (std::count(campsEnEchecVerif.begin(), campsEnEchecVerif.end(), nomJoueur) == 0) {
            coupsValides.push_back(coup);
        }

        LibererMatrice(copie);
    }

    return coupsValides;
}


