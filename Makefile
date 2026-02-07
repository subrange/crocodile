# Default: C build
CFLAGS = -Isrc -std=c11 -O2 -Wall -Wextra # -g -DDEBUG

# Uncomment for C++
#CXXFLAGS = -Isrc -std=c++17 -O2 -Wall -Wextra # -g -DDEBUG

CFLAGS += -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs

# Uncomment for C++
#CXXFLAGS += -Wall -Wextra -Wpedantic \
#             -Wformat=2 -Wno-unused-parameter -Wshadow \
#             -Wwrite-strings -Wmissing-include-dirs

SRC = src
BIN = bin
DOCS = docs

SRCS = $(wildcard $(SRC)/*.c)
#SRCS_CPP = $(wildcard $(SRC)/*.cpp)

OBJS = $(SRCS:$(SRC)/%.c=$(BIN)/%.o)
#OBJS_CPP = $(SRCS_CPP:$(SRC)/%.cpp=$(BIN)/%.o)

main: $(OBJS) | mkbin
	$(CC) $(CFLAGS) $^ -o $(BIN)/main

# Uncomment for C++
#main: $(OBJS_CPP) | mkbin
#	$(CXX) $(CXXFLAGS) $^ -o $(BIN)/main

$(BIN)/%.o: $(SRC)/%.c | mkbin
	$(CC) $(CFLAGS) -c $< -o $@

# Uncomment for C++
#$(BIN)/%.o: $(SRC)/%.cpp | mkbin
#	$(CXX) $(CXXFLAGS) -c $< -o $@

mkbin:
	@ mkdir -p $(BIN)

doc:
	doxygen

clean:
	@ rm -rf $(BIN)/* core* *~ $(SRC)/*~ $(DOCS)/* *.dSYM

.PHONY: main mkbin doc clean
