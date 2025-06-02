function euler5(nmax::Integer=20)
    # Just use Julia's built in LCM function (lol)
    lcm(1:nmax...)
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 5: $(euler5())")
end