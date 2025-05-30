module utils
    implicit none

    ! make all entities private by default
    private                  
    ! explicitly declare public entities
    public iwp, minint32, maxint32
    public primefactors, gcd, lcm

    integer, parameter :: iwp = selected_int_kind(19)
    integer, parameter :: minint32 = -2147483647, maxint32 = 2147483646

contains

    ! compute the prime factorization of a number
    function primefactors(number)

        integer(iwp), intent(in)  :: number          ! input number to factorize
        integer(iwp)              :: nreduced        ! running division result
        integer(iwp)              :: candidate       ! candidate divisor
        integer(iwp), allocatable :: primefactors(:) ! output list of prime factors

        ! Edge cases 
        if (number < 2) then 
            print *, 'ERROR: Cannot do prime factorization for numbers < 2.'
            return
        end if 

        if (number == 2) then 
            allocate(primefactors(1))
            primefactors(1) = 2
            return
        end if

        ! We will find the prime factors by trial division, in other words
        ! just checking every number to see if it evenly divides the target.
        candidate = 2
        nreduced  = number
        ! allocate a 0-sized array
        allocate(primefactors(0))

        do while (candidate <= number)
            ! once nreduced reaches 1, we can stop the loop
            if (nreduced == 1) exit
            ! see if candidate evenly divides number 
            if (mod(nreduced, candidate) == 0) then
                ! if so, update the running division result
                nreduced = nreduced / candidate
                ! and also update the prime factor list 
                ! (this auto-allocates an array of the appropriate size)
                primefactors = [primefactors, candidate]
                ! but don't increment candidate in case the number
                ! is multiply divisible by it; just skip to the next
                ! loop iteration
                cycle
            end if
            ! update the candidate
            candidate = candidate + 1
        end do

    end function primefactors

    ! compute the GCD using the Euclidean algorithm
    pure integer(iwp) function gcd(a, b)
        integer(iwp), intent(in) :: a, b
        integer(iwp)             :: a2, b2
        ! copy a and b
        a2=a 
        b2=b
        ! repeatedly take the mod of the larger number until one of them is 0
        do while (a2 > 0 .and. b2 > 0 .and. a2 /= b2)
            if (a2 > b2) a2 = mod(a2, b2)
            if (b2 > a2) b2 = mod(b2, a2)
        end do
        ! the gcd is the resultant a2 or b2 which is not 0
        gcd = max(a2, b2)
    end function gcd

    ! compute the LCM using its relationship to the GCD
    pure integer(iwp) function lcm(a, b)
        integer(iwp), intent(in) :: a, b
        ! do the division first to prevent overflows for (really) large numbers
        lcm = abs(a) / gcd(a, b) * abs(b)
    end function lcm

end module utils