program large_sum

    implicit none
    integer, parameter :: n=100
    integer        :: i, j, s, d, ones, carry, stat=1
    character(1)   :: onestr
    character(10)  :: carrystr
    character(50)  :: bignumbers(n)
    character(60)  :: bigsum, bigsuml

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
    do i=1,n
        read(1,*) bignumbers(i) 
    end do

    ! work out the sum one digit at a time
    carry = 0
    do j=50,1,-1
        s = carry
        do i=1,n
            read(bignumbers(i)(j:j), *) d
            s = s + d
        end do
        ones = mod(s, 10)  
        write(onestr, '(i1)') ones
        bigsum(j+10:j+10) = onestr
        carry = (s - ones) / 10
    end do
    
    ! handle the rest of the 'carry' by appending
    ! it to the beginning
    write(carrystr, '(i0)') carry
    bigsum(1:10) = adjustr(carrystr)
    bigsuml = adjustl(bigsum)

    print *, 'Answer: ', bigsuml(1:10)

end program large_sum