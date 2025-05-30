program sum_square_difference

    implicit none
    integer, parameter :: nmax = 100
    integer :: numbers(nmax)
    integer :: n, sum_squares, square_sum, diff

    print *, '----------------------------------'
    print *, 'Problem 6: Sum Square Difference  '
    print *, 'https://projecteuler.net/problem=6'
    print *, '----------------------------------'

    ! this one is pretty straightforward, just
    ! compute the sum of the squares and the square
    ! of the sum
    numbers = [(n, n=1, nmax)]
    sum_squares = sum(numbers**2)
    square_sum  = sum(numbers)**2
    diff = square_sum - sum_squares

    print *, 'Answer:', diff

end program sum_square_difference