program large_sum

    use utils
    implicit none
    integer, parameter :: n=100, c=60
    integer            :: ii, jj, stat=1
    character(c)       :: bignumbers(n)
    character(c+10)    :: bignumsum

    print *, '-----------------------------------'
    print *, 'Problem 13: Large Sum              '
    print *, 'https://projecteuler.net/problem=13'
    print *, '-----------------------------------'

    ! read in the numbers from the data file
    open(1, file='../data/13.numbers.dat', status='old', &
         iostat=stat, action='read')
    ! make sure the file was read in without issue
    if (stat /= 0) then 
        print *, 'ERROR: Could not read ../data/13.numbers.dat'
        stop 
    end if
    ! fill in the numbers
    do ii=1,n
        read(1,*) bignumbers(ii)(11:60)
        ! zero-pad the first few digits to leave space for the sum
        do jj=1,10
            bignumbers(ii)(jj:jj) = '0'
        end do
    end do
    close(1)

    ! call the bigadd function
    bignumsum = bigadd(bignumbers, c, n)

    ! get the first ten NON-ZERO digits
    jj = 1
    do while (bignumsum(jj:jj) == '0')
        jj = jj + 1
    end do

    print *, 'Answer: ', bignumsum(jj:jj+9)

contains 

end program large_sum