program largest_prime_factor

    ! Setup and declare variables
    use utils
    implicit none
    ! Need to make sure we can store large enough integers
    integer(iwp)              :: ninput  = 600851475143_iwp
    integer(iwp), allocatable :: primefactors(:,:)

    print *, '----------------------------------'
    print *, 'Problem 3: Largest Prime Factor   '
    print *, 'https://projecteuler.net/problem=3'
    print *, '----------------------------------'

    ! A function for computing the prime factorization of a
    ! number has been created in the utils module, since it
    ! will be useful for future problems.  We can just use
    ! that function here and take the maximum value in the
    ! output array.
    call primefactorize(ninput, primefactors)
    print *, 'Answer:', maxval(primefactors(:,1))

contains



end program largest_prime_factor