# The main project file
module ProjectEulerJulia

using BenchmarkTools
using DelimitedFiles
using Combinatorics

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
include("11.largest_product_in_a_grid.jl")
include("12.highly_divisible_triangular_number.jl")
include("13.large_sum.jl")
include("14.longest_collatz_sequence.jl")
include("15.lattice_paths.jl")
include("16.power_digit_sum.jl")
include("17.number_letter_counts.jl")
include("18.maximum_path_sum_I.jl")
include("19.counting_sundays.jl")
include("20.factorial_digit_sum.jl")
include("21.amicable_numbers.jl")
include("22.names_scores.jl")
include("23.non-abundant_sums.jl")
include("24.lexicographic_permutations.jl")
include("25.1000-digit_fibonacci_number.jl")

# Export functions
n = 25
export julia_main, runall,
       euler1,   euler2,   euler3,   euler4,   euler5,
       euler6,   euler7,   euler8,   euler9,   euler10,
       euler11,  euler12,  euler13,  euler14,  euler15,
       euler16,  euler17,  euler18,  euler19,  euler20,
       euler21,  euler22,  euler23,  euler24,  euler25

# Define the "main" function to run everything
# (this is set up for usage with PackageCompiler.jl
# to create a relocatable executable)
function julia_main()::Cint
    for i ∈ 1:n
        println("  -----------------------------------------")
        funcname = Symbol("euler$i")
        func = getfield(ProjectEulerJulia, funcname)
        func()
        result = @time func()
        println("  Problem $i: $result")
    end
    println("  -----------------------------------------")
    return 0
end
# Alias
runall() = julia_main()

end