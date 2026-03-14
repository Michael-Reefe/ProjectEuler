function euler27(maxd::Int=1000)

    # we need to find a formula of the form n^2 + an + b that produces 
    # primes for consecutive values of n, where |a| <= 1000 and |b| <= 1000.

    # a few things to notice right off the bat:
    # - since we start with n=0, in which case the polynomial
    #   reduces to just b, b itself MUST be prime
    # - similarly, for n=1, the polynomial is 1 + a + b, which
    #   also MUST be prime, so we have the constraint that
    #   a = (prime) - b - 1

    # start by generating all of the prime numbers <= 2001 (to cover extra buffer space for a < 0 and a > 0) 
    all_primes = prime_sieve(2*maxd+1)
    primes = all_primes[all_primes .<= maxd]

    maxa = maxb = maxn = 0
    for b in primes 
        for a in all_primes[findall(<=(maxd + b + 1), all_primes)] .- b .- 1   # all values for a which satisfy a = (prime) - b - 1 and |a| <= 1000
            n = 0
            while (n^2 + a*n + b) in all_primes
                n += 1
            end
            if n > maxn 
                maxn = n
                maxa = a 
                maxb = b
            end
        end
    end

    return maxa*maxb
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 27: $(euler27())")
end