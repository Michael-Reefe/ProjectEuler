# This is another problem that julia trivializes thanks to BigInts
function euler20(number::Integer=100)
    sum(s -> parse(Int, s), string(factorial(BigInt(number))))
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 20: $(euler20())")
end