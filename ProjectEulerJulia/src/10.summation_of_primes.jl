function euler10(n::Integer=2_000_000)

    # This problem is really easy because we already
    # have a Sieve of Eratosthenes subroutine that we
    # made for problem 7.  We can just call that to
    # get all the primes below 2 million and then sum
    # them up
    (sum ∘ prime_sieve)(n)

end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 10: $(euler10())")
end