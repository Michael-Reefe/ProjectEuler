# A makefile for compiling the code with gcc

# Compiler and options (use C17 standard)
CC      = gcc
CCFLAGS = -O3 -std=c17 -Wall -Werror
CCDEBUG = 
LIBS    = -lm

SRC_DIR=./
BIN_DIR=../bin

# find all .c source files (except utility files)
SRC_FILES=$(filter-out $(SRC_DIR)/lists.c $(SRC_DIR)/bigint.c $(SRC_DIR)/utils.c, $(wildcard $(SRC_DIR)/*.c))
# convert src/*.c -> bin/*.exe
BIN_FILES=$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.exe, $(SRC_FILES))

# Default target
all: $(BIN_FILES)

# Debug compile
debug: CCDEBUG = -g -fsanitize=address
debug: all

# Compile rules
$(BIN_DIR)/%.exe : $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CCFLAGS) $(CCDEBUG) $^ utils.c lists.c bigint.c -o $@ $(LIBS)
	chmod +x $@

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up
clean: 
	rm -f $(BIN_DIR)/*.exe $(OBJ_DIR)/*.o $(BIN_DIR)/*.asm *.mod

