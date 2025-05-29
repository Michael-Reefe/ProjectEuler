program largest_prime_factor

    ! Setup and declare variables
    implicit none
    ! Need to make sure we can store large enough integers
    integer, parameter :: iwp     = selected_int_kind(12)
    integer(iwp)       :: ninput  = 600851475143_iwp

    print *, '----------------------------------'
    print *, 'Problem 3: Largest Prime Factor   '
    print *, 'https://projecteuler.net/problem=3'
    print *, '----------------------------------'

    ! Call the gpf function for the number we want
    ! to know the greatest prime factor of:
    print *, 'Answer:', gpf(ninput)

contains

    ! Now we have to define the function that we will actually use to 
    ! calculate the result
    pure function gpf(number)

        integer(iwp), intent(in) :: number       ! input
        integer(iwp)             :: gpf          ! output
        integer(iwp)             :: candidate    ! candidate divisor
        integer(iwp)             :: nreduced     ! running division result

        ! Edge case where number is <=2
        if (number .le. 2) then 
            gpf = number
            return
        end if

        ! We will find the prime factors by trial division, in other words
        ! just checking every number to see if it evenly divides the target.
        candidate = 2
        gpf       = 2
        nreduced  = number

        do while (candidate .le. number)
            ! once nreduced reaches 1, we can stop the loop
            if (nreduced .eq. 1) exit
            ! see if candidate evenly divides number 
            if (mod(nreduced, candidate) .eq. 0) then
                ! if so, update the running division result
                nreduced = nreduced / candidate
                ! and also update the gpf
                gpf = candidate
                ! but don't increment candidate in case the number
                ! is multiply divisible by it; just skip to the next
                ! loop iteration
                cycle
            end if
            ! update the candidate
            candidate = candidate + 1
        end do

    end function gpf

end program largest_prime_factor