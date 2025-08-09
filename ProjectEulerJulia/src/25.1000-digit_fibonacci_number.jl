function euler25(ndigits::Integer=1000)

    # Pretty easy problem, just generate fibonacci numbers and check their length 
    # until we get to 1000

    # Make sure our fibonacci variables are BigInts so we can 
    # safely store these numbers
    f₁ = f₂ = BigInt(1)
    # Loop through and compute the following fibonacci numbers
    f₃ = BigInt(0)
    ndig = 1
    index = 2
    while ndig < 1000
        index += 1                        # Keep track of what index we're on 
        f₃ = f₁ + f₂                      # Generate the next fibonacci number 
        ndig = floor(Int, log10(f₃)) + 1  # Count how many digits the number has
        f₁ = f₂                           # Set the previous fibonacci numbers for 
        f₂ = f₃                           #    the next iteration.
    end

    return index
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 25: $(euler25())")
end