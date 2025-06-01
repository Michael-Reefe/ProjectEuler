program even_fibonacci_numbers

    ! Setup and declare variables
    implicit none
    integer :: fib1, fib2, fib3
    integer :: fib_sum

    print *, '----------------------------------'
    print *, 'Problem 2: Even Fibonacci Numbers '
    print *, 'https://projecteuler.net/problem=2'
    print *, '----------------------------------'

    ! The two starting fibonacci numbers (start at 1 and 1 instead of 1 and 2 so
    ! that we explicitly check whether 2 is part of the final sum; hint: it is)
    fib1 = 1
    fib2 = 1
    ! Loop through and compute the following fibonacci numbers
    fib3 = 0
    fib_sum = 0
    do 
        ! get the next fibonacci number
        fib3 = fib1 + fib2
        ! check if we've exceeded the 4 million limit
        if (fib3 > 4000000) exit
        ! if it's even, add it to the sum
        if (mod(fib3, 2) == 0) fib_sum = fib_sum + fib3
        ! update variables for the next loop iteration
        fib1 = fib2
        fib2 = fib3
    end do

    ! Output the result
    print *, 'Answer:', fib_sum

end program even_fibonacci_numbers