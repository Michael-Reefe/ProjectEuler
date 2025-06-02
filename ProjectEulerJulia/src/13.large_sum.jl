function euler13()

    # read in the numbers from the data file
    # julia can handle BigInts...yay!
    bignums::Vector{BigInt} = readdlm(
        joinpath(@__DIR__, "..", "data", "13.numbers.dat"), ' ', BigInt, '\n')[:,1]

    # sum them up and return the first 10 digits
    string(sum(bignums))[1:10]
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 13: $(euler13())")
end