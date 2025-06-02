# This is a pretty simple one-liner!
# Just check if each i is divisible by 3 and 5 before
# adding it to the sum.
function euler1(limit::Integer=1000)
    sum(i -> i % 3 == 0 || i % 5 == 0 ? i : 0, 0:limit-1)
end

# This only runs if this file is called as the main script.
# Equivalent to Python's if __name__ == '__main__' 
if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 1: $(euler1())")
end