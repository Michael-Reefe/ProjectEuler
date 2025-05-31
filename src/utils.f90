module utils
    implicit none

    ! make all entities private by default
    private                  
    ! explicitly declare public entities
    public iwp, rwp, minint32, maxint32
    public reallocate, &
        sieve_of_eratosthenes, &
        segmented_sieve_step

    integer, parameter :: iwp = selected_int_kind(12)
    integer, parameter :: rwp = kind(0d0)
    integer, parameter :: minint32 = -2147483647, maxint32 = 2147483646

contains

    ! a little helper function that takes an allocated array and 
    ! reallocates it with a size n larger than it had before
    ! (n defaults to 1)
    subroutine reallocate(array, n)
        integer(iwp), intent(inout), allocatable :: array(:)
        integer(iwp), intent(in), optional       :: n
        integer(iwp), allocatable                :: tmp(:)

        ! make sure array is already allocated
        if (.not. allocated(array)) then 
            print *, 'ERROR: call to reallocate on unallocated array'
            stop
        end if
        ! first allocate tmp to the appropriate size
        if (present(n)) then 
            allocate(tmp(size(array)+n))
        else
            allocate(tmp(size(array)+1))
        end if
        ! then store a copy of array in tmp
        tmp(1:size(array)) = array(:)
        ! then we call move_alloc to move the allocation back into array
        call move_alloc(tmp, array)

    end subroutine reallocate


    ! Sieve of Eratosthenes: Generates all prime numbers less than n
    subroutine sieve_of_eratosthenes(n, primes)
        integer(iwp), intent(in)                 :: n
        integer(iwp), intent(out), allocatable   :: primes(:)
        integer(iwp)                             :: i, j, primelimit, nprimes
        integer                                  :: primemask(n)

        ! initialize everything as prime at first (except 1)
        primemask = 1
        primemask(1) = 0

        ! this is a well known algorithm that works by marking all of the
        ! multiples of every number less than sqrt(n) as composite, thereby
        ! leaving the remaining numbers as the primes
        primelimit = int(sqrt(real(n, rwp)), iwp)
        do i=2,primelimit
            if (primemask(i) == 1) then 
                do j=i**2,n,i
                    primemask(j) = 0
                end do
            end if 
        end do

        ! now we can allocate an array to hold the prime numbers found so far
        nprimes = sum(primemask)
        allocate(primes(nprimes))
        j=1
        do i=1,n
            if (primemask(i) == 1) then 
                primes(j) = i
                j = j + 1
            end if
        end do

    end subroutine sieve_of_eratosthenes


    ! an iteration of the segmented sieve algorithm
    subroutine segmented_sieve_step(n, delta, primes)
        ! n is the first integer to check
        integer(iwp), intent(in)                 :: n, delta
        ! primes holds the previously found primes 
        integer(iwp), intent(inout), allocatable :: primes(:)
        integer(iwp)                             :: i, j, p, m, primelimit, newprimes
        integer                                  :: primemask(delta)

        ! m is the last integer to check
        m = n + delta - 1
        ! initialize everything as prime at first like the regular sieve
        primemask = 1
        primelimit = int(sqrt(real(m, rwp)), iwp)

        do i=1,size(primes)
            p = primes(i)
            if (p > primelimit) exit
            ! j enumerates the multiples of p within the range (n, m)
            do j=n-mod(n,p),m-mod(m,p),p
                if (j < n) cycle
                primemask(j-n+1) = 0
            end do
        end do

        ! append the newly found prime numbers to the "primes" array
        j = size(primes) + 1
        newprimes = sum(primemask)
        call reallocate(primes, newprimes)
        do i=1,size(primemask)
            if (primemask(i) == 1) then
                primes(j) = i+n-1
                j = j+1
            end if
        end do

    end subroutine segmented_sieve_step

end module utils