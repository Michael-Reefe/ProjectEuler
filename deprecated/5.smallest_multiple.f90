program smallest_multiple

    ! Set up
    implicit none
    integer :: ni, numinput(20)

    print *, '----------------------------------'
    print *, 'Problem 5: Smallest Multiple      '
    print *, 'https://projecteuler.net/problem=5'
    print *, '----------------------------------'

    ! Initialize numinput as all integers up to 20
    numinput = [(ni, ni=1, 20)]
    
    ! Call the lcm function for the result
    print *, 'Answer:', lcm(size(numinput),numinput)

contains

    pure integer function lcm(nnum,numbers)
        ! numbers is an array of length nnum containing all
        ! of the numbers that we want to compute the least
        ! common multiple of
        integer, intent(in) :: nnum
        integer, intent(in) :: numbers(nnum)
        integer             :: i, n
        logical             :: check

        ! infinite loop that will just check every integer 
        ! until it finds one that evenly divides all of the
        ! elements in numbers
        i = 1
        do 
            check = .true.
            ! for each i, check all of the elements in numbers
            do n=1,size(numbers)
                check = check .and. (mod(i, numbers(n)) .eq. 0)
            end do
            ! if check is still true, we've found the LCM
            if (check) then
                lcm = i
                exit
            end if
            i = i + 1
            ! failsafe if i is about to overflow
            if (i >= 2147483646) then
                lcm = -1 
                exit
            end if
        end do

    end function lcm

end program smallest_multiple
