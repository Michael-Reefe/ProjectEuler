#!/bin/bash

# A quick helper script that first makes a sysimage
# (if it doesn't already exist) for the julia package,
# then runs all of the problems

if ! test -f PEJ.so; then
    echo "Creating a sysimage for the Julia programs"
    julia --project=. make_sysimage.jl
fi

julia -JPEJ.so --project=. run.jl
