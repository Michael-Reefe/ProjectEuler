
function euler28(size::Int=1001)

    @assert isodd(size) "size must be odd!"

    # i and j index the x and y position in the grid
    # for 1001, i₀ and j₀ will be 501
    # so that 1:500 will be before and 502:1001 will be after 
    i = j = (size-1) ÷ 2 + 1    

    # k will keep track of the value that should be placed in the grid
    k = 1

    # c, ci, and cj will be counters that keeps track of how we need to change 
    # i and j as we spiral around the loop 
    c = 1
    ci = cj = c

    # keep track of the sum along the diagonals
    diagsum = 0

    # iterate until we reach the end of the array 
    while (i ≥ 1) && (j ≤ size)
        # figure out how the indices need to change based on c 
        if iszero(ci) && iszero(cj)
            # increment c and flip the sign
            c += sign(c)
            c *= -1 
            # set ci and cj to c
            ci = cj = c 
            continue
        end
        # check if this is along the diagonals, and if so add it
        if (i == j) || (i + j == size + 1)
            diagsum += k
        end
        # Prepare the next values of i and j
        if !iszero(cj)
            # increment j based on the sign of cj
            j += sign(cj)
            # increment cj closer to 0 by 1
            cj -= sign(cj)
            # increment k 
            k += 1
        elseif !iszero(ci)
            # increment i based on the sign of ci
            i += sign(ci)
            # increment ci closer to 0 by 1
            ci -= sign(ci)
            # increment k 
            k += 1
        end
    end

    # get the sum of the diagonals
    return diagsum
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 28: $(euler28())")
end