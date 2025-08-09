function euler24(digits=0:9, n=1000000)

    # Since we are searching for lexigographical order, we know the 
    # permutations are always ordered in the same way.  So rather than 
    # generating ALL permutations up to n, we can do something 
    # clever and just look for the one that we want.

    # In the case of 10 digits (0-9), the first 10!/10 will have '0' as
    # the first digit, the next 10!/10 will have '1' as the first digit,
    # and so on.  So if we're looking for number 1000000, which is between 
    # 10!/10*2 and 10!/10*3, we know that the first digit must be '2'.
    # We can then repeat this pattern all the way down for each digit.

    ndigits = length(digits)
    nthperm = zeros(Int, ndigits)
    digs = sort(collect(copy(digits)))

    index = n
    for i in eachindex(nthperm)
        nperms = factorial(ndigits-1)     # number of permutations in the remaining digits
        digind = cld(index, nperms)       # the index of the digit needed for this position
        nthperm[i] = digs[digind]         # set the corresponding digit
        deleteat!(digs, digind)           # remove the corresponding digit from consideration
        index -= nperms*(digind-1)        # subtract from the index to keep track of what we've used so far
        ndigits -= 1                      # remaining number of digits
    end

    join(nthperm, "")
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 24: $(euler24())")
end