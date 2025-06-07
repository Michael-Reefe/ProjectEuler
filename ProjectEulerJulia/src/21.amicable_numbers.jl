function euler21(limit::Integer=10^4)

    amicable_sum = 0
    # loop over all numbers < limit
    for i in 1:limit-1
        # by definition, amicable numbers must have sum(proper_divisors(j)) = i
        j = sumdivisors(i)-i
        # if the reverse also holds, then these must be amicable numbers
        if (j > i) && sumdivisors(j)-j == i
            amicable_sum += i + j
        end
    end

    amicable_sum
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 21: $(euler21())")
end