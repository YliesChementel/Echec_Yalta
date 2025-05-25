# Nom de l'exécutable
TARGET = YaltaEchec

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++17 -IModel -IView -IController

# Fichiers source
SRC = main.cpp \
      View/src/MakeBoard.cpp \
      View/src/DrawBoard.cpp \
	  View/src/Menu.cpp \
      Controller/src/BoardController.cpp \
	  Controller/src/MainController.cpp \
	  Model/src/Jeu.cpp \
	  Model/src/Plateau.cpp \
      Model/src/Joueur.cpp \
      Model/src/Piece.cpp

# Librairies SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread 

# Règle principale
all: $(TARGET)

# Compilation
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Nettoyage
clean:
	rm -f $(TARGET)

# Optionnel : nettoyage plus large
clean-all:
	rm -f $(TARGET) *.o
