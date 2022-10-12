CC = g++
# Extension #
EXT = cpp
# Flags #
CFLAGS = -Wall -g
# Object Files #
OBJECTS = ./bin/file.o ./bin/util.o 
# Executable # 
EXE = test
# Source directory #
SRC_DIR = ./src
# Bin directory #
BIN_DIR = ./bin

all: $(OBJECTS) $(BIN_DIR)/main.o
	$(CC) $(OBJECTS) $(BIN_DIR)/main.o -o $(EXE) $(CFLAGS)

# MAIN
$(BIN_DIR)/main.o: $(SRC_DIR)/main.$(EXT)
	$(CC) -c $(SRC_DIR)/main.$(EXT) -o $(BIN_DIR)/main.o

# SRC
$(BIN_DIR)/file.o: $(SRC_DIR)/file.$(EXT)
	$(CC) -c $(SRC_DIR)/file.$(EXT) -o $(BIN_DIR)/file.o

$(BIN_DIR)/util.o: $(SRC_DIR)/util.$(EXT)
	$(CC) -c $(SRC_DIR)/util.$(EXT) -o $(BIN_DIR)/util.o

# DELETE/CLEAN
.PHONY : clean remove info
clean:
	del -f $(BIN_DIR)*.o

remove:
	rm -f $(OBJECTS)

info:
	@echo "Trabalho Pratico Engenharia de Software -> $@"
	@echo "Aluno Rafael Coelho Monte Alto          -> author"

#clean:
#	del -f ../../bin/*.o
#
#remove:
#	rm -f ../../bin/*.o
# Windows: make clean
# Linux: make remove

# del -f $(OBJECTS)