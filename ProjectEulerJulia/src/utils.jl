
# special note: Julia's % operator is NOT equivalent to Python's.
# Python (and most other languages it seems) define % as a modulus,
# whereas Julia defines it as a remainder.  These are identical if 
# the dividend is positive, but they differ if it is negative.
# The modulus is always positive, whereas the remainder can be 
# negative. The Julia functions mod(x,y) and rem(x,y) can be called 
# more explicitly if one prefers one over the other.


# Here we define a PrimeFactorize struct that will extend Base.iterate 
# such that it will return the prime factors (and exponents on those
# prime factors) as an iterator
struct PrimeFactorize{T<:Integer}
    n::T
end

# Define the PrimeFactorize iterator to have a "SizeUnknown" size 
Base.IteratorSize(::Type{<:PrimeFactorize}) = Base.SizeUnknown()

# This defines an iterator such that if we do, for example:
# "for (primefactors, exponents) in PrimeFactorize(number)"...
# we will get an iterator over the prime factors and exponents for number
function Base.iterate(pfact::PrimeFactorize{T}, 
                      state::Tuple{T,T,T}=(pfact.n,floor(typeof(pfact.n),sqrt(pfact.n)),3)) where {T<:Integer}

    # Edge cases
    if pfact.n < 2
        return nothing
    end

    # Keep track of our running division result and our candidate divisor
    nreduced, primelimit, candidate = state

    # Remove factors of 2 first
    if nreduced % 2 == 0
        pfi = 2
        expi = 0
        while nreduced % 2 == 0
            nreduced ÷= 2
            expi += 1
        end
        primelimit = floor(Int, sqrt(nreduced))
        return (pfi, expi), (nreduced, primelimit, 3)
    end

    # We will find the prime factors by trial division, in other words
    # just checking every number to see if it evenly divides the target.

    # An upper limit of sqrt(N) is put in place since a number can have 
    # no more than 1 prime factor larger than this.
    # primelimit = floor(Int, sqrt(nreduced))

    # If nreduced ever reaches 1, we can stop, as we've found all the factors
    while nreduced > 1
        # If candidate exceeds the prime limit, we know the remaining nreduced
        # must itself be the last prime factor
        if candidate > primelimit + 1
            pfi = nreduced
            nreduced = primelimit = 1
            return (pfi, 1), (nreduced, primelimit, candidate+2)
        end
        # See if candidate evenly divides nreduced
        if nreduced % candidate == 0
            pfi = candidate
            expi = 0
            # loop through, update the running division result, and the exponent count
            while nreduced % candidate == 0
                nreduced ÷= candidate
                expi += 1
            end
            primelimit = floor(Int, sqrt(nreduced))
            return (pfi, expi), (nreduced, primelimit, candidate+2)
        end
        candidate += 2
    end

    # If we make it to this point, we've found all the prime factors, so we can stop iterating
    return nothing
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
    @inbounds for i ∈ eachindex(primes)
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


# The number of divisors of any integer is directly
# related to its prime factorization, which we already
# have a function for.
# (see: https://en.wikipedia.org/wiki/Divisor_function#Formulas_at_prime_powers)
# Specifically, the number of divisors is equal to the 
# product of the exponents of each prime factor, which
# are stored in the second column of primes
function ndivisors(number::Integer)
    prod(x->x[2]+1, PrimeFactorize(number); init=1)
end


# The sum of the divisors of any integer is similarly
# related to its prime factorization.
function sumdivisors(number::Integer)
    prod(x->(x[1]^(x[2]+1)-1)÷(x[1]-1), PrimeFactorize(number); init=1)
end

# Quick boolean function to check if a number is prime 
function isprime(number::Integer)
    PrimeFactorize(number) |> collect |> length |> isone
end

# A function to compute all divisors of a number (including 1 and itself), using 
# its prime factorization. Note that the output will NOT be sorted in any particular
# order
function find_all_divisors(number::Integer)
    primes    = Int[]
    exponents = Int[]
    for (prime, exponent) in PrimeFactorize(number)
        push!(primes, prime)
        push!(exponents, exponent)
    end
    ndivisors = prod(x->x+1, exponents; init=1)
    # initialize an array to hold the divisors of the proper length
    divisors = zeros(Int, ndivisors)
    divisors[1] = 1
    divisors[end] = number
    # edge case
    if length(primes) ≤ 1
        return divisors
    end
    # this is an array of all primes except we store copies of each 
    # prime equaling the number of times number is divisible by it
    # (i.e. if number is divisible by 2^3, we store 2 three times)
    primes_expanded = zeros(Int, sum(exponents))
    j = 1
    for i in eachindex(primes)
        primes_expanded[j:j+exponents[i]-1] .= primes[i]
        j += exponents[i]
    end
    # go through every possible combination of prime factors
    divisors[2:end] .= map(prod, unique(combinations(primes_expanded)))
    divisors
end


# there is a way faster method to check the maximum sum of 
# a path in a triangle rather than just brute force.
# - start at the bottom of the triangle, and
#   look at the row above: for each number, add the 
#   maximum of the two below it that the path connects to.
# - iteratively work backwards until you get to the top 
# - the final element will hold the maximum path sum
function triangle_maxpathsum!(triangle::Vector{T}) where T <: Vector{<:Integer}
    for i in Iterators.reverse(eachindex(triangle))
        # skip the last iteration
        i == 1 && continue
        # add the maximum of the two elements accessible to the previous row 
        for j in eachindex(triangle[i])
            j == length(triangle[i]) && continue
            triangle[i-1][j] += max(triangle[i][j], triangle[i][j+1])
        end
    end
    return triangle[1][1]
end