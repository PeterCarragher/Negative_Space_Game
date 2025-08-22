# Makefile for Negative Space Game
# Requires Allegro5 development libraries

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Source directory
SRCDIR = Allegro5\ Test

# Source files
SOURCES = \
	$(SRCDIR)/main.cpp \
	$(SRCDIR)/BlackFloor.cpp \
	$(SRCDIR)/Floor.cpp \
	$(SRCDIR)/GameObject.cpp \
	$(SRCDIR)/Globals.cpp \
	$(SRCDIR)/GreyFloor.cpp \
	$(SRCDIR)/NLTmxMap.cpp \
	$(SRCDIR)/PlayerBlack.cpp \
	$(SRCDIR)/PlayerWhite.cpp \
	$(SRCDIR)/background.cpp \
	$(SRCDIR)/goal.cpp \
	$(SRCDIR)/Ghost.cpp \
	$(SRCDIR)/Saw.cpp

# Object files
OBJS = main.o BlackFloor.o Floor.o GameObject.o Globals.o GreyFloor.o \
       NLTmxMap.o PlayerBlack.o PlayerWhite.o background.o goal.o Ghost.o Saw.o

# Target executable
TARGET = negative_space_game

# Allegro5 libraries
ALLEGRO_LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_audio -lallegro_acodec

# Include directories
INCLUDES = -I"$(SRCDIR)"

# Linker flags
LDFLAGS = $(ALLEGRO_LIBS) -lm

# Default target
all: $(TARGET) copy-assets

# Build target
$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Compile individual source files
main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

BlackFloor.o: $(SRCDIR)/BlackFloor.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

Floor.o: $(SRCDIR)/Floor.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

GameObject.o: $(SRCDIR)/GameObject.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

Globals.o: $(SRCDIR)/Globals.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

GreyFloor.o: $(SRCDIR)/GreyFloor.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

NLTmxMap.o: $(SRCDIR)/NLTmxMap.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

PlayerBlack.o: $(SRCDIR)/PlayerBlack.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

PlayerWhite.o: $(SRCDIR)/PlayerWhite.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

background.o: $(SRCDIR)/background.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

goal.o: $(SRCDIR)/goal.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

Ghost.o: $(SRCDIR)/Ghost.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

Saw.o: $(SRCDIR)/Saw.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

# Copy assets to build directory
copy-assets:
	@if [ ! -d "assets" ]; then \
		echo "Copying assets..."; \
		cp -r "Allegro5 Test/assets" .; \
		cp "Allegro5 Test/calibri.ttf" .; \
	fi

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf assets calibri.ttf

# Install Allegro5 dependencies (Ubuntu/Debian)
install-deps:
	@echo "To install Allegro5 dependencies, run:"
	@echo "sudo apt update"
	@echo "sudo apt install -y liballegro5-dev liballegro-image5-dev liballegro-font5-dev liballegro-ttf5-dev liballegro-primitives5-dev liballegro-audio5-dev liballegro-acodec5-dev"

# Run the game
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

.PHONY: all clean install-deps run debug copy-assets