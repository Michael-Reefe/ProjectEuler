function euler12(ndiv_target::Integer=500)

    # loop through and have a running total that gives the 
    # triangular numbers
    i = 1
    ndiv = ndiv_tmp = 1
    tnum = 0
    while ndiv < ndiv_target
        # generate a new triangular number:
        tnum += i
        # check how many factors this triangular number has by
        # checking the divisors of i and i+1 instead of checking
        # for tnum itself (which can get large)
        if i % 2 == 0 
            ndiv_tmp = ndivisors(i+1)
            ndiv = ndivisors(i÷2)*ndiv_tmp
        else
            ndiv = ndiv_tmp*ndivisors((i+1)÷2)
        end
        i += 1
    end

    tnum
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 12: $(euler12())")
end