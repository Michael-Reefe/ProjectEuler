function euler21(limit::Integer=10^4)
    sum(filter(is_amicable, 1:limit-1))
end

# hash table to store amicable number calculations
const amicable_numbers = Dict{Int, Bool}()

# function to check if a number is amicable, saving 
# also the results for its amicable pair to save future 
# computation time
function is_amicable(n::Integer)
    global amicable_numbers

    if haskey(amicable_numbers, n)
        return amicable_numbers[n]
    end
    m = sumdivisors(n) - n 
    if (m ≠ n) && sumdivisors(m) - m == n
        amicable_numbers[n] = true 
        amicable_numbers[m] = true
    else
        amicable_numbers[n] = false
    end
    # special case 
    if isone(n)
        amicable_numbers[n] = false 
    end
    return amicable_numbers[n]
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 21: $(euler21())")
end