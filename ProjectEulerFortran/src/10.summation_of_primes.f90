program summation_of_primes

    use utils
    implicit none
    integer(iwp), parameter   :: n = 2000000
    integer(iwp), allocatable :: primes(:)

    print *, '-----------------------------------'
    print *, 'Problem 10: Summation of Primes    '
    print *, 'https://projecteuler.net/problem=10'
    print *, '-----------------------------------'

    ! This problem is really easy because we already
    ! have a Sieve of Eratosthenes subroutine that we
    ! made for problem 7.  We can just call that to
    ! get all the primes below 2 million and then sum
    ! them up
    call sieve_of_eratosthenes(n, primes)

    print *, 'Answer:', sum(primes)

end program summation_of_primes