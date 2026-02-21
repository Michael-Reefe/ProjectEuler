# A makefile for compiling the code with gcc

# Compiler and options
CC      = gcc
CCFLAGS = -O3 

SRC_DIR=./
BIN_DIR=../bin

# find all .c source files (except utils.c)
SRC_FILES=$(filter-out $(SRC_DIR)/utils.c, $(wildcard $(SRC_DIR)/*.c))
# convert src/*.f90 -> bin/*.exe
BIN_FILES=$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.exe, $(SRC_FILES))

# Default target
all: $(BIN_FILES)

# Compile rules
$(BIN_DIR)/%.exe : $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CCFLAGS) $^ -o $@
	chmod +x $@

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up
clean: 
	rm -f $(BIN_DIR)/*.exe $(OBJ_DIR)/*.o *.mod

