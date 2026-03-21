function euler30()
    sum(n -> n == sum(s -> parse(Int, s)^5, string(n)) ? n : 0, 10:10^6)
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 30: $(euler30())")
end