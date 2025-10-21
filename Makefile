# Makefile for C++ Calculator Project

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
INCLUDES = -I.

# Directories
SRC_DIR = .
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files
SOURCES = main.cpp Calculator.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = calculator

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Create build directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the main executable
$(BUILD_DIR)/$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Install (copy executable to /usr/local/bin)
install: $(BUILD_DIR)/$(TARGET)
	sudo cp $(BUILD_DIR)/$(TARGET) /usr/local/bin/

# Run the program
run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -g3
debug: $(BUILD_DIR)/$(TARGET)

# Release build
release: CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -DNDEBUG
release: clean $(BUILD_DIR)/$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the calculator (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  run      - Build and run the calculator"
	@echo "  debug    - Build with debug information"
	@echo "  release  - Build optimized release version"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  help     - Show this help message"

.PHONY: all clean install run debug release help
