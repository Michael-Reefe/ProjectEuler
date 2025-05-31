program special_pythagorean_triplet

    implicit none
    integer, parameter :: sum_target = 1000
    integer            :: i, j, triple(3)
    logical(1)         :: found

    print *, '--------------------------------------'
    print *, 'Problem 9: Special Pythagorean Triplet'
    print *, 'https://projecteuler.net/problem=9    '
    print *, '--------------------------------------'

    ! we just need to generate some pythagorean triplets
    ! and check if their sum equals 1000.
    ! set an upper limit on the search range for n and m
    ! of 1000.
    found = .false.
    do i=1,1000
        if (found) exit
        do j=i+1,1000
            triple = pythagorean_triplet(i, j)
            if (sum(triple) == sum_target) then
                found = .true.
                exit
            end if
        end do
    end do

    print *, 'Answer:', product(triple)

contains 

    ! generate a pythagorean triplet from a pair of
    ! integers (n, m) where m > n, using a variant of
    ! Euclid's algorithm
    function pythagorean_triplet(n, m) result(triplet)
        integer, intent(in)  :: n, m
        integer              :: triplet(3)

        triplet(1) = 2*m*n
        triplet(2) = m**2 - n**2
        triplet(3) = m**2 + n**2
        if (mod(n, 2) /= 0 .and. mod(m, 2) /= 0) then 
            triplet = triplet / 2
        end if

    end function pythagorean_triplet

end program special_pythagorean_triplet