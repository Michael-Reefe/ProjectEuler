function euler26(maxd::Int=1000)

    # We need to find the longest recurrent cycle in a fractions decimal representation
    # for all fractions of the form 1/d for d < 1000.  

    function get_decimal_n_recur(d::Int)
        # (see grimbal's method in the Project Euler forums for Q26)
        rest = 1
        # start calculating remainders for the first d decimal places
        # (this eliminates problems where the first few decimal places may
        # not be part of the repeating pattern)
        for _ in 1:d
            rest = (rest*10) % d
        end
        # at this point, if rest=0, the decimal does not recur at all 
        if iszero(rest)
            return 0
        end
        # loop through and check more remainders until a pattern is found --
        # if there is a pattern in the remainders, it means that the decimal will 
        # endlessly loop with the same period
        r₀ = rest 
        rest = (rest*10) % d
        n_recur = 1
        while rest ≠ r₀ 
            rest = (rest*10) % d
            n_recur += 1
        end
        return n_recur
    end

    argmax(d -> get_decimal_n_recur(d), 2:maxd)
end


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 26: $(euler26())")
end