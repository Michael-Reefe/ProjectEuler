program smallest_multiple

    ! Set up
    use utils
    implicit none
    integer, parameter :: nmax = 20
    integer(iwp)       :: ni, lcmout

    print *, '----------------------------------'
    print *, 'Problem 5: Smallest Multiple      '
    print *, 'https://projecteuler.net/problem=5'
    print *, '----------------------------------'

    ! The LCM of many numbers is the same as the LCM of
    ! nested pairs of numbers, i.e.:
    ! LCM(a,b,c,...) = LCM(a,LCM(b,LCM(c,...)))
    
    ! So we just need to compute the LCM for each pair
    ! iteratively, using the LCM function in the utils
    ! module
    lcmout = 1
    do ni=1,nmax
        lcmout = lcm(lcmout, ni)
    end do

    print *, 'Answer:', lcmout

contains

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

end program smallest_multiple
