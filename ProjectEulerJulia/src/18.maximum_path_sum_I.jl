function euler18()

    # Read in the triangle data 
    triangle = Vector{Int}[]
    open(joinpath(@__DIR__, "..", "data", "18.triangle.dat"), "r") do f
        for (i, line) in (enumerate ∘ eachline)(f)
            push!(triangle, zeros(Int, i))
            map!(x -> parse(Int, x), triangle[i], split(line, " "))
        end
    end
    # call the utils function
    triangle_maxpathsum!(triangle)

end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 18: $(euler18())")
end