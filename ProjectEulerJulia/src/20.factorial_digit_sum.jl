# This is another problem that julia trivializes thanks to BigInts
function euler20(number::Integer=100)
    sum(s -> parse(Int, s), string(factorial(BigInt(number))))
end