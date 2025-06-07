function euler19(year_start::Integer=1901, year_end::Integer=2000)
    # How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
    # Note: could've used DateTimes to figure this out easily, but I felt like that would ruin the point, so I 
    #       tried to do it myself.

    # This is a variable where we will keep track of the day of the week;
    # it will range from 0-6, with 0 = Sunday and 6 = Saturday.
    # We initialize it at 1 since we will start on 1 Jan 1900, which is a Monday.
    day_of_week = 1

    # This is where we will keep track of how many sundays have fallen on the first of the month
    total_sundays = 0

    # Iterate through each month (1 = January, 12 = December)
    for year in 1900:year_end
        # Step 0: Check if this is a leap year
        leapyear = is_leap_year(year)
        for month in 1:12
            # Step 1: check if the first day of the month is a Sunday
            if iszero(day_of_week) && year ≥ year_start
                total_sundays += 1
            end
            # Step 2: add the number of days in this month to our day_of_week variable,
            # mod 7 to keep it within the range 0-6
            day_of_week += count_days(month, leapyear)
            day_of_week %= 7
        end
    end

    total_sundays
end

# Return the number of days in a given month
count_days(month::Integer, leapyear::Bool) = if month in (4, 6, 9, 11)
    30
elseif month != 2
    31
else
    28 + (leapyear ? 1 : 0)
end

# We can make a little function to check whether a year is a leap year
is_leap_year(year::Integer) = iszero(year % 4) && (!iszero(year % 100) || iszero(year % 400))


if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 19: $(euler19())")
end