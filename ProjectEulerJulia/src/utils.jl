
# special note: Julia's % operator is NOT equivalent to Python's.
# Python (and most other languages it seems) define % as a modulus,
# whereas Julia defines it as a remainder.  These are identical if 
# the dividend is positive, but they differ if it is negative.
# The modulus is always positive, whereas the remainder can be 
# negative. The Julia functions mod(x,y) and rem(x,y) can be called 
# more explicitly if one prefers one over the other.

# A function that finds the prime factors of a given number
function primefactorize(number::Integer)

    # Prepare outputs
    primefactors = Int[]
    exponents    = Int[]

    # Edge cases
    if number < 2
        return 
    end

    # Set a running division result 
    nreduced = number

    # Remove factors of 2 first
    if nreduced % 2 == 0
        push!(primefactors, 2)
        push!(exponents, 0)
        while nreduced % 2 == 0
            nreduced /= 2
            exponents[end] += 1
        end
    end

    # We will find the prime factors by trial division, in other words
    # just checking every number to see if it evenly divides the target.
    candidate = 3
    # An upper limit of sqrt(N) is put in place since a number can have 
    # no more than 1 prime factor larger than this.
    primelimit = floor(Int, sqrt(nreduced))

    # If nreduced ever reaches 1, we can stop, as we've found all the factors
    while nreduced > 1
        # If candidate exceeds the prime limit, we know the remaining nreduced
        # must itself be the last prime factor
        if candidate > primelimit + 1
            push!(primefactors, nreduced)
            push!(exponents, 1)
            break
        end
        # See if candidate evenly divides nreduced
        if nreduced % candidate == 0
            push!(primefactors, candidate)
            push!(exponents, 0)
            # loop through, update the running division result, and the exponent count
            while nreduced % candidate == 0
                nreduced /= candidate
                exponents[end] += 1
            end
            # update the upper limit
            primelimit = floor(Integer, sqrt(nreduced))
        end
        # Update the candidate, stepping by 2 since we already checked all the even nums
        candidate += 2
    end

    primefactors, exponents
end


# Sieve of Eratosthenes: Generates all prime numbers less than n
function prime_sieve(n::Integer)

    # instantiate a bitmask of size n
    primemask = trues(n)
    # 1 is not prime
    primemask[1] = false 

    # this is a well known algorithm that works by marking all of the
    # multiples of every number less than sqrt(n) as composite, thereby
    # leaving the remaining numbers as the primes
    primelimit = floor(Int, sqrt(n))
    for i ∈ 2:primelimit
        primemask[i] || continue
        for j ∈ i^2:i:n
            primemask[j] = false
        end
    end

    # now we can return an array to hold the prime numbers found
    findall(primemask)
end


# an iteration of the segmented sieve algorithm
# so that we dont have to store potentially huge arrays 
# in memory all at once
function segmented_sieve_step!(primes::Vector{<:T}, n::T, chunksize::T) where {T<:Integer}

    # n is the first integer to check
    # m is the last integer to check
    m = n + chunksize - 1
    # initialize everything as prime at first like the regular sieve
    primemask = trues(chunksize)

    primelimit = floor(Int, sqrt(m))
    for i ∈ eachindex(primes)
        p = primes[i]
        p > primelimit && break
        # j enumerates the multiples of p within the range (n, m)
        for j ∈ n-n%p:p:m-m%p
            j < n && continue
            primemask[j-n+1] = 0
        end
    end

    # append the newly found prime numbers to the "primes" array
    newprimes = (n:m)[primemask]
    append!(primes, newprimes)
end