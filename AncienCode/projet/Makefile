# pour créer l'exécutable
yalta: src/Piece.o src/Plateau.o src/Jeu.o src/Joueur.o main.o
	g++ -Iinclude -o yalta src/Piece.o src/Plateau.o src/Jeu.o src/Joueur.o main.o

# pour compiler src/Piece.o
src/Piece.o: src/Piece.cpp include/Piece.h
	g++ -Iinclude -c src/Piece.cpp -o src/Piece.o

# pour compiler src/Plateau.o
src/Plateau.o: src/Plateau.cpp include/Plateau.h include/Piece.h
	g++ -Iinclude -c src/Plateau.cpp -o src/Plateau.o

# pour compiler src/Joueur.o
src/Joueur.o: src/Joueur.cpp include/Joueur.h
	g++ -Iinclude -c src/Joueur.cpp -o src/Joueur.o

# pour compiler src/Jeu.o
src/Jeu.o: src/Jeu.cpp include/Jeu.h include/Plateau.h include/Piece.h 
	g++ -Iinclude -c src/Jeu.cpp -o src/Jeu.o

# pour compiler main.o
main.o: main.cpp include/Jeu.h include/Piece.h
	g++ -Iinclude -c main.cpp -o main.o

# pour nettoyer les fichiers générés
clean:
	rm -f src/*.o yalta

.PHONY: clean
