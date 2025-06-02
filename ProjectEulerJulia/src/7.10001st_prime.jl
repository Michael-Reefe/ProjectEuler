function euler7(search_target::Integer=10001)
    # We need to find the 10,001st prime number.

    # To do so, we can make use of the Sieve of Eratosthenes,
    # which is a pretty efficient way to mark all of the prime
    # numbers below some value n.
    # (note: this function is contained in utils)

    # Unfortunately, we don't know what n should be here, since
    # we don't know how large the 10,001st prime is (that's the
    # whole point of the problem). 

    # So instead what we can do is iteratively call the Sieve
    # of Eratosthenes on chunks of numbers and count up how many
    # primes we find until we reach the 10,001st.

    # "n1" holds the first number in the chunk of numbers to be
    # searched
    n1 = 1
    # note: ÷ performs integer floor division
    chunksize = search_target ÷ 10
    # We first do the initial iteration with the regular 
    # Sieve of Eratosthenes:
    primes = prime_sieve(chunksize)
    # From here, we do an infinite loop until primes has a
    # length of 10,001
    while length(primes) < search_target
        n1 += chunksize
        segmented_sieve_step!(primes, n1, chunksize)
    end

    primes[search_target]
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 7: $(euler7())")
end