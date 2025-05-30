program largest_prime_factor

    ! Setup and declare variables
    use utils
    implicit none
    ! Need to make sure we can store large enough integers
    integer(iwp)              :: ninput  = 600851475143_iwp
    integer(iwp), allocatable :: primes(:) 

    print *, '----------------------------------'
    print *, 'Problem 3: Largest Prime Factor   '
    print *, 'https://projecteuler.net/problem=3'
    print *, '----------------------------------'

    ! There is a prime factorization function in the "utils"
    ! module written specifically for this problem.  We will 
    ! use that and then take the maximum of the resulting array.
    primes = primefactors(ninput)
    print *, 'Answer:', maxval(primes)

end program largest_prime_factor