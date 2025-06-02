# Define some dictionaries to convert numbers to words
const number_names = Dict{Int,String}(
     0 => "zero",      1 => "one",         2 => "two",
     3 => "three",     4 => "four",        5 => "five",
     6 => "six",       7 => "seven",       8 => "eight",
     9 => "nine",     10 => "ten",        11 => "eleven",
    12 => "twelve",   13 => "thirteen",   14 => "fourteen",
    15 => "fifteen",  16 => "sixteen",    17 => "seventeen",
    18 => "eighteen", 19 => "nineteen",   20 => "twenty", 
    30 => "thirty",   40 => "forty",      50 => "fifty",  
    60 => "sixty",    70 => "seventy",    80 => "eighty", 
    90 => "ninety",  100  => "hundred", 1000 => "thousand"
)


# Make a function that loops through and counts up the 
# characters used in each number (excluding spaces)
function euler17(maxn::Integer=1000)
    characters = 0
    for i ∈ 1:maxn
        characters += length(replace(get_string_name(i), " " => ""))
    end
    characters
end


# Define a function for converting an integer to its name 
# as a string (only works for numbers < 9999)
function get_string_name(n::Integer)
    if n > 9999
        error("Cannot handle integers > 9999.")
    end
    # copy n 
    m = n
    # store a string to hold the output
    string_name = ""
    # first handle the thousands
    if m ≥ 1000
        thousands_digit = (m - m % 1000) ÷ 1000
        m -= thousands_digit*1000
        string_name *= number_names[thousands_digit] * " " 
        string_name *= number_names[1000] * " "
    end
    # then handle the hundreds
    if m ≥ 100
        hundreds_digit = (m - m % 100) ÷ 100
        m -= hundreds_digit*100
        string_name *= number_names[hundreds_digit] * " "
        string_name *= number_names[100] * " "
    end
    if (m > 0) && (n ≥ 100)
        string_name *= "and "
    end
    # then handle the tens IF it's >= 20
    if m ≥ 20
        tens_digit = (m - m % 10) ÷ 10
        m -= tens_digit*10
        string_name *= number_names[tens_digit*10] * " "
    end
    # finally, handle the ones/teens
    if m > 0
        string_name *= number_names[m]
    end
    
    string_name
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 17: $(euler17())")
end