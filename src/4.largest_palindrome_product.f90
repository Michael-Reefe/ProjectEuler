program largest_palindrome_product

    ! Setup and declare variables
    implicit none
    integer :: ninput = 3

    print *, '-------------------------------------'
    print *, 'Problem 4: Largest Palindrome Product'
    print *, 'https://projecteuler.net/problem=4'
    print *, '-------------------------------------'

    print *, 'Answer:', gpp(ninput)

contains 

    ! Define a function to calculate the greatest palindrome product
    ! of two numbers with some number of digits (ndigits)
    pure integer function gpp(ndigits)
        integer, intent(in) :: ndigits      ! input - number of digits
        integer             :: n1, n2       ! loop variables
        integer             :: minn, maxn   ! loop variable limits
        integer             :: product      ! product of n1 x n2

        ! loop through every possible product of two 3 digit numbers.
        ! start from the large end since that's more likely to contain
        ! a large palindrome
        gpp  = 0
        minn = 10**(ndigits-1)
        maxn = 10**ndigits-1
        do n1=maxn,minn,-1
            ! for the limits, we use n1 here so we don't double-check
            ! the pairs (n1,n2) and (n2,n1)
            do n2=maxn,n1,-1
                product = n1*n2
                ! we only need to check if the product is a palindrome
                ! if it's larger than the previous palindrom product
                if (product > gpp .and. ispalindrome(product)) then 
                    gpp = product
                end if
            end do
        end do

    end function gpp

    ! Inner function to check whether a number is a palindrome or not
    pure logical function ispalindrome(number)
        integer, intent(in) :: number
        integer             :: i, strlen
        character(20)       :: strnum, strrev
        ! convert the integer number to a string
        write(strnum, '(i0)') number
        strlen = len(strnum)
        ! the reverse of the string
        do i=1,strlen
            strrev(strlen-i+1:strlen-i+1) = strnum(i:i)
        end do
        ! check if the number is a palindrome
        ispalindrome = trim(adjustl(strnum)) == trim(adjustl(strrev))
    end function ispalindrome

end program largest_palindrome_product