program power_digit_sum

    use utils
    implicit none
    character(:), allocatable :: bignum
    integer                   :: i, d, nchar, digitsum

    print *, '-----------------------------------'
    print *, 'Problem 16: Power Digit Sum        '
    print *, 'https://projecteuler.net/problem=16'
    print *, '-----------------------------------'

    ! we will use the "bigexp" subroutine from the utils
    ! module to generate 2^1000 as a string and put it into
    ! bignum
    call bigexp(bignum, 2, 1000)

    ! now sum up the digits
    nchar = len(bignum)
    digitsum = 0
    do i=1,nchar
        read(bignum(i:i), *) d
        digitsum = digitsum + d
    end do

    print *, 'Answer:', digitsum

end program power_digit_sum