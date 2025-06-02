function euler3(number::Integer=600851475143)

    # A function for computing the prime factorization of a
    # number has been created in the utils module, since it
    # will be useful for future problems.  We can just use
    # that function here and take the maximum value in the
    # output array.
    primes, _ = primefactorize(number)

    maximum(primes)
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 3: $(euler3())")
end