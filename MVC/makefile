# Nom de l'exécutable
TARGET = YaltaEchec

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++17 -IModel -IView -IController

# Fichiers source
SRC = main.cpp \
      Model/model.cpp \
      View/view.cpp \
      Controller/controller.cpp \
	  Model/Jeu.cpp \
	  Model/Plateau.cpp \
      Model/Joueur.cpp \
      Model/Piece.cpp

# Librairies SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

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
