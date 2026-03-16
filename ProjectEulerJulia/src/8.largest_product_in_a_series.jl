function euler8(window_size::Integer=13)

    # Because it will make this problem easier,
    # I'm going to do what's called a "pro gamer move"
    # and store our big number as a string
    bignum = read(joinpath(@__DIR__, "..", "data", "8.bignumber.dat"), String)

    # now this is where I show off how sexy Julia can be:
    maximum(
        i->mapreduce(s->parse(Int, s), *, @view bignum[i:i+window_size-1]),
        1:length(bignum)-window_size+1
    )
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 8: $(euler8())")
end