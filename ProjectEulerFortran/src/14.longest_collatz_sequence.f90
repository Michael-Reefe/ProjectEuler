program longest_collatz_sequence

    implicit none
    integer, parameter :: iwp = selected_int_kind(20)
    integer, parameter :: maxn = 1000000
    integer            :: i, minn, ilen, maxlen, maxnum 

    print *, '------------------------------------'
    print *, 'Problem 14: Longest Collatz Sequence'
    print *, 'https://projecteuler.net/problem=14 '
    print *, '------------------------------------'

    ! check the length of every collatz sequence
    ! under 1 million - but we actually only need
    ! to check for numbers above 500,000 since any
    ! collatz(2n) = collatz(n) + 1
    minn = maxn/2 + 1
    maxlen = 1
    maxnum = 1
    do i=minn,maxn-1
        ilen = collatz(i)
        if (ilen > maxlen) then
            maxlen = ilen
            maxnum = i
        end if
    end do

    print *, 'Answer:', maxnum

contains

    ! calculate the length of the collatz sequence that
    ! starts at n
    pure integer function collatz(n)
        integer, intent(in) :: n
        integer(iwp)        :: current

        collatz = 0
        current = n
        do while (current > 1)
            if (mod(current, 2) == 0) then 
                current = current / 2
            else 
                current = 3*current + 1
            end if
            collatz = collatz + 1
        end do

    end function collatz

end program longest_collatz_sequence