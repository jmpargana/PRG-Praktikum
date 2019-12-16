# MakeFile For this project
# run "make" in current library to compile

CC := g++ -std=c++17 # This is the main compiler

SRCDIR := src
BUILDDIR := build
TARGET := bin/fcnn

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := -L/usr/include/boost -L/usr/include/boost/filesystem -L/usr/include/boost/system -lboost_filesystem -lboost_system # for arch linux system
INC := -I include


$(TARGET): $(OBJECTS)
	@echo "Creating fully connected neural network binary..."
	$(CC) $^ -o $(TARGET) $(LIB)


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
