CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = 
OBJ = $(SRC:.cpp=.o)
EXEC = insertion-sort-test

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) InsertionSortTest.cpp $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)