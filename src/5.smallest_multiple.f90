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

end program smallest_multiple
