program largest_prime_factor

    ! Setup and declare variables
    use utils
    implicit none
    ! Need to make sure we can store large enough integers
    integer(iwp)       :: ninput  = 600851475143_iwp

    print *, '----------------------------------'
    print *, 'Problem 3: Largest Prime Factor   '
    print *, 'https://projecteuler.net/problem=3'
    print *, '----------------------------------'

    print *, 'Answer:', gpf(ninput)

contains

    ! compute the greatest prime factor of a number 
    integer(iwp) function gpf(number)

        integer(iwp), intent(in)  :: number          ! input number to factorize
        integer(iwp)              :: nreduced, candidate, primelimit

        ! Edge cases 
        if (number < 2) then 
            print *, 'ERROR: Cannot do prime factorization for numbers < 2.'
            return
        end if 

        ! Set a running division product
        nreduced = number

        ! remove factors of 2 first
        if (mod(nreduced, 2) == 0) then
            gpf = 2_iwp
            do while (mod(nreduced, 2) == 0)
                nreduced = nreduced / 2
            end do
        end if

        ! We will find the prime factors by trial division, in other words
        ! just checking every number to see if it evenly divides the target.
        candidate  = 3_iwp
        primelimit = int(sqrt(real(number, rwp)), iwp)

        do 
            ! once nreduced reaches 1, we can stop the loop
            if (nreduced == 1) exit
            ! if candidate ever exceeds primelimit, then we know that
            ! the remaining "nreduced" must be a prime, so we can stop
            if (candidate > primelimit + 1) then
                gpf = nreduced
                exit 
            end if
            ! see if candidate evenly divides number 
            if (mod(nreduced, candidate) == 0) then
                ! if so, update the running division result
                nreduced = nreduced / candidate
                ! and also update the greatest prime factor
                gpf = candidate
                ! but don't increment candidate in case the number
                ! is multiply divisible by it; just skip to the next
                ! loop iteration
                primelimit = int(sqrt(real(nreduced, rwp)), iwp)
                cycle
            end if
            ! update the candidate -
            ! we only need to check odd numbers since we already removed
            ! factors of 2
            candidate = candidate + 2
        end do

    end function gpf


end program largest_prime_factor