function euler22()

    # Read in the names text file
    names::Vector{String} = readdlm(
        joinpath(@__DIR__, "..", "data", "22.names.dat"), ',', String, '\n'
    )[1,:]

    # Make sure everything is uppercase
    @. names = uppercase(names)

    # Sort alphabetically
    sort!(names)

    # Calculate the name scores and sum them up
    sum(i->calculate_name_score(names[i], i), eachindex(names))
end


calculate_name_score(name::String, position::Integer) = sum(char->char-'A'+1, name) * position


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 22: $(euler22())")
end