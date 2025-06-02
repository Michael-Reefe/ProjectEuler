function euler2(limit::Integer=4_000_000)

    # The two starting fibonacci numbers (start at 1 and 1 instead of 1 and 2 so
    # that we explicitly check whether 2 is part of the final sum; hint: it is)
    f₁ = f₂ = 1
    # Loop through and compute the following fibonacci numbers
    f₃ = 0
    fₛ = 0
    while f₃ < limit
        f₃ = f₁ + f₂
        if f₃ % 2 == 0 
            fₛ += f₃
        end
        f₁ = f₂ 
        f₂ = f₃
    end

    fₛ
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 2: $(euler2())")
end