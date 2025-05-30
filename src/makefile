# A makefile for compiling the code with gfortran

# Compiler and options
F90      = gfortran
F90FLAGS = -O3 -cpp -fPIC

SRC_DIR=./
BIN_DIR=../bin
OBJ_DIR=../obj

# find all .f90 source files (except utils.f90)
SRC_FILES=$(filter-out $(SRC_DIR)/utils.f90, $(wildcard $(SRC_DIR)/*.f90))
# convert src/*.f90 -> bin/*.exe
BIN_FILES=$(patsubst $(SRC_DIR)/%.f90, $(BIN_DIR)/%.exe, $(SRC_FILES))

# Default target
all: $(BIN_FILES)

# Compile rules
$(OBJ_DIR)/utils.o : $(SRC_DIR)/utils.f90 | $(OBJ_DIR)
	$(F90) $(F90FLAGS) -c $^ -o $@

$(BIN_DIR)/%.exe : $(SRC_DIR)/%.f90 $(OBJ_DIR)/utils.o | $(BIN_DIR)
	$(F90) $(F90FLAGS) $^ -o $@
	chmod +x $@

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
# Same for object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean: 
	rm -f $(BIN_DIR)/*.exe $(OBJ_DIR)/*.o *.mod

