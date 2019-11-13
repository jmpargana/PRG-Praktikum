# MakeFile For this project
# run "make" in current library to compile

CC := g++ -std=c++17 # This is the main compiler

SRCDIR := src
BUILDDIR := build

GAMEOFLIFE := bin/GameOfLife
VICRYPT := bin/visualencrypt

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
INC := -I include


# main rule to generate both programs
all: $(GAMEOFLIFE) $(VICRYPT)


$(GAMEOFLIFE): $(BUILDDIR)/game_of_life.o $(BUILDDIR)/matrix.o $(BUILDDIR)/cellular_automaton.o
	@echo "Creating GameOfLife binary..."
	$(CC) $^ -o $(GAMEOFLIFE)


$(VICRYPT): $(BUILDDIR)/vis_crypt.o
	@echo "Creating VisualEncryption binary..."
	$(CC) $^ -o $(VICRYPT)


$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Creating object file..."
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "Cleaning build directory and binaries..."
	$(RM) -r $(BUILDDIR) bin/GameOfLife bin/visualencrypt bin/tester

tester: test/test.cpp
	@echo "Creating tests..."
	$(CC) $(CFLAGS) $(INC) test/test.cpp build/matrix.o build/cellular_automaton.o -o bin/tester
