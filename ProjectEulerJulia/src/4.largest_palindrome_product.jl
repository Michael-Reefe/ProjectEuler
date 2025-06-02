function euler4(ndigits::Integer=3)

    minn = 10^(ndigits-1)
    maxn = 10^(ndigits)-1

    # loop through every possible product of two 3 digit numbers.
    # start from the large end since that's more likely to contain
    # a large palindrome
    gpp = 0
    for n1 ∈ maxn:-1:minn
        # for the limits, we use n1 here so we don't double-check
        # the pairs (n1,n2) and (n2,n1)
        for n2 ∈ maxn:-1:n1
            product = n1*n2 
            # we only need to check if the product is a palindrome
            # if it's larger than the previous palindrom product
            if (product > gpp) && ispalindrome(product)
                gpp = product 
            end
        end
    end

    gpp
end

# A function that checks whether a number is a palindrome
@inline function ispalindrome(number::Integer)
    s = string(number)
    s == reverse(s)
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 4: $(euler4())")
end