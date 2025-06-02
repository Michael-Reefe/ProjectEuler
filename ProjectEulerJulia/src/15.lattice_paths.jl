# the lattice paths can be counted by just using
# the binomial coefficient, AKA the "choose" function,
# where "n choose k" = n! / k!(n-k)!

# In this case, n is the total length of any path from
# the top-left to the bottom-right of the grid: 
# n = gridx+gridy

# And since we only have 2 options to move at any grid
# point, once we have chosen all of the right movements,
# all of the down movements are fully constrained (and
# vice versa).  Therefore, since k represents the number
# of choices, we have: k = gridx

# So, the problem boils down to calculating 40 choose 20.
# Luckily, julia has a built-in binomial coefficient function,
# so this is a one-liner!

function euler15(gridx::Integer=20, gridy::Integer=20)
    binomial(gridx+gridy, gridx)
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 15: $(euler15())")
end