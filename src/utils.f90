module utils
    implicit none

    ! make all entities private by default
    private                  
    ! explicitly declare public entities
    public iwp, rwp, minint32, maxint32
    public primefactors, gcd, lcm

    integer, parameter :: iwp = selected_int_kind(12)
    integer, parameter :: rwp = kind(0d0)
    integer, parameter :: minint32 = -2147483647, maxint32 = 2147483646

contains

    ! compute the prime factorization of a number
    function primefactors(number)

        integer(iwp), intent(in)  :: number          ! input number to factorize
        integer(iwp)              :: nreduced        ! running division result
        integer(iwp)              :: candidate       ! candidate divisor
        integer(iwp)              :: primelimit      ! upper limit on the candidate
        integer(iwp), allocatable :: primefactors(:) ! output list of prime factors

        ! Edge cases 
        if (number < 2) then 
            print *, 'ERROR: Cannot do prime factorization for numbers < 2.'
            return
        end if 

        ! Set a running division product
        nreduced = number
        ! allocate a 0-sized array
        allocate(primefactors(0))

        ! remove factors of 2 first
        if (mod(nreduced, 2) == 0) then
            primefactors = [2_iwp]
            do while (mod(nreduced, 2) == 0)
                nreduced = nreduced / 2
            end do
        end if

        ! We will find the prime factors by trial division, in other words
        ! just checking every number to see if it evenly divides the target.
        candidate  = 3
        primelimit = int(sqrt(real(number, rwp)), iwp)

        do 
            ! if candidate ever exceeds primelimit, then we know that
            ! the remaining "nreduced" must be a prime, so we can stop
            if (candidate >= primelimit) then
                primefactors = [primefactors, nreduced]
                exit 
            end if
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
                primelimit = int(sqrt(real(nreduced, rwp)), iwp)
                cycle
            end if
            ! update the candidate -
            ! we only need to check odd numbers since we already removed
            ! factors of 2
            candidate = candidate + 2
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