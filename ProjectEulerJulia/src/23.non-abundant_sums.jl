function euler23()

    # We need to find the sum of all positive integers which cannot be written as 
    # the sum of two abundant numbers.  We know that all integers > 28123 can, so 
    # we only need to check integers up to 28123.

    # 1. The first task is to find all of the abundant numbers below 28123.
    #    An abundant number is one for which its proper divisors sum up to greater than 
    #    the number itself.
    #    We already have the capability of finding all of a number's divisors, and we 
    #    have a sumdivisors function in utils.jl.  We just need to subtract the number 
    #    itself to make sure we only include the *proper* divisors. 
    n_limit = 28123
    abundant_numbers = filter(i -> sumdivisors(i)-i > i, 1:n_limit)

    # 2. The second task is to generate a list of all possible UNIQUE sums of pairs of 
    #    abundant numbers less than the limit (28123).
    #    We do this by making a boolean vector that tells whether each integer from 1-28123
    #    is a sum of two abundant numbers.
    abundant_sum_mask = falses(n_limit)
    for n1 in eachindex(abundant_numbers)
        for n2 in n1:length(abundant_numbers)
            sumi = abundant_numbers[n1] + abundant_numbers[n2]
            if sumi ≤ n_limit
                abundant_sum_mask[sumi] = true
            end
        end
    end

    # 3. Finally, we sum up all of the integers that are NOT the sum of abundant numbers
    nonabundant_sum = sum((1:n_limit)[.~abundant_sum_mask])

    return nonabundant_sum
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 23: $(euler23())")
end