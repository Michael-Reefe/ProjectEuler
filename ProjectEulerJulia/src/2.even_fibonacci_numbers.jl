function euler2()
    # The two starting fibonacci numbers (start at 1 and 1 instead of 1 and 2 so
    # that we explicitly check whether 2 is part of the final sum; hint: it is)
    fib1 = fib2 = 1
    # Loop through and compute the following fibonacci numbers
    fib3 = 0
    fibsum = 0
    while fib3 < 4_000_000
        fib3 = fib1 + fib2
        if mod(fib3, 2) == 0 
            fibsum += fib3
        end
        fib1 = fib2 
        fib2 = fib3
    end
    fibsum
end

# This only runs if this file is called as the main script.
# Equivalent to Python's if __name__ == '__main__' 
if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 2: $(euler2())")
end