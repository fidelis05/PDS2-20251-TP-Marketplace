CXX         := g++
CXX_FLAGS   := -Wall -Wextra -std=c++11 -ggdb

BIN         := bin
SRC         := src
INCLUDE     := include
LIB         := lib

LIBRARIES   :=
EXECUTABLE  := main

TESTS       := tests

TEST_SOURCES := $(wildcard $(TESTS)/test_*.cpp)
TEST_BINS := $(patsubst $(TESTS)/%.cpp, $(BIN)/%, $(TEST_SOURCES))

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/test_%: $(TESTS)/test_%.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -Iexternal $< -o $@ $(LIBRARIES)

$(BIN):
	mkdir -p $(BIN)

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do echo "Executando $$t"; $$t; done

clean:
	-rm -rf $(BIN)/*