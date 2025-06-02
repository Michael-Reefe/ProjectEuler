# this is another problem where Julia's built-in ability
# to handle BigInts is a godsend, since we can just directly 
# compute 2^1000 (after casting it to a BigInt type):
function euler16(exponent::Integer=1000)
    sum(s -> parse(Int, s), string(BigInt(2)^exponent))
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 16: $(euler16())")
end

