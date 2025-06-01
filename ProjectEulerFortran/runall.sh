#!/bin/bash

# a quick helper script to run all of the programs and time them

# Change to the "bin" directory
cd bin || { echo "Directory 'bin' not found."; exit 1; }

# Loop through all .exe files and execute them
# Find all .exe files, sort them in natural numeric order, and execute each
find . -maxdepth 1 -type f -name "*.exe" | sort -V | while read -r exe; do
    echo ""
    echo "Executing: $exe"
    time "./$exe"
done
