function euler1()
    # This can be done with a pretty simple loop and the mod function
    # Note: It could be written in one line using list comprehension,
    #       but writing out the loop is actually faster and more memory
    #       efficient!
    s = 0
    for i ∈ 0:999
        if mod(i, 3) == 0 || mod(i, 5) == 0
            s += i
        end
    end
    s
end

# This only runs if this file is called as the main script.
# Equivalent to Python's if __name__ == '__main__' 
if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 1: $(euler1())")
end