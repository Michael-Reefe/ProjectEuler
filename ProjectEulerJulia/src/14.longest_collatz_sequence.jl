# keep a dictionary to store the previous results
# so we don't re-calculate anything unnecessarily
const collatz_lengths = Dict{Int,Int}(1 => 1)

function euler14(maxn::Integer=1_000_000)

    # check the length of every collatz sequence
    # under 1 million - but we actually only need
    # to check for numbers above 500,000 since any
    # collatz(2n) = collatz(n) + 1
    minn = maxn÷2 + 1
    maxlen = 1
    maxnum = 1
    for i ∈ minn:maxn-1
        ilen = collatz(i)
        if ilen > maxlen
            maxlen = ilen
            maxnum = i
        end
    end 

    maxnum
end

# calculate the length of the collatz sequence that
# starts at n
function collatz(n::Integer)
    global collatz_lengths

    # check if we've already saved this value
    if haskey(collatz_lengths, n)
        return collatz_lengths[n]
    end

    # if not, define it recursively
    if n % 2 == 0
        collatz_lengths[n] = 1 + collatz(n÷2)
    else
        collatz_lengths[n] = 2 + collatz((3n+1)÷2)
    end
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 14: $(euler14())")
end