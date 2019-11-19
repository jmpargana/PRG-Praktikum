# MakeFile For this project
# run "make" in current library to compile

CC := g++ #-std=c++17 # This is the main compiler

SRCDIR := src
BUILDDIR := build
TARGET := bin/fcnn

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
INC := -I include


$(TARGET): $(OBJECTS)
	@echo "Creating GameOfLife binary..."
	$(CC) $^ -o $(TARGET)


$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Creating object file..."
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "Cleaning build directory and binaries..."
	$(RM) -r $(BUILDDIR) bin/*

tester: test/test.cpp
	@echo "Creating tests..."
	$(CC) $(CFLAGS) $(INC) test/test.cpp
