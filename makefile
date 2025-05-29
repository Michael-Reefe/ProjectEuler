# A makefile for compiling the code with gfortran

# Compiler and options
F90      = gfortran
F90FLAGS = -O3

SRC_DIR=src
BIN_DIR=bin

# find all .f90 source files
SRC_FILES=$(wildcard $(SRC_DIR)/*.f90)
# convert src/*.f90 -> bin/*.exe
BIN_FILES=$(patsubst $(SRC_DIR)/%.f90, $(BIN_DIR)/%.exe, $(SRC_FILES))

# Default target
all: $(BIN_FILES)

# Compile rule
$(BIN_DIR)/%.exe : $(SRC_DIR)/%.f90 | $(BIN_DIR)
	$(F90) $(F90FLAGS) $< -o $@
	chmod +x $@

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up
clean : 
	rm -f $(BIN_DIR)/*.exe

