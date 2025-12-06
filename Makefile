# Makefile for Terrain Generator

# Compiler and Flags
CXX = g++
# -Isrc allows us to find doctest.h located in the src/ directory
CXXFLAGS = -std=c++20 -Wall -Wextra -g -Isrc
LDFLAGS = 

# Directories
OBJ_DIR = obj
BIN_DIR = bin

# --- Source Files ---
# Core sources are non-test .cpp files. Add any new ones here.
CORE_SRCS = $(wildcard src/paleta/paleta.cpp)
CORE_OBJS = $(CORE_SRCS:src/%.cpp=$(OBJ_DIR)/%.o)

# Test sources and their corresponding binary names
TEST_NAMES = paleta imagem sequencia terreno
TEST_BINS = $(addprefix $(BIN_DIR)/, $(addsuffix _test, $(TEST_NAMES)))

# --- Main Executable ---
# Assumes you will create a src/main.cpp for the final program
MAIN_BIN = $(BIN_DIR)/terrain_generator

# Phony targets don't represent files
.PHONY: all default test clean help paleta imagem sequencia terreno
.PHONY: $(addprefix test-, $(TEST_NAMES))

# --- Build Rules ---

# The default target, executed when you run `make`
default: $(MAIN_BIN)

all: default

# Rule to link the main program.
# This will fail until src/main.cpp is created.
$(MAIN_BIN): src/main.cpp src/paleta/paleta.cpp src/terreno/terreno.cpp src/imagem/imagem.cpp
	@mkdir -p $(@D)
	@echo "==> Linking main executable..."
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# --- Component Object Rules ---

# `make paleta` builds the object file for the paleta component.
paleta: $(OBJ_DIR)/paleta/paleta.o
	@echo "==> Built object for 'paleta'."

# These components do not have a corresponding .cpp file, only a test file.
imagem sequencia terreno:
	@echo "No buildable source for '$@'. It only has a test file."

# Generic rule for compiling .cpp files into .o object files
$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	@echo "==> Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Test Rules ---

# `make test` builds and runs all tests
test: $(TEST_BINS)
	@echo "==> Running all tests..."
	@for test_bin in $(TEST_BINS); do \
		echo "--- Running $$test_bin ---"; \
		./$$test_bin; \
	done

# Rules to build and run a specific test, e.g., `make test-paleta`
test-paleta: $(BIN_DIR)/paleta_test
	@echo "--- Running paleta tests ---"
	./$< 

test-imagem: $(BIN_DIR)/imagem_test
	@echo "--- Running imagem tests ---"
	./$< 

test-sequencia: $(BIN_DIR)/sequencia_test
	@echo "--- Running sequencia tests ---"
	./$< 

test-terreno: $(BIN_DIR)/terreno_test
	@echo "--- Running terreno tests ---"
	./$< 

# Rule for building the paleta test (it depends on paleta.o)
$(BIN_DIR)/paleta_test: src/paleta/paleta_testes.cpp $(OBJ_DIR)/paleta/paleta.o
	@mkdir -p $(@D)
	@echo "==> Building test: $@"
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule for building the imagem test
$(BIN_DIR)/imagem_test: src/imagem/imagem_testes.cpp src/imagem/imagem.cpp src/paleta/paleta.cpp
	@mkdir -p $(@D)
	@echo "==> Building test: $@"
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/sequencia_test: src/sequencia/sequencia_testes.cpp
	@mkdir -p $(@D)
	@echo "==> Building test: $@"
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/terreno_test: src/terreno/terreno_testes.cpp src/terreno/terreno.cpp src/imagem/imagem.cpp src/paleta/paleta.cpp
	@mkdir -p $(@D)
	@echo "==> Building test: $@"
	$(CXX) $(CXXFLAGS) $^ -o $@


# --- Housekeeping ---

clean:
	@echo "==> Cleaning up..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Available targets:"
	@echo "  all, default      Builds the main program (requires src/main.cpp)"
	@echo "  paleta            Builds the 'paleta' component object file"
	@echo "  test              Builds and runs all available tests"
	@echo "  test-paleta       Builds and runs only the paleta test"
	@echo "  test-imagem       Builds and runs only the imagem test"
	@echo "  test-sequencia    Builds and runs only the sequencia test"
	@echo "  test-terreno      Builds and runs only the terreno test"
	@echo "  clean             Removes all generated files (in obj/ and bin/)"
	@echo ""
