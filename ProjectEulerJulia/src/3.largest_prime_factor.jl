function euler3(number::Integer=600851475143)

    # An iterable for computing the prime factorization of a
    # number has been created in the utils module, since it
    # will be useful for future problems.  We can just use
    # that here and take the maximum value in the
    # output array.
    maximum(x->x[1], PrimeFactorize(number))

end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 3: $(euler3())")
end