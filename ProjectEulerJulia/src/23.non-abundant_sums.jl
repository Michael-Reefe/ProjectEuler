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
    abundant_numbers = zeros(Int, n_limit)
    j = 1
    for i in 1:n_limit
        if sumdivisors(i)-i > i 
            abundant_numbers[j] = i
            j += 1
        end
    end
    abundant_numbers = abundant_numbers[1:j-1]
    n_abun = length(abundant_numbers)

    # 2. The second task is to concatenate a list of all possible UNIQUE sums of pairs of 
    #    abundant numbers less than the limit (28123)
    abundant_sums = zeros(Int, n_abun*(n_abun-1)÷2+n_abun)
    i = 1
    for n1 in eachindex(abundant_numbers)
        for n2 in n1:length(abundant_numbers)
            sumi = abundant_numbers[n1] + abundant_numbers[n2]
            if sumi ≤ n_limit
                abundant_sums[i] = sumi
                i += 1
            end
        end
    end
    unique!(abundant_sums)

    # 3. Finally, to make the final step faster than just doing a loop through each number 
    #    and checking if it's in the list, we can instead just get the sum of ALL numbers 
    #    below the limit (28123), and the SUBTRACT each number in abundant_sums that is less 
    #    than the limit.
    nonabundant_sum = sum(1:n_limit) - sum(abundant_sums)

    return nonabundant_sum
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 23: $(euler23())")
end