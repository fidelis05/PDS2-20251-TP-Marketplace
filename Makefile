CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++11 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
TESTS   := tests

LIBRARIES	:= -lncurses
EXECUTABLE	:= main
TEST_EXECUTABLE := test_runner
COMPREHENSIVE_TEST := test_comprehensive

all: $(BIN)/$(EXECUTABLE)

run: $(BIN)/$(EXECUTABLE)
	clear
	./$(BIN)/$(EXECUTABLE)

test: clean $(BIN)/$(TEST_EXECUTABLE)
	./$(BIN)/$(TEST_EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(TEST_EXECUTABLE): $(TESTS)/test_all.cpp $(SRC)/Admin.cpp $(SRC)/Carrinho.cpp $(SRC)/Correios.cpp $(SRC)/Interface.cpp $(SRC)/Pedido.cpp $(SRC)/Produto.cpp $(SRC)/Usuario.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/*
