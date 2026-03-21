function euler29(maxd::Int=100)

    # allocate a buffer for holding a^b values
    distinct = zeros(BigInt, (maxd-1)^2)

    # calculate a^b values
    i = 1
    for a ∈ 2:maxd 
        c = BigInt(a)
        for b ∈ 2:maxd 
            c *= a      # iteratively multiply by a, rather than doing a^b each time (slow)
            distinct[i] = c
            i += 1
        end
    end
    # filter to only the unique items in distinct
    unique!(distinct)

    return length(distinct)
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 29: $(euler29())")
end