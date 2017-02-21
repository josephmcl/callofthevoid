


NC_FOLDER = ./includes
SRC_FOLDER = ./sources
OBJ_FOLDER = ./objects

CXX = g++
AR = ar

# Debug
CXXFLAGS = -g3 -O0 -Wall 

# Release
#CXXFLAGS = -O2 -Wall

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

clean:
$(RM) $(OBJ_FOLDER)/*.o $(LIBRARY) $(EXECUTABLE)


