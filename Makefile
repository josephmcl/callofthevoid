


INC_FOLDER = src/header
SRC_FOLDER = src
OBJ_FOLDER = src/objects

CXX = g++
AR = ar

# Lazy
CXXFLAGS = -g3 -std=c++11 -O0

# Debug
#CXXFLAGS = -g3 -std=c++11 -O0 -Wall 

# Release
#CXXFLAGS = -std=c++11 -O2 -Wall

ARFLAGS = rcs
INC = -I$(INC_FOLDER)

LDFLAGS = -pthread -lm
LDLIBS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image

RM = rm -f

SOURCES = timer.cpp eventhandler.cpp audiohandler.cpp frame.cpp script.cpp title.cpp bar.cpp gamestate.cpp maphandler.cpp setup.cpp utility.cpp battle.cpp graphic.cpp move.cpp terrain.cpp  window.cpp point.cpp text.cpp fighter.cpp main.cpp rectlist.cpp 

OBJECTS = $(patsubst %.cpp, $(OBJ_FOLDER)/%.o, $(SOURCES)) 

LIBRARY = 
EXECUTABLE = cotv

all: $(LIBRARY) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

$(LIBRARY): $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp | $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $< 

$(OBJ_FOLDER): 
	mkdir -p $(OBJ_FOLDER)


