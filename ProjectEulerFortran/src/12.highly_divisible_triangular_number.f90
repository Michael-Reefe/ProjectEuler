program highly_divisible_triangular_number

    use utils
    implicit none
    integer(iwp) :: i, ndiv, ndiv_tmp, tnum

    print *, '----------------------------------------------'
    print *, 'Problem 12: Highly Divisible Triangular Number'
    print *, 'https://projecteuler.net/problem=12           '
    print *, '----------------------------------------------'

    ! loop through and have a running total that gives the 
    ! triangular numbers
    i = 1
    ndiv_tmp = 1
    do while (ndiv < 500)
        ! triangular numbers can be generated with this formula:
        tnum = i*(i+1)/2
        ! check how many factors this triangular number has by
        ! checking the divisors of i and i+1 instead of checking
        ! for tnum itself (which can get large)
        if (mod(i,2) == 0) then 
            ndiv_tmp = ndivisors(i+1)
            ndiv = ndivisors(i/2)*ndiv_tmp
        else
            ndiv = ndiv_tmp*ndivisors((i+1)/2)
        end if
        i = i + 1
    end do

    print *, 'Answer:', tnum

contains 

    integer(iwp) function ndivisors(number)
        integer(iwp), intent(in)  :: number
        integer(iwp), allocatable :: primes(:,:)
        ! the number of divisors of any integer is directly
        ! related to its prime factorization, which we already
        ! have a function for:
        call primefactorize(number, primes)
        ! specifically, the number of divisors is equal to the 
        ! product of the exponents of each prime factor, which
        ! are stored in the second column of primes
        ndivisors = product(primes(:,2)+1)
    end function ndivisors

end program highly_divisible_triangular_number