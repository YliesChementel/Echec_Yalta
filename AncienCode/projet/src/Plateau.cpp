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

    // Placer les pièces du joueur 1
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

    // Placer les pièces du joueur 2
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

    // Placer les pièces du joueur 3
    for (int j = 4; j < 12; ++j) {
        ListePiece3[index3]->SetXPosition(10);
        ListePiece3[index3]->SetYPosition(j);
        matrice[10][j] = ListePiece3[index3++];
    }
    for (int j = 4; j < 12; ++j) {
        ListePiece3[index3]->SetXPosition(11);
        ListePiece3[index3]->SetYPosition(j);
        matrice[11][j] = ListePiece3[index3++];
    }

    // Mettre les cases restantes vides 
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (matrice[i][j] == nullptr) {
                matrice[i][j] = nullptr;
            }
        }
    }
}

void Plateau::AffichageMatrice() {
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

std::vector<std::pair<int, int>> Plateau::DeplacerPiece(int xOrigine, int yOrigine) {
    Piece* piece = matrice[xOrigine][yOrigine];
    return piece->DeplacementCoup(xOrigine,yOrigine);
}

void Plateau::DeplacementAutoriser(int xOrigine, int yOrigine,int xCoup,int yCoup, Joueur* ListeJoueur){
    if (matrice[xCoup][yCoup] != nullptr) {
            std::cout << "Capture" << std::endl;
            if(matrice[xCoup][yCoup]->GetCamp()==0){
                ListeJoueur[0].retirerPiece(matrice[xCoup][yCoup]);
            }
            else if(matrice[xCoup][yCoup]->GetCamp()==1){
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
    VerifierEnEchec(ListeJoueur);
}

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

void Plateau::VerifierEnEchec(Joueur* ListeJoueur){
    std::vector<std::pair<int, int>> coupsEchecBlanc;
    std::vector<std::pair<int, int>> coupsEchecRouge;
    std::vector<std::pair<int, int>> coupsEchecNoir;
    std::vector<std::pair<int, int>> coups;
    std::pair<int, int> roiBlanc;
    std::pair<int, int> roiRouge;
    std::pair<int, int> roiNoir;


    Piece** listeBlanc = ListeJoueur[0].getListePiece();
    for(int i=0;i < ListeJoueur[0].getTaille();i++){
        if(listeBlanc[i]->GetType()!="r"){
            coups = listeBlanc[i]->DeplacementCoup(listeBlanc[i]->GetXPosition(),listeBlanc[i]->GetYPosition());
            coupsEchecBlanc.insert(coupsEchecBlanc.end(), coups.begin(), coups.end());
        }
        else{
            roiBlanc={listeBlanc[i]->GetXPosition(), listeBlanc[i]->GetYPosition()};
        }
    }

    Piece** listeRouge = ListeJoueur[1].getListePiece();
    for(int i=0;i < ListeJoueur[1].getTaille();i++){
        if(listeRouge[i]->GetType()!="r"){
            coups = listeRouge[i]->DeplacementCoup(listeRouge[i]->GetXPosition(),listeRouge[i]->GetYPosition());
            coupsEchecRouge.insert(coupsEchecRouge.end(), coups.begin(), coups.end());
        }
        else {
            roiRouge={listeRouge[i]->GetXPosition(), listeRouge[i]->GetYPosition()};
        }
    }

    Piece** listeNoir = ListeJoueur[2].getListePiece();
    for(int i=0;i < ListeJoueur[2].getTaille();i++){
        if(listeNoir[i]->GetType()!="r"){
            coups = listeNoir[i]->DeplacementCoup(listeNoir[i]->GetXPosition(),listeNoir[i]->GetYPosition());
            coupsEchecNoir.insert(coupsEchecNoir.end(), coups.begin(), coups.end());
        }
        else{
            roiNoir={listeNoir[i]->GetXPosition(), listeNoir[i]->GetYPosition()};
        }
    }

    for (const auto& coup : coupsEchecBlanc) {
        if(coup==roiNoir || coup==roiRouge){
            std::cout<< "ECHEC"<< std::endl;
            break;
        }
    }
    for (const auto& coup : coupsEchecRouge) {
        if(coup==roiNoir || coup==roiBlanc){
            std::cout<< "ECHEC"<< std::endl;
            break;
        }
    }
    for (const auto& coup : coupsEchecNoir) {
        if(coup==roiBlanc || coup==roiRouge){
            std::cout<< "ECHEC"<< std::endl;
            break;
        }
    }
}