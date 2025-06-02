function euler9(sum_target::Integer=1000)

    # we just need to generate some pythagorean triplets
    # and check if their sum equals 1000.
    # set an upper limit on the search range for n and m
    # of 1000.
    a = b = c = 0
    found = false
    for i ∈ 1:1000 
        found && break
        for j ∈ i+1:1000
            a, b, c = pythagorean_triplet(i, j)
            if (a+b+c) == sum_target 
                found = true
                break
            end
        end
    end

    a*b*c
end

# generate a pythagorean triplet from a pair of
# integers (n, m) where m > n, using a variant of
# Euclid's algorithm
@inline function pythagorean_triplet(n::T, m::T) where {T<:Integer}
    a = 2*m*n
    b = m^2 - n^2
    c = m^2 + n^2
    if (n % 2 ≠ 0) && (m % 2 ≠ 0) 
        a /= 2; b /= 2; c /= 2
    end
    a, b, c
end 
