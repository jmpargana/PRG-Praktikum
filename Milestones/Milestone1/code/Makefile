# MakeFile For this project
# run "make" in current library to compile

CC := g++ -std=c++17 # This is the main compiler

SRCDIR := src
BUILDDIR := build

GAMEOFLIFE := bin/GameOfLife
# VISUALENCRYPTION := bin/VisualEncryption

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
INC := -I include


# main rule to generate both programs
all: $(GAMEOFLIFE) # $(VISUALENCRYPTION)


$(GAMEOFLIFE): $(OBJECTS)
	@echo "Creating GameOfLife binary..."
	$(CC) $^ -o $(GAMEOFLIFE)


# $(VISUALENCRYPTION): $(OBJECTS)
#	@echo "Creating VisualEncryption binary..."
# 	$(CC) $^ -o $(VISUALENCRYPTION)


$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Creating object file..."
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "Cleaning build directory and binaries..."
	$(RM) -r $(BUILDDIR) $(TARGET)

tester: test/test.cpp
	@echo "Creating tests..."
	$(CC) $(CFLAGS) $(INC) test/test.cpp build/matrix.o build/cellular_automaton.o -o bin/tester
