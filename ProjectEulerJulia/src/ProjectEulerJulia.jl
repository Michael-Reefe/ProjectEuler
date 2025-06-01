# The main project file
module ProjectEulerJulia

using BenchmarkTools

# include all of the files for each problem
include("1.multiples_of_3_or_5.jl")
include("2.even_fibonacci_numbers.jl")

# Export functions
export julia_main, runall
       euler1, euler2

# Define the "main" function to run everything
# (this is set up for usage with PackageCompiler.jl
# to create a relocatable executable)
function julia_main()::Cint
    try
        for i ∈ 1:2
            funcname = Symbol("euler$i")
            func = getfield(ProjectEulerJulia, funcname)
            func()
            result = @time func()
            println("Problem $i: $result")
        end
    catch
        return 1
    end
    return 0
end
# Alias
runall() = julia_main()

end