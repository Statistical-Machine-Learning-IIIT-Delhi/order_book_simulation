# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

# Uncomment below if using fmt library
# LDFLAGS := -lfmt

# Directories
SRC_DIR := src
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Executables: turn src/foo.cpp into bin/foo
BINS := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

# Default target
all: $(BIN_DIR) $(BINS)

# Ensure bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule to build each binary
$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Clean up
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
