program multiples_of_3_or_5

    ! Setup and declare variables
    implicit none
    integer :: i
    integer :: multiple_sum

    print *, '----------------------------------'
    print *, 'Problem 1: Multiples of 3 or 5    '
    print *, 'https://projecteuler.net/problem=1'
    print *, '----------------------------------'
    
    ! This can be done with a pretty simple loop and the mod function
    multiple_sum = 0
    do i=0,999
        if (mod(i, 3) .eq. 0 .or. mod(i, 5) .eq. 0) multiple_sum = multiple_sum + i
    end do

    ! Output the results
    print *, 'Answer:', multiple_sum

end program multiples_of_3_or_5