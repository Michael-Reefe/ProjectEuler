# The main project file
module ProjectEulerJulia

using BenchmarkTools

# include all of the files for each problem
include("utils.jl")
include("1.multiples_of_3_or_5.jl")
include("2.even_fibonacci_numbers.jl")
include("3.largest_prime_factor.jl")
include("4.largest_palindrome_product.jl")
include("5.smallest_multiple.jl")
include("6.sum_square_difference.jl")
include("7.10001st_prime.jl")
include("8.largest_product_in_a_series.jl")
include("9.special_pythagorean_triplet.jl")
include("10.summation_of_primes.jl")

# Export functions
n = 10
export julia_main, runall,
       euler1,   euler2,   euler3,   euler4,   euler5,
       euler6,   euler7,   euler8,   euler9,   euler10

# Define the "main" function to run everything
# (this is set up for usage with PackageCompiler.jl
# to create a relocatable executable)
function julia_main()::Cint
    for i ∈ 1:n
        funcname = Symbol("euler$i")
        func = getfield(ProjectEulerJulia, funcname)
        func()
        println("  -----------------------------------------")
        result = @time func()
        println("  Problem $i: $result")
    end
    println("  -----------------------------------------")
    return 0
end
# Alias
runall() = julia_main()

end