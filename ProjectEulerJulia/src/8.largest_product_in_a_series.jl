function euler8(window_size::Integer=13)

    # Because it will make this problem easier,
    # I'm going to do what's called a "pro gamer move"
    # and store our big number as a string
    bignum = read(joinpath(@__DIR__, "..", "data", "8.bignumber.dat"), String)

    # Now all we have to do is scan through "bignumber" with
    # a window size of 13 characters and find the largest 
    # product of the digits
    maxprod = 0
    for i ∈ 1:length(bignum)-window_size+1
        # read in 13 digits from bignumber and multiply them
        testprod = 1
        for j ∈ i:i+window_size-1
            testprod *= parse(Int, bignum[j])
        end
        # check if this is larger than the largest previously
        # found product
        if testprod > maxprod
            maxprod = testprod
        end
    end

    maxprod
end