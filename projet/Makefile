# pour créer l'exécutable
yalta: src/Piece.o src/Plateau.o main.o
	g++ -Iinclude -o yalta src/Piece.o src/Plateau.o main.o

# pour compiler src/Piece.o
src/Piece.o: src/Piece.cpp include/Piece.h
	g++ -Iinclude -c src/Piece.cpp -o src/Piece.o

# pour compiler src/Plateau.o
src/Plateau.o: src/Plateau.cpp include/Plateau.h include/Piece.h
	g++ -Iinclude -c src/Plateau.cpp -o src/Plateau.o

# pour compiler main.o
main.o: main.cpp include/Plateau.h include/Piece.h
	g++ -Iinclude -c main.cpp -o main.o

# pour nettoyer les fichiers générés
clean:
	rm -f src/*.o yalta

.PHONY: clean
