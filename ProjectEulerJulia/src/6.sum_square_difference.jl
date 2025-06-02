function euler6(nmax::Integer=100)
    # this one is pretty straightforward, just
    # compute the sum of the squares and the square
    # of the sum
    numbers = 1:nmax
    sum(numbers)^2 - sum(numbers.^2)
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 6: $(euler6())")
end